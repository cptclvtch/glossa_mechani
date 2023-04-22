#define NAME LABEL(GO_TO_INDEX)
#define ARGUMENTS 1

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"
  SPECIFY_ADDRESS(arguments[0], 0,2)
  break;

  case 1:
  VERIFY_SINGLE_VALUE(head.index, ==, MEMORY_AT_ADDRESS(arguments[0]))
  COLLECT_FINDINGS
  //----------------------
  #undef SUBTITLE
  #define SUBTITLE "Restricted index access"
  SPECIFY_ADDRESS(arguments[0], 0,0)
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
head.index = MEMORY_AT_ADDRESS(arguments[0]);
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
Places the head on the index specified in the first argument.

#include "../internal/instruction_post_template.c"
