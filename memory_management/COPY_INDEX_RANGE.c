#define NAME LABEL(COPY_INDEX_RANGE)
#define ARGUMENTS 3

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"

  {
    DATA_TYPE test_array = 3;
    for(; test_array <= 4; test_array++)
    {
      resize_array_to(test_array, test_array);
      for(test_loop = 0; test_loop <= test_array; test_loop++)
        MEMORY_AT(test_array, test_loop) = test_loop;
    }
  }

  SPECIFY_ADDRESS(arguments[0], 4,2)
  SPECIFY_ADDRESS(arguments[1], 4,3)
  SPECIFY_ADDRESS(arguments[2], 4,1)
  break;

  case 1:
  {
    DATA_TYPE expected_array_values[] = {0,2,3,1,2,3,4};
    VERIFY_ARRAY_OF_VALUES(MEMORY_AT(4, test_iterator), ==, expected_array_values[test_iterator], 6)
    VERIFY_SINGLE_VALUE(MAX_INDEX_AT(4), ==, 6)
    COLLECT_FINDINGS
  }
  //--------------------------
  #undef SUBTITLE
  #define SUBTITLE "Flipped range indices"

  resize_array_to(4, 4);
  for(test_loop = 0; test_loop <= 4; test_loop++)
    MEMORY_AT(4, test_loop) = test_loop;

  SPECIFY_ADDRESS(arguments[0], 4,3)
  SPECIFY_ADDRESS(arguments[1], 4,2)
  SPECIFY_ADDRESS(arguments[2], 4,1)
  break;

  case 2:
  {
    DATA_TYPE expected_array_values[] = {0,2,3,1,2,3,4};
    VERIFY_ARRAY_OF_VALUES(MEMORY_AT(4, test_iterator), ==, expected_array_values[test_iterator], 6)
    VERIFY_SINGLE_VALUE(MAX_INDEX_AT(4), ==, 6)
    COLLECT_FINDINGS
  }

  //--------------------------
  #undef SUBTITLE
  #define SUBTITLE "Different arrays"

  resize_array_to(4, 4);
  for(test_loop = 0; test_loop <= 4; test_loop++)
    MEMORY_AT(4, test_loop) = test_loop;

  SPECIFY_ADDRESS(arguments[0], 3,2)
  SPECIFY_ADDRESS(arguments[1], 3,3)
  SPECIFY_ADDRESS(arguments[2], 4,1)
  break;

  default:
  {
    DATA_TYPE expected_array_values[] = {0,2,3,1,2,3,4};
    VERIFY_ARRAY_OF_VALUES(MEMORY_AT(4, test_iterator), ==, expected_array_values[test_iterator], 6)
    VERIFY_SINGLE_VALUE(MAX_INDEX_AT(4), ==, 6)
    VERIFY_SINGLE_VALUE(MAX_INDEX_AT(3), ==, 3)
    COLLECT_FINDINGS
  }
  //----------------------
  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
//INDEX_MOVEMENT
{
  VERIFY_ORDER_OF_RANGE_INDICES(arguments[0].index, arguments[1].index)
  DATA_TYPE range_length = 1 + arguments[1].index - arguments[0].index;

  DATA_TYPE old_max_index = MAX_INDEX_AT(arguments[2].array);
  resize_array_to(arguments[2].array, old_max_index + range_length);

  internal_overwrite_index_range(interpreter, arguments[0].array,
                                              arguments[0].index,
                                              arguments[1].index,
                                              arguments[2].array,
                                              old_max_index + 1);

  internal_move_index_range(interpreter,  arguments[2].array,
                                          old_max_index + 1,
                                          MAX_INDEX_AT(arguments[2].array),
                                          arguments[2].index);

  //Unorthodox Head Movement
  if(head.array == arguments[2].array && head.index >= arguments[2].index) head.index += range_length;
}
#endif

#define DESCRIPTION \
Copies a range of data, as specified by the first two arguments, to the location specified by the third argument. \
The range needs to belong to a single array, but will work even if the second argument is from a different array.

#include "../internal/instruction_post_template.c"
