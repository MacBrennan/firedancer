#define _GNU_SOURCE
#define FD_UNALIGNED_ACCESS_STYLE 0
#include "../../util/bits/fd_bits.h"

#include "fdctl.h"

#include <fcntl.h>
#include <sys/mman.h>

action_t ACTIONS[ ACTIONS_CNT ] = {
  { .name = "run",        .args = NULL,               .fn = run_cmd_fn,        .perm = run_cmd_perm },
  { .name = "run1",       .args = run1_cmd_args,      .fn = run1_cmd_fn,       .perm = NULL },
  { .name = "run-solana", .args = NULL,               .fn = run_solana_cmd_fn, .perm = NULL },
  { .name = "configure",  .args = configure_cmd_args, .fn = configure_cmd_fn,  .perm = configure_cmd_perm },
  { .name = "monitor",    .args = monitor_cmd_args,   .fn = monitor_cmd_fn,    .perm = monitor_cmd_perm },
  { .name = "keygen",     .args = NULL,               .fn = keygen_cmd_fn,     .perm = NULL },
  { .name = "ready",      .args = NULL,               .fn = ready_cmd_fn,      .perm = NULL },
  { .name = "info",       .args = NULL,               .fn = info_cmd_fn,       .perm = NULL },
  { .name = "mem",        .args = NULL,               .fn = info_cmd_fn,       .perm = NULL },
  { .name = "topo",       .args = NULL,               .fn = info_cmd_fn,       .perm = NULL },
};

extern int * fd_log_private_shared_lock;

static void
main_boot_memfd( int        boot_memfd,
                 config_t * config ) {
  uchar * bytes = mmap( NULL, sizeof( config_t ), PROT_READ, MAP_PRIVATE, boot_memfd, 0 );
  if( FD_UNLIKELY( bytes == MAP_FAILED ) ) {
    fd_log_private_fprintf_0( STDERR_FILENO, "mmap() failed (%i-%s)", errno, fd_io_strerror( errno ) );
    exit_group( 1 );
  }
  fd_memcpy( config, bytes, sizeof( config_t ) );
  if( FD_UNLIKELY( munmap( bytes, sizeof( config_t ) ) ) ) {
    fd_log_private_fprintf_0( STDERR_FILENO, "munmap() failed (%i-%s)", errno, fd_io_strerror( errno ) );
    exit_group( 1 );
  }
  if( FD_UNLIKELY( close( boot_memfd ) ) ) {
    fd_log_private_fprintf_0( STDERR_FILENO, "close() failed (%i-%s)", errno, fd_io_strerror( errno ) );
    exit_group( 1 );
  }
}

config_t fdctl_boot( int *    pargc,
                     char *** pargv ) {
  int boot_memfd = fd_env_strip_cmdline_int( pargc, pargv, "--boot-memfd", NULL, -1 );
  if( FD_UNLIKELY( boot_memfd >= 0 ) ) {
    config_t config;
    main_boot_memfd( boot_memfd, &config );

    /* Parent must have already opened the log file. No main command
        line args are provided in memfd case.  For now the file descriptors
        are assumed constant. */
    int boot_argc = 4;
    char * _boot_argv[ 5 ] = { "--log-lock-memfd", "3", "--log-fd", "4", NULL };
    char ** boot_argv = _boot_argv;
    fd_boot( &boot_argc, &boot_argv );

    return config;
  } else {
    fd_boot( pargc, pargv );

    /* load configuration and command line parsing */
    return config_parse( pargc, pargv );
  }
}

int
main1( int     argc,
       char ** _argv ) {
  char ** argv = _argv;
  argc--; argv++;

  config_t config = fdctl_boot( &argc, &argv );
  fd_log_thread_set( "main" );

  if( FD_UNLIKELY( !argc ) ) FD_LOG_ERR(( "no subcommand specified" ));

  action_t * action = NULL;
  for( ulong i=0; i<sizeof(ACTIONS)/sizeof(ACTIONS[ 0 ]); i++ ) {
    if( FD_UNLIKELY( !strcmp( argv[ 0 ], ACTIONS[ i ].name ) ) ) {
      action = &ACTIONS[ i ];
      break;
    }
  }
  if( FD_UNLIKELY( !action ) ) FD_LOG_ERR(( "unknown subcommand `%s`", argv[ 0 ] ));

  argc--; argv++;

  args_t args;
  if( FD_LIKELY( action->args ) ) action->args( &argc, &argv, &args );
  if( FD_UNLIKELY( argc ) ) FD_LOG_ERR(( "unknown argument `%s`", argv[ 0 ] ));

  /* check if we are appropriate permissioned to run the desired command */
  if( FD_LIKELY( action->perm ) ) {
    fd_caps_ctx_t caps[1] = {0};
    action->perm( &args, caps, &config );
    if( FD_UNLIKELY( caps->err_cnt ) ) {
      for( ulong i=0; i<caps->err_cnt; i++ ) FD_LOG_WARNING(( "%s", caps->err[ i ] ));
      if( FD_LIKELY( !strcmp( action->name, "run" ) ) ) {
        FD_LOG_ERR(( "insufficient permissions to execute command `%s`. It is recommended "
                     "to start Firedancer as the root user, but you can also start it "
                     "with the missing capabilities listed above. The program only needs "
                     "to start with elevated permissions to do privileged operations at "
                     "boot, and will immediately drop permissions and switch to the user "
                     "specified in your configuration file once they are complete. Firedancer "
                     "will not execute outside of the boot process as root, and will refuse "
                     "to start if it cannot drop privileges. Firedancer needs to be started "
                     "privileged to configure high performance networking with XDP.", action->name ));
      } else if( FD_LIKELY( !strcmp( action->name, "configure" ) ) ) {
        FD_LOG_ERR(( "insufficient permissions to execute command `%s`. It is recommended "
                     "to configure Firedancer as the root user. Firedancer configuration requires "
                     "root because it does privileged operating system actions like setting up XDP. "
                     "Configuration is a local action that does not access the network, and the process "
                     "exits immedaitely once configuration completes. The user that Firedancer runs "
                     "as is specified in your configuration file, and although configuration runs as root "
                     "it will permission the relevant resources for the user in your configuration file, "
                     "which can be an anonymous maximally restrictive account with no privileges.", action->name ));
      } else {
        FD_LOG_ERR(( "insufficient permissions to execute command `%s`", action->name ));
      }
    }
  }

  /* run the command */
  action->fn( &args, &config );

  return 0;
}
