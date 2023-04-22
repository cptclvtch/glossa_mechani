#define NAME LABEL(DELETE_ARRAY_RANGE)
#define ARGUMENTS 2

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"
  SPECIFY_ADDRESS(arguments[0], 3,0)
  SPECIFY_ADDRESS(arguments[1], 4,0)
  break;

  case 1:
  VERIFY_SINGLE_VALUE(MEMORY_MAX_INDEX, ==, MEMORY_AT(0,3) - 2)
  COLLECT_FINDINGS
  //---------------------------------

  #undef SUBTITLE
  #define SUBTITLE "Flipped range indices"
  resize_memory_to(MEMORY_AT(0,3));

  SPECIFY_ADDRESS(arguments[0], 3, 0)
  SPECIFY_ADDRESS(arguments[1], 2, 0)
  break;

  case 2:
  VERIFY_SINGLE_VALUE(MEMORY_MAX_INDEX, ==, MEMORY_AT(0,3) - 2)
  COLLECT_FINDINGS
  //---------------------------------

  #undef SUBTITLE
  #define SUBTITLE "Middle deletion"
  resize_memory_to(MEMORY_AT(0,3));

  SPECIFY_ADDRESS(arguments[0], 2, 0)
  SPECIFY_ADDRESS(arguments[1], 3, 0)
  break;

  case 3:
  VERIFY_SINGLE_VALUE(MEMORY_MAX_INDEX, ==, MEMORY_AT(0,3) - 2)
  COLLECT_FINDINGS
  //---------------------------------

  #undef SUBTITLE
  #define SUBTITLE "Range of width 1"
  resize_memory_to(MEMORY_AT(0,3));

  SPECIFY_ADDRESS(arguments[0], 3, 0)
  SPECIFY_ADDRESS(arguments[1], 3, 0)
  break;

  case 4:
  VERIFY_SINGLE_VALUE(MEMORY_MAX_INDEX, ==, MEMORY_AT(0,3) - 1)
  COLLECT_FINDINGS
  //---------------------------------

  #undef SUBTITLE
  #define SUBTITLE "Whole range"
  resize_memory_to(MEMORY_AT(0,3));

  SPECIFY_ADDRESS(arguments[0], 0, 0)
  SPECIFY_ADDRESS(arguments[1], MEMORY_AT(0,3), 0)
  break;

  default:
  VERIFY_SINGLE_VALUE(MEMORY_MAX_INDEX, ==, 0)
  COLLECT_FINDINGS
  //---------------------------------

  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
//ARRAY_MOVEMENT
VERIFY_ORDER_OF_RANGE_INDICES(arguments[0].array, arguments[1].array)
delete_array_range(arguments[0].array, arguments[1].array)

//Unorthodox Head Movement
if(arguments[0].array <= head.array && head.array <= arguments[1].array)
{
  head.array = arguments[0].array;
  head.index = 0;
  #ifndef TESTING
  goto next_instruction;
  #endif
}

if(head.array > arguments[1].array)
  head.array -= 1 + arguments[1].array - arguments[0].array;
#endif

#define DESCRIPTION \
Deletes the range of arrays specified by the first two arguments. \
The range cannot end with the last array. \
If the head is contained in the array range, it will be placed immediately after it, with index 0.

#include "../internal/instruction_post_template.c"
