#define NAME LABEL(OVERWRITE_INDEX_RANGE)
#define ARGUMENTS 3

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"

  {
    resize_memory_to(4);
    resize_array_to(3, 3);
    resize_array_to(4, 4);
    DATA_TYPE test_array = 3;
    for(;test_array <= 4; test_array++)
      for(test_loop = 0; test_loop <= test_array; test_loop++)
        MEMORY_AT(test_array, test_loop) = test_loop;
  }

  SPECIFY_ADDRESS(arguments[0], 3,2)
  SPECIFY_ADDRESS(arguments[1], 3,3)
  SPECIFY_ADDRESS(arguments[2], 4,0)
  break;

  case 1:
  {
    DATA_TYPE expected_array_values[] = {2,3,2,3,4};
    VERIFY_ARRAY_OF_VALUES(MEMORY_AT(4, test_iterator), ==, expected_array_values[test_iterator], 4)
    COLLECT_FINDINGS
  }
  //--------------------------
  #undef SUBTITLE
  #define SUBTITLE "Same array copy - backward"

  for(test_loop = 0; test_loop <= 4; test_loop++)
    MEMORY_AT(4, test_loop) = test_loop;

  SPECIFY_ADDRESS(arguments[0], 4,1)
  SPECIFY_ADDRESS(arguments[1], 4,3)
  SPECIFY_ADDRESS(arguments[2], 4,0)
  break;

  case 2:
  {
    DATA_TYPE expected_array_values[] = {1,2,3,3,4};
    VERIFY_ARRAY_OF_VALUES(MEMORY_AT(4, test_iterator), ==, expected_array_values[test_iterator], 4)
    COLLECT_FINDINGS
  }
  //--------------------------
  #undef SUBTITLE
  #define SUBTITLE "Same array copy - forward"

  for(test_loop = 0; test_loop <= 4; test_loop++)
    MEMORY_AT(4, test_loop) = test_loop;

  SPECIFY_ADDRESS(arguments[0], 4,1)
  SPECIFY_ADDRESS(arguments[1], 4,3)
  SPECIFY_ADDRESS(arguments[2], 4,3)
  break;

  default:
  {
    DATA_TYPE expected_array_values[] = {0,1,2,1,2};
    VERIFY_ARRAY_OF_VALUES(MEMORY_AT(4, test_iterator), ==, expected_array_values[test_iterator], 4)
    COLLECT_FINDINGS
  }
  //----------------------
  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
VERIFY_ORDER_OF_RANGE_INDICES(arguments[0].index, arguments[1].index)
internal_overwrite_index_range(interpreter,  arguments[0].array,
                                        arguments[0].index,
                                        arguments[1].index,
                                        arguments[2].array,
                                        arguments[2].index);
#endif

#define DESCRIPTION \
Uses the range specified with the first two arguments to overwrite data at the location specified in the third argument. \
If the destination array is too short, the range becomes truncated to fit. \
The range needs to belong to a single array, but will work even if the second argument is from a different array.

#include "../internal/instruction_post_template.c"
