#define VERIFY_ORDER_OF_RANGE_INDICES(first, last)\
if(first > last)    \
{                   \
  DATA_TYPE temporary = first;\
  first = last;     \
  last = temporary; \
}

#ifdef TESTING
#undef TITLE
#define TITLE "internal_move_array_range()"
POST_TITLE
//--------------------------
#undef SUBTITLE
#define SUBTITLE "Best Case Scenario"

retire_interpreter(interpreter);

setup_interpreter(interpreter);
resize_memory_to(4);
for(test_loop = 1; test_loop <= 4; test_loop++)
  resize_array_to(test_loop, test_loop);

internal_move_array_range(interpreter, 3, 4, 0);

{
  DATA_TYPE expected_array_max_indices[] = {3,4,0,1,2};
  VERIFY_ARRAY_OF_VALUES(MAX_INDEX_AT(test_iterator), ==, expected_array_max_indices[test_iterator], 4)
  COLLECT_FINDINGS
}
//--------------------------
resize_array_to(3, 3);
resize_array_to(4, 4);

#else
void internal_move_array_range(INTERPRETER_MEMORY* interpreter, DATA_TYPE move_first_index, DATA_TYPE move_last_index, DATA_TYPE move_to_index)
{
  //ARRAY_MOVEMENT
  DATA_TYPE* pointer_cache;
  #undef MAX_INDEX
  #define MAX_INDEX MEMORY_MAX_INDEX
  #undef SWAP_CORE
  #define SWAP_CORE SWAP(MAX_INDEX_AT(start + cache_index), MAX_INDEX_AT(start + to_index), swap_cache) \
                    SWAP(ARRAY_AT(start + cache_index).data, ARRAY_AT(start + to_index).data, pointer_cache)
  #include "move_range_template.c"
}
#endif

#ifdef TESTING
#undef TITLE
#define TITLE "internal_move_index_range()"
POST_TITLE
//--------------------------
#undef SUBTITLE
#define SUBTITLE "Best Case Scenario"

for(test_loop = 0; test_loop <= 4; test_loop++)
  MEMORY_AT(4, test_loop) = test_loop;

internal_move_index_range(interpreter, 4, 3, 4, 0);

{
  DATA_TYPE expected_array_values[] = {3,4,0,1,2};
  VERIFY_ARRAY_OF_VALUES(MEMORY_AT(4, test_iterator), ==, expected_array_values[test_iterator], 4)
  COLLECT_FINDINGS
}
//--------------------------
#else
void internal_move_index_range(INTERPRETER_MEMORY* interpreter, DATA_TYPE target_array, DATA_TYPE move_first_index, DATA_TYPE move_last_index, DATA_TYPE move_to_index)
{
  //INDEX_MOVEMENT
  if(target_array > MEMORY_MAX_INDEX) return;

  #undef MAX_INDEX
  #define MAX_INDEX MAX_INDEX_AT(target_array)
  #undef SWAP_CORE
  #define SWAP_CORE   SWAP(MEMORY_AT(target_array,start + cache_index), MEMORY_AT(target_array, start + to_index), swap_cache)
  #include "move_range_template.c"
}
#endif

#ifdef TESTING
#undef TITLE
#define TITLE "internal_overwrite_index_range()"
POST_TITLE
//--------------------------
#undef SUBTITLE
#define SUBTITLE "Best Case Scenario"
{
  DATA_TYPE test_array = 3;
  for(;test_array <= 4; test_array++)
    for(test_loop = 0; test_loop <= test_array; test_loop++)
      MEMORY_AT(test_array, test_loop) = test_loop;
}

internal_overwrite_index_range(interpreter, 3, 2,3, 4, 0);

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

internal_overwrite_index_range(interpreter, 4, 1,3, 4, 0);

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

internal_overwrite_index_range(interpreter, 4, 1,3, 4, 3);

{
  DATA_TYPE expected_array_values[] = {0,1,2,1,2};
  VERIFY_ARRAY_OF_VALUES(MEMORY_AT(4, test_iterator), ==, expected_array_values[test_iterator], 4)
  COLLECT_FINDINGS
}
retire_interpreter(interpreter);
//--------------------------
#else
void internal_overwrite_index_range(INTERPRETER_MEMORY* interpreter, DATA_TYPE copy_from_array, DATA_TYPE copy_first_index, DATA_TYPE copy_last_index, DATA_TYPE copy_to_array, DATA_TYPE copy_to_index)
{
  //INDEX_MOVEMENT
  if(copy_from_array == copy_to_array && copy_first_index == copy_to_index) return;

  DATA_TYPE loop = copy_last_index - copy_first_index;
  DATA_TYPE smaller_bound = MAX_INDEX_AT(copy_to_array) - copy_to_index;
  if(loop < smaller_bound) smaller_bound = loop;

  loop = smaller_bound;
  DATA_TYPE target = 0;
  DATA_TYPE increment = MAX_VALUE;
  if(copy_from_array == copy_to_array && copy_to_index < copy_first_index)
  {
    loop = 0;
    target = smaller_bound;
    increment = 1;
  }

  while(1)
  {
    MEMORY_AT(copy_to_array, copy_to_index + loop) = MEMORY_AT(copy_from_array, copy_first_index + loop);
    if(loop == target) break; else loop += increment;
  }
}
#endif

#define delete_index_range(from_array, start_index, end_index)  if(end_index < MAX_INDEX_AT(from_array)) internal_move_index_range(interpreter, from_array, end_index + 1, MAX_INDEX_AT(from_array), start_index); \
                                                                resize_array_to(from_array, MAX_INDEX_AT(from_array) - end_index + start_index - ((end_index - start_index) < MAX_INDEX_AT(from_array)));

#define delete_array_range(start_array, end_array)              if(end_array < MEMORY_MAX_INDEX) internal_move_array_range(interpreter, end_array + 1, MEMORY_MAX_INDEX, start_array); \
                                                                resize_memory_to(MEMORY_MAX_INDEX - end_array + start_array - ((end_array - start_array) < MEMORY_MAX_INDEX));
