#define NAME LABEL(MOVE_ARRAY_RANGE)
#define ARGUMENTS 3

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"

  resize_memory_to(4);
  for(test_loop = 1; test_loop <= 4; test_loop++)
    resize_array_to(test_loop, test_loop);

  SPECIFY_ADDRESS(arguments[0], 3,0)
  SPECIFY_ADDRESS(arguments[1], 4,0)
  SPECIFY_ADDRESS(arguments[2], 1,0)
  break;

  case 1:
  {
    DATA_TYPE expected_array_max_indices[] = {5,3,4,1,2};
    VERIFY_ARRAY_OF_VALUES(MAX_INDEX_AT(test_iterator), ==, expected_array_max_indices[test_iterator], 4)
    COLLECT_FINDINGS
  }
  //----------------------
  #undef SUBTITLE
  #define SUBTITLE "Flipped range indices"

  SPECIFY_ADDRESS(arguments[0], 4,0)
  SPECIFY_ADDRESS(arguments[1], 3,0)
  SPECIFY_ADDRESS(arguments[2], 1,0)
  break;

  default:
  {
    DATA_TYPE expected_array_max_indices[] = {5,1,2,3,4};
    VERIFY_ARRAY_OF_VALUES(MAX_INDEX_AT(test_iterator), ==, expected_array_max_indices[test_iterator], 4)
    COLLECT_FINDINGS
  }
  //----------------------
  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
//ARRAY_MOVEMENT
{
  VERIFY_ORDER_OF_RANGE_INDICES(arguments[0].array, arguments[1].array)
  internal_move_array_range(interpreter, arguments[0].array, arguments[1].array, arguments[2].array);

  //Unorthodox Head Movement
  working_variable = head.array;

  if(arguments[0].array <= head.array && head.array <= arguments[1].array)
    working_variable += arguments[2].array - arguments[0].array;

  DATA_TYPE range_length = 1 + arguments[1].array - arguments[0].array;

  if(arguments[1].array < head.array && head.array <= arguments[2].array)
    working_variable -= range_length;

  if(arguments[2].array <= head.array && head.array < arguments[0].array)
    working_variable += range_length;

  head.array = working_variable;
}
#endif

#define DESCRIPTION \
Moves the array range specified in the first and second arguments to the position specified \
in the third argument.

#include "../internal/instruction_post_template.c"
