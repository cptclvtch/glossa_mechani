#ifndef DATA_TYPE
#define DATA_TYPE uint32_t
#endif

#ifndef MEMORY_ALLOCATION_FAILED
#define MEMORY_ALLOCATION_FAILED (DATA_TYPE*)-1
#endif

#define ARRAY_RESIZE_SUCCESSFUL 0
#define ARRAY_RESIZE_TOO_BIG 1
#define ARRAY_RESIZE_UNTARGETABLE 2

#ifdef TESTING
  #undef TITLE
  #define TITLE "setup_array()"
  POST_TITLE
  //-------------------------------
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"

  ARRAY test_array = setup_array(0);

  VERIFY_SINGLE_VALUE(test_array.data, !=, MEMORY_ALLOCATION_FAILED)
  VERIFY_SINGLE_VALUE(test_array.max_index, ==, 0)

  COLLECT_FINDINGS
#else
ARRAY setup_array(DATA_TYPE max_index)
{
  ARRAY new_allocation;
  new_allocation.max_index = max_index;
  new_allocation.data = ALLOCATE_MEMORY( new_allocation.max_index, DATA_TYPE)

  return new_allocation;
}
#endif

#ifdef TESTING
  #undef TITLE
  #define TITLE "retire_array()"
  POST_TITLE
  //------------------------------
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"

  result = retire_array(&test_array);

  VERIFY_SINGLE_VALUE(test_array.data, ==, MEMORY_ALLOCATION_FAILED)
  VERIFY_SINGLE_VALUE(result, ==, DEALLOCATION_SUCCESSFUL)

  COLLECT_FINDINGS

  //------------------------------
  #undef SUBTITLE
  #define SUBTITLE "Repeated usage"

  result = retire_array(&test_array);

  VERIFY_SINGLE_VALUE(test_array.data, ==, MEMORY_ALLOCATION_FAILED)
  VERIFY_SINGLE_VALUE(result, ==, DEALLOCATION_SUCCESSFUL)

  COLLECT_FINDINGS

#else
DATA_TYPE retire_array(ARRAY* target)
{
  DATA_TYPE result = DEALLOCATION_SUCCESSFUL;

  if(target->data != MEMORY_ALLOCATION_FAILED)
  {
    result = DEALLOCATE_MEMORY(target->data, target->max_index)
    target->data = (DATA_TYPE*)MEMORY_ALLOCATION_FAILED;
  }
  return result;
}
#endif

#ifdef TESTING
  #undef TITLE
  #define TITLE "resize_array()"
  POST_TITLE
  //-------------------------------
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"

  test_array = setup_array(0);
  result = resize_array(&test_array, 4);

  VERIFY_SINGLE_VALUE(result, ==, ARRAY_RESIZE_SUCCESSFUL)
  VERIFY_SINGLE_VALUE(test_array.max_index, ==, 4)

  COLLECT_FINDINGS
  ADD_SEPARATOR
#else
DATA_TYPE resize_array(ARRAY* target, DATA_TYPE new_max_index)
{
  if(target->data == MEMORY_ALLOCATION_FAILED) return ARRAY_RESIZE_UNTARGETABLE;
  if(new_max_index == target->max_index) return ARRAY_RESIZE_SUCCESSFUL;

  ARRAY new_allocation = setup_array(new_max_index);

  if(new_allocation.data == MEMORY_ALLOCATION_FAILED) return ARRAY_RESIZE_TOO_BIG;

  DATA_TYPE loop = 0;
  DATA_TYPE new_is_smaller = new_allocation.max_index < target->max_index;
  DATA_TYPE length = new_allocation.max_index * new_is_smaller  +  target->max_index * !new_is_smaller;

  for(;loop <= length; loop++)
  {
    new_allocation.data[loop] = target->data[loop];
  }

  DEALLOCATE_MEMORY( target->data, target->max_index);

  target->max_index = new_allocation.max_index;
  target->data = new_allocation.data;

  return ARRAY_RESIZE_SUCCESSFUL;
}
#endif
