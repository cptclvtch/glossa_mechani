argument_index = 0;

while(argument_index < INSTRUCTION_INFO_AT(instruction, NUMBER_OF_ARGUMENTS) )
{
  SPECIFY_ADDRESS(arguments[argument_index], head.array, head.index)

  switch(AT_HEAD_OFFSET(argument_index*ARGUMENT_SIZE + 1))
  {
    ADDRESS target;

    //Cases 
    #include "IMMEDIATE.c"
    
    #include "CURRENT_ARRAY.c"

    #include "POSITIVE_RELATIVE.c"

    #include "NEGATIVE_RELATIVE.c"

    default:
    #include "DIRECT.c"
  }
  
  argument_index++;
}