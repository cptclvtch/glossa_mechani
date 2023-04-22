#include "array.c"

#ifndef DONT_FILL_IN
#define DONT_FILL_IN 0
#endif
#ifndef FILL_IN
#define FILL_IN 1
#endif

#define GRID_RESIZE_SUCCESSFUL       ARRAY_RESIZE_SUCCESSFUL
#define GRID_RESIZE_TOO_BIG         ARRAY_RESIZE_TOO_BIG
#define GRID_RESIZE_UNTARGETABLE    ARRAY_RESIZE_UNTARGETABLE

#ifdef TESTING
  #undef TITLE
  #define TITLE "setup_grid()"
  POST_TITLE
  //--------------------------------
  #undef SUBTITLE
  #define SUBTITLE "With no Fill In"
  GRID test_grid = setup_grid(0, DONT_FILL_IN);
  VERIFY_SINGLE_VALUE(test_grid.data, !=, MEMORY_ALLOCATION_FAILED)
  VERIFY_SINGLE_VALUE(test_grid.max_index, ==, 0)

  COLLECT_FINDINGS
  //--------------------------------
  #undef SUBTITLE
  #define SUBTITLE "With Fill In"
  test_grid = setup_grid(0, FILL_IN);
  VERIFY_SINGLE_VALUE(test_grid.data, !=, MEMORY_ALLOCATION_FAILED)
  VERIFY_SINGLE_VALUE(test_grid.max_index, ==, 0)

  VERIFY_SINGLE_VALUE(test_grid.data[0].data, !=, MEMORY_ALLOCATION_FAILED)

  COLLECT_FINDINGS
#else
GRID setup_grid(DATA_TYPE max_index, DATA_TYPE fill_in)
{
  GRID new_allocation;
  new_allocation.max_index = max_index;
  new_allocation.data = ALLOCATE_MEMORY(new_allocation.max_index, ARRAY)

  if(new_allocation.data != MEMORY_ALLOCATION_FAILED && fill_in)
  {
    DATA_TYPE loop = 0;
    for(; loop <= new_allocation.max_index; loop++)
    {
      new_allocation.data[loop] = setup_array(0);
    }
  }

  return new_allocation;
}
#endif

#ifdef TESTING
  #undef TITLE
  #define TITLE "retire_grid()"
  POST_TITLE
  //-------------------------------
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"
  result = retire_grid(&test_grid);

  VERIFY_SINGLE_VALUE(test_grid.data, ==, MEMORY_ALLOCATION_FAILED)
  VERIFY_SINGLE_VALUE(result, ==, DEALLOCATION_SUCCESSFUL)

  COLLECT_FINDINGS

  //---------------------------
  #undef SUBTITLE
  #define SUBTITLE "Repeated usage"

  result = retire_grid(&test_grid);

  VERIFY_SINGLE_VALUE(test_grid.data, ==, MEMORY_ALLOCATION_FAILED)
  VERIFY_SINGLE_VALUE(result, ==, DEALLOCATION_SUCCESSFUL)

  COLLECT_FINDINGS
#else
DATA_TYPE retire_grid(GRID* target)
{
  DATA_TYPE loop = 0;
  DATA_TYPE result = 0;

  if(target->data != MEMORY_ALLOCATION_FAILED)
  {
    while(loop <= target->max_index)
    {
      if(target->data[loop].data != MEMORY_ALLOCATION_FAILED)
      {
        result = DEALLOCATE_MEMORY(target->data[loop].data, target->data[loop].max_index)
        if(result != DEALLOCATION_SUCCESSFUL) return !DEALLOCATION_SUCCESSFUL;
        target->data[loop].data = (DATA_TYPE*)MEMORY_ALLOCATION_FAILED;
      }
      loop++;
    }

    result = DEALLOCATE_MEMORY(target->data, target->max_index)
    if(result != DEALLOCATION_SUCCESSFUL) return !DEALLOCATION_SUCCESSFUL;
    target->data = (ARRAY*)MEMORY_ALLOCATION_FAILED;
  }

  target->max_index = 0;

  return DEALLOCATION_SUCCESSFUL;
}
#endif

#ifdef TESTING
  #undef TITLE
  #define TITLE "resize_grid()"
  POST_TITLE
  //--------------------------------
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"

  test_grid = setup_grid(0,FILL_IN);
  resize_grid(&test_grid, 1);
  VERIFY_SINGLE_VALUE(test_grid.max_index, ==, 1);

  COLLECT_FINDINGS
  ADD_SEPARATOR
#else
DATA_TYPE resize_grid(GRID* arrays, DATA_TYPE new_max_index)
{
  if(arrays->data == MEMORY_ALLOCATION_FAILED) return MEMORY_RESIZE_UNTARGETABLE;
  if(new_max_index == arrays->max_index) return MEMORY_RESIZE_SUCCESSFUL;

  GRID new_allocation = setup_grid(new_max_index, 0);
  if(new_allocation.data == MEMORY_ALLOCATION_FAILED) return MEMORY_RESIZE_TOO_BIG;

  DATA_TYPE loop = 0;
  DATA_TYPE new_is_smaller = new_allocation.max_index < arrays->max_index;
  DATA_TYPE length = new_allocation.max_index * new_is_smaller  +  arrays->max_index * !new_is_smaller;

  for(; loop <= length; loop++)
  {
    new_allocation.data[loop].max_index = arrays->data[loop].max_index;
    new_allocation.data[loop].data = arrays->data[loop].data;
  }

  //allocate memory for new_allocation pointers if size increased
  for(loop = arrays->max_index + 1; loop <= new_max_index; loop++)
  {
    new_allocation.data[loop] = setup_array(0);

    if(new_allocation.data[loop].data == MEMORY_ALLOCATION_FAILED)
    {
      for(--loop; loop > arrays->max_index; loop--)
      {
        DEALLOCATE_MEMORY(new_allocation.data[loop].data, new_allocation.data[loop].max_index)
      }
      DEALLOCATE_MEMORY(new_allocation.data, new_max_index)

      return MEMORY_RESIZE_TOO_BIG;
    }
  }

  for(loop = new_allocation.max_index + 1; loop <= arrays->max_index; loop++)
  {
    retire_array(&arrays->data[loop]);
  }

  DEALLOCATE_MEMORY(arrays->data, arrays->max_index);

  arrays->max_index = new_allocation.max_index;
  arrays->data = new_allocation.data;

  return 0;
}
#endif
