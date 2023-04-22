
#ifdef TESTING
  #undef TITLE
  #define TITLE "retire_interpreter()"
  POST_TITLE
  //--------------------------
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"

  interpreter->memory = setup_grid(0,FILL_IN);
  interpreter->instruction_info = setup_grid(NUMBER_OF_CORE_INSTRUCTIONS - 1,FILL_IN);

  result = retire_interpreter(interpreter);
  VERIFY_SINGLE_VALUE(interpreter->memory.data, ==, MEMORY_ALLOCATION_FAILED)
  VERIFY_SINGLE_VALUE(interpreter->instruction_info.data, ==, MEMORY_ALLOCATION_FAILED)
  VERIFY_SINGLE_VALUE(result, ==, DEALLOCATION_SUCCESSFUL)

  COLLECT_FINDINGS

  //---------------------------
  #undef SUBTITLE
  #define SUBTITLE "Repeated usage"

  result = retire_interpreter(interpreter);
  VERIFY_SINGLE_VALUE(interpreter->memory.data, ==, MEMORY_ALLOCATION_FAILED)
  VERIFY_SINGLE_VALUE(result, ==, DEALLOCATION_SUCCESSFUL)

  COLLECT_FINDINGS
#else
DATA_TYPE retire_interpreter(INTERPRETER_MEMORY* interpreter)
{
  if(retire_grid(&interpreter->memory) != DEALLOCATION_SUCCESSFUL) return !DEALLOCATION_SUCCESSFUL;

  if(retire_grid(&interpreter->instruction_info) != DEALLOCATION_SUCCESSFUL) return !DEALLOCATION_SUCCESSFUL;

  return DEALLOCATION_SUCCESSFUL;
}
#endif

#ifdef TESTING
  #undef TITLE
  #define TITLE "resize_instruction_info_to()"
  POST_TITLE
  //-------------------
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"

  interpreter->instruction_info = setup_grid(NUMBER_OF_CORE_INSTRUCTIONS + 10,FILL_IN);
  result = resize_instruction_info_to(interpreter, NUMBER_OF_CORE_INSTRUCTIONS - 1);
  VERIFY_SINGLE_VALUE(interpreter->instruction_info.max_index, ==, NUMBER_OF_CORE_INSTRUCTIONS - 1)
  VERIFY_SINGLE_VALUE(result, ==, GRID_RESIZE_SUCCESSFUL)

  COLLECT_FINDINGS
  //-------------------
  #undef SUBTITLE
  #define SUBTITLE "Smaller than core instructions"

  result = resize_instruction_info_to(interpreter, 0);
  VERIFY_SINGLE_VALUE(interpreter->instruction_info.max_index, ==, NUMBER_OF_CORE_INSTRUCTIONS - 1)
  VERIFY_SINGLE_VALUE(result, ==, GRID_RESIZE_UNTARGETABLE)

  COLLECT_FINDINGS
#else
DATA_TYPE resize_instruction_info_to(INTERPRETER_MEMORY* interpreter, DATA_TYPE max_index)
{
  if(max_index < NUMBER_OF_CORE_INSTRUCTIONS - 1) return GRID_RESIZE_UNTARGETABLE;

  return resize_grid(&(interpreter->instruction_info), max_index);
}
#endif

#ifdef TESTING
  #undef TITLE
  #define TITLE "setup_interpreter()"
  POST_TITLE
  //-------------------------------
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"

  setup_interpreter(interpreter);
  VERIFY_SINGLE_VALUE(MEMORY_DATA, !=, MEMORY_ALLOCATION_FAILED)
  VERIFY_SINGLE_VALUE(interpreter->instruction_info.data, !=, MEMORY_ALLOCATION_FAILED)

  COLLECT_FINDINGS

  ADD_SEPARATOR
#else
DATA_TYPE setup_interpreter(INTERPRETER_MEMORY* interpreter)
{
  //INSTRUCTION INFO
  interpreter->instruction_info = setup_grid(NUMBER_OF_CORE_INSTRUCTIONS - 1, DONT_FILL_IN);

  DATA_TYPE temp_arg_sizes[] = {
    #define ARGUMENTS_MODE
    #define ENUMERATE
    #include "../instructions.c"
  };

  DATA_TYPE loop = 0;
  for(; loop <= interpreter->instruction_info.max_index; loop++)
  {
    interpreter->instruction_info.data[loop] = setup_array(NUMBER_OF_INSTRUCTION_INFO_ELEMENTS - 1);
    interpreter->instruction_info.data[loop].data[NUMBER_OF_ARGUMENTS] = temp_arg_sizes[loop];
  }

  //MEMORY
  MEMORY_MAX_INDEX = 0;
  interpreter->memory = setup_grid(MEMORY_MAX_INDEX, FILL_IN);

  if(MEMORY_DATA == MEMORY_ALLOCATION_FAILED)
  {
    #ifdef CLT
    PRINT("\nCouldn't allocate memory to 'MEMORY_DATA'.\n")
    #endif
    retire_interpreter(interpreter);
    return 0;
  }

  if(ARRAY_AT(0).data == MEMORY_ALLOCATION_FAILED)
  {
    #ifdef CLT
    PRINT("\nCouldn't allocate memory for 'ARRAY_AT(0).data'.\n")
    #endif
    retire_interpreter(interpreter);
    return 0;
  }

  return 1;
}
#endif

#ifdef TESTING
  #undef TITLE
  #define TITLE "load_up_array()"
  POST_TITLE
  //-------------------------------
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"

  DATA_TYPE test[] = {0,1,2,3,4,5};
  load_up_array(interpreter, 0, test);

  VERIFY_ARRAY_OF_VALUES(MEMORY_AT(0,test_iterator), ==, test[test_iterator], 5)

  COLLECT_FINDINGS

  retire_interpreter(interpreter);
  setup_interpreter(interpreter);

#else
void _load_up_array(INTERPRETER_MEMORY* interpreter, DATA_TYPE target, DATA_TYPE array[], DATA_TYPE array_max_index)
{
  if(MEMORY_DATA == MEMORY_ALLOCATION_FAILED) return;
  if(ARRAY_AT(target).data == MEMORY_ALLOCATION_FAILED) return;

  if(resize_array(&ARRAY_AT(target), array_max_index) != ARRAY_RESIZE_SUCCESSFUL) return;

  DATA_TYPE loop = 0;

  for(; loop <= array_max_index; loop++)
  {
    MEMORY_AT(target, loop) = array[loop];
  }
}

#define load_up_array(interpreter, target, array) _load_up_array(interpreter, target, array, sizeof(array)/sizeof(DATA_TYPE) - 1)
#endif
