#define NAME LABEL(GET_HEAD)
#define ARGUMENTS 2

#include "../internal/instruction_pre_template.c"

#ifdef IMPLEMENTATION_MODE
MEMORY_AT_ADDRESS(arguments[0]) = head.array;
MEMORY_AT_ADDRESS(arguments[1]) = head.index;
#endif

#define DESCRIPTION \
Populates the two arguments with the current location of the head (array and index respectively).

#include "../internal/instruction_post_template.c"
