#ifndef HEADER_fd_src_app_fdctl_run_h
#define HEADER_fd_src_app_fdctl_run_h

#include "../fdctl.h"
#include "tiles/tiles.h"

#include "../../../tango/xdp/fd_xsk.h"

typedef struct {
  config_t *       config;
  fd_topo_tile_t * tile;
} tile_main_args_t;

int
solana_labs_main( void * args );

int
tile_main( void * _args );

void
run_firedancer( config_t * const config );

#endif /* HEADER_fd_src_app_fdctl_run_h */
