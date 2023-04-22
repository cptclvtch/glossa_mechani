#define NAME LABEL(RESIZE_ARRAY_TO)
#define ARGUMENTS 2

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"
  SPECIFY_ADDRESS(arguments[0], 0, 1)
  SPECIFY_ADDRESS(arguments[1], 0, 3)
  break;

  case 1:
  VERIFY_SINGLE_VALUE(MAX_INDEX_AT(MEMORY_AT_ADDRESS(arguments[0])), ==, MEMORY_AT_ADDRESS(arguments[1]))
  COLLECT_FINDINGS

  test_counter++;
  SPECIFY_ADDRESS(arguments[0], 0, 4)

  case 2:
  #undef SUBTITLE
  #define SUBTITLE "Invalid resizes"

  if(test_loop < 4) test_counter--;
  test_loop++;
  MEMORY_AT(0,4)--;
  break;

  default:
  MEMORY_AT(0,4) = MAX_VALUE;
  COLLECT_FINDINGS
  //----------------------
  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
if(MEMORY_AT_ADDRESS(arguments[0]) <= MEMORY_MAX_INDEX)
{
  resize_array_to(MEMORY_AT_ADDRESS(arguments[0]), MEMORY_AT_ADDRESS(arguments[1]));
}
#endif

#define DESCRIPTION \
Resizes the array specified in the first argument to the size specified in the second argument. \
Thus, this instruction can additionally trigger a memory limit trap.

#include "../internal/instruction_post_template.c"
