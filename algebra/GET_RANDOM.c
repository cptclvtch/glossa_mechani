#define NAME LABEL(GET_RANDOM)
#define ARGUMENTS 1

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"
  SPECIFY_ADDRESS(arguments[0], 0,5)
  break;

  default:
  VERIFY_SINGLE_VALUE(MEMORY_AT_ADDRESS(arguments[0]), ==, 2531011)
  COLLECT_FINDINGS
  //----------------------
  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
MEMORY_AT_ADDRESS(arguments[0]) = (seed = seed * 214013 + 2531011);
#endif

#define DESCRIPTION \
Places a pseudo-random (LCG) value in the first argument.

#include "../internal/instruction_post_template.c"
