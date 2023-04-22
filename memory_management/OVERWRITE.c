#define NAME LABEL(OVERWRITE)
#define ARGUMENTS 2

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"
  SPECIFY_ADDRESS(arguments[0], 0,5)
  SPECIFY_ADDRESS(arguments[1], 0,2)
  break;

  default:
  VERIFY_SINGLE_VALUE(MEMORY_AT_ADDRESS(arguments[0]), ==, MEMORY_AT_ADDRESS(arguments[1]))
  COLLECT_FINDINGS
  //----------------------
  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
//INDEX_MOVEMENT
MEMORY_AT_ADDRESS(arguments[0]) = MEMORY_AT_ADDRESS(arguments[1]);
#endif

#define DESCRIPTION \
Replaces the value of the first argument with the value of the \
second argument.

#include "../internal/instruction_post_template.c"
