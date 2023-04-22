#define NAME LABEL(GET_ARRAY_MAX_INDEX)
#define ARGUMENTS 2

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Best Case Scenario"
  SPECIFY_ADDRESS(arguments[0], 0,1)
  SPECIFY_ADDRESS(arguments[1], 0,5)
  break;

  default:
  VERIFY_SINGLE_VALUE(MEMORY_AT_ADDRESS(arguments[1]), ==, MAX_INDEX_AT(MEMORY_AT_ADDRESS(arguments[0])))
  COLLECT_FINDINGS
  //----------------------
  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
MEMORY_AT_ADDRESS(arguments[1]) = MAX_INDEX_AT(MEMORY_AT_ADDRESS(arguments[0]));
#endif

#define DESCRIPTION \
Places the size of the array specified by the second argument into the first argument.

#include "../internal/instruction_post_template.c"
