#define NAME LABEL(SUBTRACT)
#define ARGUMENTS 3

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario w/ Same argument"
  SPECIFY_ADDRESS(arguments[0], 0,3)
  SPECIFY_ADDRESS(arguments[1], 0,3)
  result = MEMORY_AT_ADDRESS(arguments[0]) - MEMORY_AT_ADDRESS(arguments[1]);
  break;

  case 1:
  VERIFY_SINGLE_VALUE(MEMORY_AT_ADDRESS(arguments[0]), ==, result)
  VERIFY_SINGLE_VALUE(MEMORY_AT_ADDRESS(arguments[2]), ==, 0)
  COLLECT_FINDINGS
  MEMORY_AT_ADDRESS(arguments[0]) = 5;
  //----------------------

  #undef SUBTITLE
  #define SUBTITLE "Underflow"
  SPECIFY_ADDRESS(arguments[0], 0,1)
  SPECIFY_ADDRESS(arguments[1], 0,3)
  result = MEMORY_AT_ADDRESS(arguments[0]) - MEMORY_AT_ADDRESS(arguments[1]);
  break;

  default:
  VERIFY_SINGLE_VALUE(MEMORY_AT_ADDRESS(arguments[0]), ==, result)
  VERIFY_SINGLE_VALUE(MEMORY_AT_ADDRESS(arguments[2]), ==, 1)
  COLLECT_FINDINGS
  MEMORY_AT_ADDRESS(arguments[0]) = 0;
  //----------------------
  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
working_variable = MEMORY_AT_ADDRESS(arguments[0]);
MEMORY_AT_ADDRESS(arguments[0]) -= MEMORY_AT_ADDRESS(arguments[1]);

MEMORY_AT_ADDRESS(arguments[2]) = MEMORY_AT_ADDRESS(arguments[0]) > working_variable;

#ifdef CLT
PRINT(" = %u ", MEMORY_AT_ADDRESS(arguments[0]))
#endif
#endif

#define DESCRIPTION \
Subtracts the second argument out of the first argument. The third argument is set to 1 if the instruction underflows, and 0 if it doesnt.

#include "../internal/instruction_post_template.c"
