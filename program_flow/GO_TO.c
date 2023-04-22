#define NAME LABEL(GO_TO)
#define ARGUMENTS 2

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"
  SPECIFY_ADDRESS(arguments[0], 0,1)
  SPECIFY_ADDRESS(arguments[1], 0,2)
  break;

  case 1:
  VERIFY_SINGLE_VALUE(head.array, ==, 0)
  VERIFY_SINGLE_VALUE(head.index, ==, 1)
  COLLECT_FINDINGS
  //----------------------
  #undef SUBTITLE
  #define SUBTITLE "Restricted array access"
  SPECIFY_ADDRESS(arguments[0], 0,0)
  SPECIFY_ADDRESS(arguments[1], 0,1)
  break;

  case 2:
  VERIFY_SINGLE_VALUE(head.array, ==, 9999)
  COLLECT_FINDINGS
  //----------------------
  #undef SUBTITLE
  #define SUBTITLE "Restricted index access"
  SPECIFY_ADDRESS(arguments[0], 0,1)
  SPECIFY_ADDRESS(arguments[1], 0,0)
  break;

  default:
  VERIFY_SINGLE_VALUE(head.index, ==, 9999)
  COLLECT_FINDINGS
  //----------------------
  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
head.array = MEMORY_AT_ADDRESS(arguments[0]);
head.index = MEMORY_AT_ADDRESS(arguments[1]);
#endif

#ifdef CORE_IMPLEMENTATION_ONLY
#undef IMPLEMENTATION_MODE
#endif

#ifdef IMPLEMENTATION_MODE
goto next_instruction;

#define REDEF_IMPLEMENTATION_MODE
#undef IMPLEMENTATION_MODE
#endif

#define DESCRIPTION \
Places the head at the array specified by the first argument and the index specified by the second argument.

#include "../internal/instruction_post_template.c"
