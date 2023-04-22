#define NAME LABEL(DELETE_INDEX_RANGE)
#define ARGUMENTS 2

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"
  resize_memory_to(1);
  resize_array_to(1, MEMORY_AT(0,3));

  SPECIFY_ADDRESS(arguments[0], 1,4)
  SPECIFY_ADDRESS(arguments[1], 1,5)
  break;

  case 1:
  VERIFY_SINGLE_VALUE(MAX_INDEX_AT(1), ==, MEMORY_AT(0,3) - 2)
  COLLECT_FINDINGS
  //---------------------------------

  #undef SUBTITLE
  #define SUBTITLE "Flipped range indices"
  resize_array_to(1, MEMORY_AT(0,3));

  SPECIFY_ADDRESS(arguments[0], 1, 5)
  SPECIFY_ADDRESS(arguments[1], 1, 4)
  break;

  case 2:
  VERIFY_SINGLE_VALUE(MAX_INDEX_AT(1), ==, MEMORY_AT(0,3) - 2)
  COLLECT_FINDINGS
  //---------------------------------

  #undef SUBTITLE
  #define SUBTITLE "Middle deletion"
  resize_array_to(1, MEMORY_AT(0,3));

  SPECIFY_ADDRESS(arguments[0], 1, 2)
  SPECIFY_ADDRESS(arguments[1], 1, 3)
  break;

  case 3:
  VERIFY_SINGLE_VALUE(MAX_INDEX_AT(1), ==, MEMORY_AT(0,3) - 2)
  COLLECT_FINDINGS
  //---------------------------------

  #undef SUBTITLE
  #define SUBTITLE "Whole range"
  resize_array_to(1, MEMORY_AT(0,3));

  SPECIFY_ADDRESS(arguments[0], 1, 0)
  SPECIFY_ADDRESS(arguments[1], 1, MEMORY_AT(0,3))
  break;

  default:
  VERIFY_SINGLE_VALUE(MAX_INDEX_AT(1), ==, 0)
  COLLECT_FINDINGS
  //---------------------------------

  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
//INDEX_MOVEMENT
VERIFY_ORDER_OF_RANGE_INDICES(arguments[0].index, arguments[1].index);
delete_index_range(arguments[0].array, arguments[0].index, arguments[1].index)

//Unorthodox Head Movement
if(arguments[0].array == head.array)
{
  working_variable = head.index;

  if(arguments[0].index <= head.index && head.index <= arguments[1].index)
  {
    working_variable = arguments[0].index;
    #ifndef TESTING
    goto next_instruction;
    #endif
  }

  if(head.index > arguments[1].index) working_variable -= 1 + arguments[1].index - arguments[0].index;

  head.index = working_variable;
}
#endif

#define DESCRIPTION \
Deletes the range of indices specified by the first two arguments. \
The range cannot end with the last index. \
The range needs to belong to a single array, but will work even if the second argument is from a different array. \
If the head is contained in the index range, it will be placed immediately after it.

#include "../internal/instruction_post_template.c"
