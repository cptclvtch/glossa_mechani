#define NAME LABEL(LESS_THAN)
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
  result = MEMORY_AT_ADDRESS(arguments[0]) < MEMORY_AT_ADDRESS(arguments[1]);
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
MEMORY_AT_ADDRESS(arguments[2]) = (MEMORY_AT_ADDRESS(arguments[0]) < MEMORY_AT_ADDRESS(arguments[1]));
#endif

#define DESCRIPTION \
Places a '1' into the third argument if the first argument is less than the second argument. Places a '0' otherwise.

#include "../internal/instruction_post_template.c"
