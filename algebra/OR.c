#define NAME LABEL(OR)
#define ARGUMENTS 3

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"
  SPECIFY_ADDRESS(arguments[0], 0,1)
  SPECIFY_ADDRESS(arguments[1], 0,2)
  result = MEMORY_AT_ADDRESS(arguments[0]) || MEMORY_AT_ADDRESS(arguments[1]);
  break;

  default:
  VERIFY_SINGLE_VALUE(MEMORY_AT_ADDRESS(arguments[2]), ==, result)
  COLLECT_FINDINGS
  //----------------------
  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
MEMORY_AT_ADDRESS(arguments[2]) = MEMORY_AT_ADDRESS(arguments[0]) || MEMORY_AT_ADDRESS(arguments[1]);
#endif

#define DESCRIPTION \
Places the result of a logical "or" of the first and second argument into the third argument.

#include "../internal/instruction_post_template.c"
