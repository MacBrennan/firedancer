#include "fdctl.h"
#include <stdio.h>

#define MAX_LENGTH 4096

#define PRINT_HELP( ... ) do {                                                \
    int n = snprintf( cur, rem, __VA_ARGS__ );                                \
    if( FD_UNLIKELY( n < 0 ) ) FD_LOG_ERR(( "snprintf failed" ));             \
    if( FD_UNLIKELY( (ulong)n >= rem ) ) FD_LOG_ERR(( "snprintf overflow" )); \
    rem -= (ulong)n;                                                          \
    cur += n;                                                                 \
  } while( 0 )

void
help_cmd_fn( args_t *         args,
             config_t * const config ) {
  (void)args;
  (void)config;

  char help[ MAX_LENGTH ];
  char * cur = help;
  ulong rem = MAX_LENGTH - 1;

  PRINT_HELP( "fdctl: Firedancer control binary\n\n" );
  PRINT_HELP( "usage: fdctl [OPTIONS] <SUBCOMMAND>\n\n" );
  PRINT_HELP( "Sub Commands:\n" );

  for( ulong i=0; i < ACTIONS_CNT ; i++ ) {
    PRINT_HELP( "%16s\t%s", ACTIONS[ i ].name, ACTIONS[ i ].desc );
    uchar alias = 0;
    for( ulong j=0; j < ACTION_ALIASES_CNT; j++ ) {
      if( FD_UNLIKELY( !strcmp( ACTIONS[ i ].name, ACTION_ALIASES[ j ].alias ) ) ) {
        if ( FD_UNLIKELY( !alias ) ) {
          PRINT_HELP( " [ aliases:" );
          alias = 1;
        }
        PRINT_HELP( " %s,", ACTION_ALIASES[ j ].name );
      }
    }
    if( FD_UNLIKELY( alias ) ) {
      cur -= 1;   /* remove trailing comma */
      rem += 1;
      PRINT_HELP( " ]" );
    }
    PRINT_HELP( "\n" );
  }

  PRINT_HELP( "\nOptions:\n" );
  /* fdctl does not have many flag arguments
     so we hard-code the --config parameter. */
  PRINT_HELP( "\t--config <PATH>\n" );
  PRINT_HELP( "\t\tPath to config TOML file" );

  /* TODO: add subcommand help args */

  FD_LOG_NOTICE(( "\n%s", help ));
}
