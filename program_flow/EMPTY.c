#define NAME LABEL(EMPTY)

#ifdef IMPLEMENTATION_MODE
#define REDEF_IMPLEMENTATION_MODE
#endif

#include "../internal/instruction_pre_template.c"

#define DESCRIPTION \
Does nothing.

#include "../internal/instruction_post_template.c"
