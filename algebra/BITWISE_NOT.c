#define NAME LABEL(BITWISE_NOT)
#define ARGUMENTS 1

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"
  SPECIFY_ADDRESS(arguments[0], 0,3)
  result = ~MEMORY_AT_ADDRESS(arguments[0]);
  break;

  default:
  VERIFY_SINGLE_VALUE(MEMORY_AT_ADDRESS(arguments[0]), ==, result)
  COLLECT_FINDINGS
  MEMORY_AT_ADDRESS(arguments[0]) = 5;
  //----------------------
  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
MEMORY_AT_ADDRESS(arguments[0]) = ~MEMORY_AT_ADDRESS(arguments[0]);

#ifdef CLT
PRINT(" = %u ",MEMORY_AT_ADDRESS(arguments[0]))
#endif
#endif

#define DESCRIPTION \
Performs a binary "not" on the first argument.

#include "../internal/instruction_post_template.c"
