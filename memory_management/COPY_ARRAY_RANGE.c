#define NAME LABEL(COPY_ARRAY_RANGE)
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
  SPECIFY_ADDRESS(arguments[2], 2,0)
  break;

  case 1:
  {
    DATA_TYPE expected_array_max_indices[] = {5,1,3,4,2,3,4};
    VERIFY_ARRAY_OF_VALUES(MAX_INDEX_AT(test_iterator), ==, expected_array_max_indices[test_iterator], 6)
    COLLECT_FINDINGS
  }
  //---------------------------------

  #undef SUBTITLE
  #define SUBTITLE "Flipped range indices"

  resize_memory_to(4);
  for(test_loop = 1; test_loop <= 4; test_loop++)
    resize_array_to(test_loop, test_loop);

  SPECIFY_ADDRESS(arguments[0], 4,0)
  SPECIFY_ADDRESS(arguments[1], 3,0)
  SPECIFY_ADDRESS(arguments[2], 2,0)
  break;

  default:
  {
    DATA_TYPE expected_array_max_indices[] = {5,1,3,4,2,3,4};
    VERIFY_ARRAY_OF_VALUES(MAX_INDEX_AT(test_iterator), ==, expected_array_max_indices[test_iterator], 6)
    COLLECT_FINDINGS
  }
  //---------------------------------
  resize_memory_to(4);

  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
//ARRAY_MOVEMENT
{
  VERIFY_ORDER_OF_RANGE_INDICES(arguments[0].array, arguments[1].array)

  //abcde00
  DATA_TYPE old_max_index = MEMORY_MAX_INDEX;
  resize_memory_to(old_max_index + 1 + arguments[1].array - arguments[0].array);

  //abcdeBC
  DATA_TYPE array_iterator = 0;
  DATA_TYPE range_width = arguments[1].array - arguments[0].array;
  for(; array_iterator <= range_width; array_iterator++)
  {
    DATA_TYPE from_array = arguments[0].array + array_iterator;
    DATA_TYPE to_array = old_max_index + 1 + array_iterator;
    resize_array_to(to_array, MAX_INDEX_AT(from_array));
    internal_overwrite_index_range(interpreter,  from_array,
                                            0,
                                            MAX_INDEX_AT(from_array),
                                            to_array,
                                            0);
  }

  //abBCcde
  internal_move_array_range(interpreter, old_max_index + 1, MEMORY_MAX_INDEX, arguments[2].array);

  //Unorthodox Head Movement
  if(head.array >= arguments[2].array) head.array += 1 + arguments[1].array - arguments[0].array;
}
#endif

#define DESCRIPTION \
Copies array range specified in the first two arguments, to the location specified by the third argument. \
Thus, this instruction can additionally trigger a memory limit trap.

#include "../internal/instruction_post_template.c"
