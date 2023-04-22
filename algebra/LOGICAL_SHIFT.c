#define NAME LABEL(LOGICAL_SHIFT)
#define ARGUMENTS 3

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Left"
  SPECIFY_ADDRESS(arguments[0], 0,3)
  SPECIFY_ADDRESS(arguments[1], 0,2)
  SPECIFY_ADDRESS(arguments[2], 0,1)
  result = MEMORY_AT_ADDRESS(arguments[0]) << MEMORY_AT_ADDRESS(arguments[1]);
  break;

  case 1:
  VERIFY_SINGLE_VALUE(MEMORY_AT_ADDRESS(arguments[0]), ==, result)
  COLLECT_FINDINGS
  MEMORY_AT_ADDRESS(arguments[0]) = 5;
  //----------------------

  #undef SUBTITLE
  #define SUBTITLE "Right"
  SPECIFY_ADDRESS(arguments[0], 0,3)
  SPECIFY_ADDRESS(arguments[1], 0,2)
  SPECIFY_ADDRESS(arguments[2], 0,2)
  result = MEMORY_AT_ADDRESS(arguments[0]) >> MEMORY_AT_ADDRESS(arguments[1]);
  break;

  default:
  VERIFY_SINGLE_VALUE(MEMORY_AT_ADDRESS(arguments[0]), ==, result)
  COLLECT_FINDINGS
  MEMORY_AT_ADDRESS(arguments[0]) = 5;
  //----------------------
  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
if(MEMORY_AT_ADDRESS(arguments[2]))
  MEMORY_AT_ADDRESS(arguments[0]) >>= MEMORY_AT_ADDRESS(arguments[1]);
else
  MEMORY_AT_ADDRESS(arguments[0]) <<= MEMORY_AT_ADDRESS(arguments[1]);

#ifdef CLT
PRINT(" = %u ",MEMORY_AT_ADDRESS(arguments[0]))
#endif
#endif

#define DESCRIPTION \
Performs a logical shift on the first argument by the amount specified in \
the second argument, in the direction specified in the third argument (0 for left and >0 for right).

#include "../internal/instruction_post_template.c"
