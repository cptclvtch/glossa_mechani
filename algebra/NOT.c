#define NAME LABEL(NOT)
#define ARGUMENTS 2

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"
  SPECIFY_ADDRESS(arguments[0], 0,2)
  SPECIFY_ADDRESS(arguments[1], 0,5)
  result = !MEMORY_AT_ADDRESS(arguments[0]);
  break;

  default:
  VERIFY_SINGLE_VALUE(MEMORY_AT_ADDRESS(arguments[1]), ==, result)
  COLLECT_FINDINGS
  //----------------------
  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
MEMORY_AT_ADDRESS(arguments[1]) = !MEMORY_AT_ADDRESS(arguments[0]);
#endif

#define DESCRIPTION \
Places the result of a logical "not" of the first into the second argument.

#include "../internal/instruction_post_template.c"
