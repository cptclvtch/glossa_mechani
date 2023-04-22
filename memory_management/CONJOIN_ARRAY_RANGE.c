#define NAME LABEL(CONJOIN_ARRAY_RANGE)
#define ARGUMENTS 2

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"

  resize_memory_to(3);
  for(test_loop = 1; test_loop <= 3; test_loop++)
  {
    resize_array_to(test_loop, test_loop);
    DATA_TYPE inner_loop = 0;
    for(; inner_loop <= MAX_INDEX_AT(test_loop); inner_loop++)
      MEMORY_AT(test_loop, inner_loop) = inner_loop;
  }

  SPECIFY_ADDRESS(arguments[0], 1,0)
  SPECIFY_ADDRESS(arguments[1], 3,0)
  break;

  case 1:
  {
    DATA_TYPE expected_array_values[] = {0,1,0,1,2,0,1,2,3};
    VERIFY_ARRAY_OF_VALUES(MEMORY_AT(1, test_iterator), ==, expected_array_values[test_iterator], 6)
    COLLECT_FINDINGS
  }
  //---------------------------------

  #undef SUBTITLE
  #define SUBTITLE "Flipped range indices"

  resize_memory_to(3);
  for(test_loop = 1; test_loop <= 3; test_loop++)
  {
    resize_array_to(test_loop, test_loop);
    DATA_TYPE inner_loop = 0;
    for(; inner_loop <= MAX_INDEX_AT(test_loop); inner_loop++)
      MEMORY_AT(test_loop, inner_loop) = inner_loop;
  }

  SPECIFY_ADDRESS(arguments[0], 3,0)
  SPECIFY_ADDRESS(arguments[1], 1,0)
  break;

  default:
  {
    DATA_TYPE expected_array_values[] = {0,1,0,1,2,0,1,2,3};
    VERIFY_ARRAY_OF_VALUES(MEMORY_AT(1, test_iterator), ==, expected_array_values[test_iterator], 6)
    COLLECT_FINDINGS
  }
  //---------------------------------

  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
//ARRAY_MOVEMENT
if(arguments[0].array != arguments[1].array)
{
  VERIFY_ORDER_OF_RANGE_INDICES(arguments[0].array, arguments[1].array)

  DATA_TYPE new_array_size = MAX_INDEX_AT(arguments[0].array);
  DATA_TYPE write_index = new_array_size + 1;
  DATA_TYPE array_iterator = arguments[0].array + 1;
  for(; array_iterator <= arguments[1].array; array_iterator++)
  {
    new_array_size += 1 + MAX_INDEX_AT(array_iterator);
  }
  resize_array_to(arguments[0].array, new_array_size);

  array_iterator = arguments[0].array + 1;
  for(; array_iterator <= arguments[1].array; array_iterator++)
  {
    if(array_iterator == head.array) head.index += write_index;

    internal_overwrite_index_range(interpreter, array_iterator,
                                                0,
                                                MAX_INDEX_AT(array_iterator),
                                                arguments[0].array,
                                                write_index);
    write_index += MAX_INDEX_AT(array_iterator) + 1;
  }

  delete_array_range(arguments[0].array + 1, arguments[1].array)

  //Unorthodox Head Movement
  working_variable = head.array;

  if(arguments[0].array <= head.array && head.array <= arguments[1].array)  working_variable  = arguments[0].array;
  if(arguments[1].array <  head.array)                                      working_variable -= arguments[1].array - arguments[0].array;

  head.array = working_variable;
}
#endif

#define DESCRIPTION \
Turns a range of arrays into one array.

#include "../internal/instruction_post_template.c"
