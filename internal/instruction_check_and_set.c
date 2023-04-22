if(head.array > MEMORY_MAX_INDEX) goto DECAPITATE;
if(head.index > MAX_INDEX_AT(head.array)) goto next_array;
array_left = MAX_INDEX_AT(head.array) - head.index;

instruction = AT_HEAD_OFFSET(0);

is_valid_instruction = instruction < NUMBER_OF_CORE_INSTRUCTIONS;
if(!is_valid_instruction)
{
  SET_ERROR(INVALID_INSTRUCTION, head.array, head.index)
}

instruction *= is_valid_instruction;

if(array_left < INSTRUCTION_INFO_AT(instruction, NUMBER_OF_ARGUMENTS)*ARGUMENT_SIZE)
{
  SET_ERROR(INVALID_INSTRUCTION, head.array, head.index)
  goto next_array;
}

if(instruction == SET_ERROR_TRAP)
{
  for(working_variable = 1; working_variable <= 3; working_variable++)
  {
    SPECIFY_ADDRESS(error_storage[working_variable-1] , head.array, head.index + 2*working_variable);
  }
}