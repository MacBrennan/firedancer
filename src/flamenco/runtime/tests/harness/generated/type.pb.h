/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.9.1 */

#ifndef PB_ORG_SOLANA_SEALEVEL_V1_TYPE_PB_H_INCLUDED
#define PB_ORG_SOLANA_SEALEVEL_V1_TYPE_PB_H_INCLUDED

#include "../../../../../ballet/nanopb/pb_firedancer.h"
#include "metadata.pb.h"

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
typedef struct fd_exec_test_type_context {
    pb_bytes_array_t *content;
} fd_exec_test_type_context_t;

typedef struct fd_exec_test_type_effects {
    uint64_t result;
    pb_bytes_array_t *representation;
    pb_bytes_array_t *yaml;
} fd_exec_test_type_effects_t;

typedef struct fd_exec_test_type_fixture {
    bool has_metadata;
    fd_exec_test_fixture_metadata_t metadata;
    bool has_input;
    fd_exec_test_type_context_t input;
    bool has_output;
    fd_exec_test_type_effects_t output;
} fd_exec_test_type_fixture_t;


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define FD_EXEC_TEST_TYPE_CONTEXT_INIT_DEFAULT   {NULL}
#define FD_EXEC_TEST_TYPE_EFFECTS_INIT_DEFAULT   {0, NULL, NULL}
#define FD_EXEC_TEST_TYPE_FIXTURE_INIT_DEFAULT   {false, FD_EXEC_TEST_FIXTURE_METADATA_INIT_DEFAULT, false, FD_EXEC_TEST_TYPE_CONTEXT_INIT_DEFAULT, false, FD_EXEC_TEST_TYPE_EFFECTS_INIT_DEFAULT}
#define FD_EXEC_TEST_TYPE_CONTEXT_INIT_ZERO      {NULL}
#define FD_EXEC_TEST_TYPE_EFFECTS_INIT_ZERO      {0, NULL, NULL}
#define FD_EXEC_TEST_TYPE_FIXTURE_INIT_ZERO      {false, FD_EXEC_TEST_FIXTURE_METADATA_INIT_ZERO, false, FD_EXEC_TEST_TYPE_CONTEXT_INIT_ZERO, false, FD_EXEC_TEST_TYPE_EFFECTS_INIT_ZERO}

/* Field tags (for use in manual encoding/decoding) */
#define FD_EXEC_TEST_TYPE_CONTEXT_CONTENT_TAG    1
#define FD_EXEC_TEST_TYPE_EFFECTS_RESULT_TAG     1
#define FD_EXEC_TEST_TYPE_EFFECTS_REPRESENTATION_TAG 2
#define FD_EXEC_TEST_TYPE_EFFECTS_YAML_TAG       3
#define FD_EXEC_TEST_TYPE_FIXTURE_METADATA_TAG   1
#define FD_EXEC_TEST_TYPE_FIXTURE_INPUT_TAG      2
#define FD_EXEC_TEST_TYPE_FIXTURE_OUTPUT_TAG     3

/* Struct field encoding specification for nanopb */
#define FD_EXEC_TEST_TYPE_CONTEXT_FIELDLIST(X, a) \
X(a, POINTER,  SINGULAR, BYTES,    content,           1)
#define FD_EXEC_TEST_TYPE_CONTEXT_CALLBACK NULL
#define FD_EXEC_TEST_TYPE_CONTEXT_DEFAULT NULL

#define FD_EXEC_TEST_TYPE_EFFECTS_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT64,   result,            1) \
X(a, POINTER,  SINGULAR, BYTES,    representation,    2) \
X(a, POINTER,  SINGULAR, BYTES,    yaml,              3)
#define FD_EXEC_TEST_TYPE_EFFECTS_CALLBACK NULL
#define FD_EXEC_TEST_TYPE_EFFECTS_DEFAULT NULL

#define FD_EXEC_TEST_TYPE_FIXTURE_FIELDLIST(X, a) \
X(a, STATIC,   OPTIONAL, MESSAGE,  metadata,          1) \
X(a, STATIC,   OPTIONAL, MESSAGE,  input,             2) \
X(a, STATIC,   OPTIONAL, MESSAGE,  output,            3)
#define FD_EXEC_TEST_TYPE_FIXTURE_CALLBACK NULL
#define FD_EXEC_TEST_TYPE_FIXTURE_DEFAULT NULL
#define fd_exec_test_type_fixture_t_metadata_MSGTYPE fd_exec_test_fixture_metadata_t
#define fd_exec_test_type_fixture_t_input_MSGTYPE fd_exec_test_type_context_t
#define fd_exec_test_type_fixture_t_output_MSGTYPE fd_exec_test_type_effects_t

extern const pb_msgdesc_t fd_exec_test_type_context_t_msg;
extern const pb_msgdesc_t fd_exec_test_type_effects_t_msg;
extern const pb_msgdesc_t fd_exec_test_type_fixture_t_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define FD_EXEC_TEST_TYPE_CONTEXT_FIELDS &fd_exec_test_type_context_t_msg
#define FD_EXEC_TEST_TYPE_EFFECTS_FIELDS &fd_exec_test_type_effects_t_msg
#define FD_EXEC_TEST_TYPE_FIXTURE_FIELDS &fd_exec_test_type_fixture_t_msg

/* Maximum encoded size of messages (where known) */
/* fd_exec_test_TypeContext_size depends on runtime parameters */
/* fd_exec_test_TypeEffects_size depends on runtime parameters */
/* fd_exec_test_TypeFixture_size depends on runtime parameters */

/* Mapping from canonical names (mangle_names or overridden package name) */
#define org_solana_sealevel_v1_TypeContext fd_exec_test_TypeContext
#define org_solana_sealevel_v1_TypeEffects fd_exec_test_TypeEffects
#define org_solana_sealevel_v1_TypeFixture fd_exec_test_TypeFixture
#define ORG_SOLANA_SEALEVEL_V1_TYPE_CONTEXT_INIT_DEFAULT FD_EXEC_TEST_TYPE_CONTEXT_INIT_DEFAULT
#define ORG_SOLANA_SEALEVEL_V1_TYPE_EFFECTS_INIT_DEFAULT FD_EXEC_TEST_TYPE_EFFECTS_INIT_DEFAULT
#define ORG_SOLANA_SEALEVEL_V1_TYPE_FIXTURE_INIT_DEFAULT FD_EXEC_TEST_TYPE_FIXTURE_INIT_DEFAULT
#define ORG_SOLANA_SEALEVEL_V1_TYPE_CONTEXT_INIT_ZERO FD_EXEC_TEST_TYPE_CONTEXT_INIT_ZERO
#define ORG_SOLANA_SEALEVEL_V1_TYPE_EFFECTS_INIT_ZERO FD_EXEC_TEST_TYPE_EFFECTS_INIT_ZERO
#define ORG_SOLANA_SEALEVEL_V1_TYPE_FIXTURE_INIT_ZERO FD_EXEC_TEST_TYPE_FIXTURE_INIT_ZERO

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
