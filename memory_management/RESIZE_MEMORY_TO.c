#define NAME LABEL(RESIZE_MEMORY_TO)
#define ARGUMENTS 1

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"
  SPECIFY_ADDRESS(arguments[0], 0, 3)
  break;

  case 1:
  VERIFY_SINGLE_VALUE(MEMORY_MAX_INDEX, ==, MEMORY_AT_ADDRESS(arguments[0]))
  COLLECT_FINDINGS

  test_counter++;
  SPECIFY_ADDRESS(arguments[0], 0, 4)

  case 2:
  #undef SUBTITLE
  #define SUBTITLE "Invalid resizes"

  VERIFY_SINGLE_VALUE(MEMORY_MAX_INDEX, ==, MEMORY_AT(0,3))

  if(test_loop < 4) test_counter--;
  test_loop++;
  MEMORY_AT_ADDRESS(arguments[0])--;
  break;

  default:
  MEMORY_AT_ADDRESS(arguments[0]) = MAX_VALUE;
  COLLECT_FINDINGS
  //----------------------
  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
resize_memory_to(MEMORY_AT_ADDRESS(arguments[0]));
#endif

#define DESCRIPTION \
Resizes the interpreter memory to the size specified in the first argument. \
Thus, this instruction can additionally trigger a memory limit trap.

#include "../internal/instruction_post_template.c"
