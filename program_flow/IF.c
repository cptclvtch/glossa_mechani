#define NAME LABEL(IF)
#define ARGUMENTS 1

#include "../internal/instruction_pre_template.c"

#ifdef IMPLEMENTATION_MODE
if(MEMORY_AT_ADDRESS(arguments[0]))
{
  goto advance_head;
}
else
{
  ADVANCE_HEAD
  #include "../internal/instruction_check_and_set.c"
  goto advance_head;
}

#define REDEF_IMPLEMENTATION_MODE
#undef IMPLEMENTATION_MODE
#endif

#define DESCRIPTION \
Places the head on the next instruction if the argument is greater than 0, \
or places the head on the instruction after that if the argument is 0.

#include "../internal/instruction_post_template.c"
