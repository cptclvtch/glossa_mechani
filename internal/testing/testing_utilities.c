void read_out_array(ARRAY* array, DATA_TYPE pace)
{
  #ifdef CLT
  PRINT("\n")
  if(array->data == MEMORY_ALLOCATION_FAILED)
  {
    PRINT("ERROR: No memory allocated for 'array->data'\n")
    CHECK_FOR_LIMIT
  }
  else
  {
    PRINT("Max Index: %u", array->max_index)
    CHECK_FOR_LIMIT

    DATA_TYPE loop = 0;
    for(; loop <= array->max_index; loop++)
    {
      if(loop % pace == 0)
      {
        PRINT("\n")
        CHECK_FOR_LIMIT
      }
      PRINT_FN("0x%08x ", array->data[loop]);
    }
    PRINT("\n")
    ENTER_TO_CONTINUE
  }
  #endif
}

void read_out_grid(GRID* grid)
{
  #ifdef CLT
  PRINT("\nGrid Max Index: %u\n", grid->max_index)

  DATA_TYPE loop = 0;
  for(; loop <= grid->max_index; loop++)
  {
    read_out_array(&grid->data[loop], 10);
  }
  #endif
}

void read_out_memory(INTERPRETER_MEMORY* interpreter)
{
  ENTER_TO_CONTINUE
  #ifdef CLT
  CHECK_FOR_SKIP("main memory check", read_out_grid(&interpreter->memory);)
  CHECK_FOR_SKIP("instruction info check", read_out_grid(&interpreter->instruction_info);)
  #endif
}