#define NAME LABEL(DECAPITATE)

#ifdef IMPLEMENTATION_MODE
#define REDEF_IMPLEMENTATION_MODE
#endif

#include "../internal/instruction_pre_template.c"

#define DESCRIPTION \
Kills the current head.

#include "../internal/instruction_post_template.c"
