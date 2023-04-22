#define NAME LABEL(DIVIDE)
#define ARGUMENTS 4

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"
  SPECIFY_ADDRESS(arguments[0], 0,3)
  SPECIFY_ADDRESS(arguments[1], 0,3)
  SPECIFY_ADDRESS(arguments[3], 0,6)
  result = MEMORY_AT_ADDRESS(arguments[0]) / MEMORY_AT_ADDRESS(arguments[1]);
  break;

  case 1:
  VERIFY_SINGLE_VALUE(MEMORY_AT_ADDRESS(arguments[0]), ==, result)
  VERIFY_SINGLE_VALUE(MEMORY_AT_ADDRESS(arguments[3]), ==, 0)
  COLLECT_FINDINGS
  MEMORY_AT_ADDRESS(arguments[0]) = 5;
  //----------------------

  #undef SUBTITLE
  #define SUBTITLE "Division by zero"
  SPECIFY_ADDRESS(arguments[0], 0,3)
  SPECIFY_ADDRESS(arguments[1], 0,1)
  break;

  default:
  VERIFY_SINGLE_VALUE(MEMORY_AT_ADDRESS(arguments[0]), ==, 5)
  VERIFY_SINGLE_VALUE(MEMORY_AT_ADDRESS(arguments[3]), ==, 1)
  COLLECT_FINDINGS
  MEMORY_AT_ADDRESS(arguments[0]) = 5;
  //----------------------
  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
MEMORY_AT_ADDRESS(arguments[2]) = MEMORY_AT_ADDRESS(arguments[0]);
if(MEMORY_AT_ADDRESS(arguments[1]))
{
  MEMORY_AT_ADDRESS(arguments[3]) = 0;
  MEMORY_AT_ADDRESS(arguments[2]) %= MEMORY_AT_ADDRESS(arguments[1]);
  MEMORY_AT_ADDRESS(arguments[0]) /= MEMORY_AT_ADDRESS(arguments[1]);
}
else
{
  MEMORY_AT_ADDRESS(arguments[3]) = 1;

  #ifdef CLT
  PRINT(" Division by zero. ")
  #endif
}
#ifdef CLT
PRINT(" = %u , %u",MEMORY_AT_ADDRESS(arguments[0]), MEMORY_AT_ADDRESS(arguments[2]))
#endif
#endif

#define DESCRIPTION \
Divides the first argument by the second argument. The remainder goes into the third argument. \
A second argument of 0 outputs a remainder thats the same as the first argument. The fourth argument is set to 1 if divided by zero, and 0 if it doesnt.

#include "../internal/instruction_post_template.c"
