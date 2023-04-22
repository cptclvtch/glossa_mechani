#define NAME LABEL(GET_INSTRUCTION_INFO)
#define ARGUMENTS 3

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"
  SPECIFY_ADDRESS(arguments[0], 0,1)
  SPECIFY_ADDRESS(arguments[1], 0,2)
  SPECIFY_ADDRESS(arguments[2], 0,5)
  break;

  case 1:
  VERIFY_SINGLE_VALUE(MEMORY_AT_ADDRESS(arguments[2]), ==, 0)
  COLLECT_FINDINGS
  //----------------------
  #undef SUBTITLE
  #define SUBTITLE "Invalid instruction"
  SPECIFY_ADDRESS(arguments[0], 0,0)
  break;

  default:
  VERIFY_SINGLE_VALUE(MEMORY_AT_ADDRESS(arguments[2]), ==, 0)
  COLLECT_FINDINGS
  //----------------------
  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
if(MEMORY_AT_ADDRESS(arguments[0]) < NUMBER_OF_CORE_INSTRUCTIONS)
{
  DATA_TYPE type = MEMORY_AT_ADDRESS(arguments[1]);
  if(type >= NUMBER_OF_INSTRUCTION_INFO_ELEMENTS)
  {
    type = NUMBER_OF_INSTRUCTION_INFO_ELEMENTS - 1;
  }

  MEMORY_AT_ADDRESS(arguments[2]) = INSTRUCTION_INFO_AT(MEMORY_AT_ADDRESS(arguments[0]), type);
}
else
{
  #ifndef CORE_IMPLEMENTATION_ONLY
  SET_ERROR(INVALID_INSTRUCTION, head.array, head.index + 4);
  #endif
}
#endif

#define DESCRIPTION \
Places the information according to the inquiry of the first two arguments (instruction code and information type respectively) into the third argument. \
The information types are: 0 or greater for the number of arguments.

#include "../internal/instruction_post_template.c"
