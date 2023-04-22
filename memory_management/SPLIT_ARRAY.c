#define NAME LABEL(SPLIT_ARRAY)
#define ARGUMENTS 1

#include "../internal/instruction_pre_template.c"

#ifdef TESTING

switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"

  {
    resize_memory_to(4);
    resize_array_to(4, 4);
    for(test_loop = 0; test_loop <= 4; test_loop++)
      MEMORY_AT(4, test_loop) = test_loop;
  }

  SPECIFY_ADDRESS(arguments[0], 4,2)
  break;

  case 1:
  {
    DATA_TYPE expected_array_values[] = {0,1};
    VERIFY_ARRAY_OF_VALUES(MEMORY_AT(4, test_iterator), ==, expected_array_values[test_iterator], 1)
    VERIFY_SINGLE_VALUE(MAX_INDEX_AT(4), ==, 1)
  }
  {
    DATA_TYPE expected_array_values[] = {2,3,4};
    VERIFY_ARRAY_OF_VALUES(MEMORY_AT(5, test_iterator), ==, expected_array_values[test_iterator], 2)
    VERIFY_SINGLE_VALUE(MAX_INDEX_AT(5), ==, 2)
  }
  COLLECT_FINDINGS
  //--------------------------
  #undef SUBTITLE
  #define SUBTITLE "Split at 0"

  {
    resize_memory_to(4);
    resize_array_to(4, 4);
    for(test_loop = 0; test_loop <= 4; test_loop++)
      MEMORY_AT(4, test_loop) = test_loop;
  }

  SPECIFY_ADDRESS(arguments[0], 4,0)
  break;

  default:
  {
    DATA_TYPE expected_array_values[] = {0,1,2,3,4};
    VERIFY_ARRAY_OF_VALUES(MEMORY_AT(4, test_iterator), ==, expected_array_values[test_iterator], 4)
    VERIFY_SINGLE_VALUE(MAX_INDEX_AT(4), ==, 4)
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
//INDEX_MOVEMEMT
if(arguments[0].index)
{
  resize_memory_to(MEMORY_MAX_INDEX + 1);

  resize_array_to(MEMORY_MAX_INDEX, MAX_INDEX_AT(arguments[0].array) - arguments[0].index);
  internal_overwrite_index_range(interpreter, arguments[0].array,
                                              arguments[0].index,
                                              MAX_INDEX_AT(arguments[0].array),
                                              MEMORY_MAX_INDEX,
                                              0);
  resize_array_to(arguments[0].array, arguments[0].index - 1);

  internal_move_array_range(interpreter, MEMORY_MAX_INDEX, MEMORY_MAX_INDEX, arguments[0].array + 1);

  //Unorthodox Head Movement
  if(head.array == arguments[0].array && head.index >= arguments[0].index)
    head.index -= arguments[0].index;

  head.array += head.array >= arguments[0].array;
}
#endif

#define DESCRIPTION \
Splits up an array at the specified location. The new array starts with the index specified. Splitting at 0 does nothing.

#include "../internal/instruction_post_template.c"
