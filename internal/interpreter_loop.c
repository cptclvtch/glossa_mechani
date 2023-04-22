void interpreter_loop(INTERPRETER_MEMORY* interpreter)
{
  //------------Loop setup------------
  //Variable definition
  ADDRESS   head;
  ADDRESS   arguments[16];
  DATA_TYPE argument_index;
  DATA_TYPE instruction, is_valid_instruction, array_left;
  DATA_TYPE working_variable; //variable of the night
  #define VARIABLE_MODE
  #include "error_handling.c"
  #include "instructions.c"
  #ifdef CLT
  #include "interpreter_loop_readout.c"
  #endif
  #undef VARIABLE_MODE

  //Variable initialization
  SPECIFY_ADDRESS(head, 0,0)

  #ifdef CLT
  no_of_messages = 0;
  #endif

  #ifdef __labels_as_values__
  void* instruction_table[] = {
  #define NAME_MODE
  #define TURN_TO_LABEL
  #define ENUMERATE
  #include "instructions.c"
  };
  #endif
  
  //------------Loop body------------
  goto next_instruction;

  next_array:
    head.array++;
    head.index = 0;

  next_instruction:

    #include "instruction_check_and_set.c"
    #include "arguments/check_and_set.c"

    #ifdef CLT
    #include "interpreter_loop_readout.c"
    #endif

    GO_TO_INSTRUCTION

    #define IMPLEMENTATION_MODE
    #include "instructions.c"

    EMPTY_AND_DECAPITATE_INSTRUCTIONS

  advance_head:
  ADVANCE_HEAD
  goto next_instruction;

  DECAPITATE:;
}
