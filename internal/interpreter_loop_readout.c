#ifdef VARIABLE_MODE
#undef VARIABLE_MODE
const char* core_instructions_text[] = {
  #define TURN_TO_STRING
  #define NAME_MODE
  #define ENUMERATE
  #include "instructions.c"
};
#define VARIABLE_MODE

const char* argument_type_text[] = {
  "NEGATIVE_RELATIVE",
  "POSITIVE_RELATIVE",
  "CURRENT_ARRAY",
  "IMMEDIATE"
};
#else

CHECK_FOR_LIMIT

PRINT("\n%u:%-5u %-21s", head.array, head.index, core_instructions_text[instruction])

argument_index = 0;
while(argument_index < INSTRUCTION_INFO_AT(instruction, NUMBER_OF_ARGUMENTS))
{
  #define PRINT_ARGUMENT(type, data) PRINT(" %-17" type " : %-10u", data, AT_HEAD_OFFSET(2 + argument_index*ARGUMENT_SIZE))
  
  DATA_TYPE type = AT_HEAD_OFFSET(1 + argument_index*ARGUMENT_SIZE);
  if(type > MAX_ARRAY_INDEX)
  {
    PRINT_ARGUMENT("s", argument_type_text[type - (DATA_TYPE)(NEGATIVE_RELATIVE)])
  }
  else
  {
    PRINT_ARGUMENT("u", AT_HEAD_OFFSET(1 + argument_index*ARGUMENT_SIZE))
  }
  #undef PRINT_ARGUMENT

  argument_index++;
}
argument_index = 0;

#endif