#define NAME LABEL(SKIP)
#define ARGUMENTS 2

#include "../internal/instruction_pre_template.c"

#ifdef TESTING
switch(test_counter)
{
  case 0:
  #undef SUBTITLE
  #define SUBTITLE "Forward index access"
  head.index = 0;
  SPECIFY_ADDRESS(arguments[0], 0,2)
  SPECIFY_ADDRESS(arguments[1], 0,1)
  array_left = MAX_VALUE;
  break;

  case 1:
  VERIFY_SINGLE_VALUE(head.index, ==, 1)
  COLLECT_FINDINGS
  //----------------------
  #undef SUBTITLE
  #define SUBTITLE "Backward index access"
  SPECIFY_ADDRESS(arguments[0], 0,2)
  SPECIFY_ADDRESS(arguments[1], 0,2)
  break;

  case 2:
  VERIFY_SINGLE_VALUE(head.index, ==, 0)
  COLLECT_FINDINGS
  //----------------------
  #undef SUBTITLE
  #define SUBTITLE "Lengthless skip"
  SPECIFY_ADDRESS(arguments[0], 0,1)
  SPECIFY_ADDRESS(arguments[1], 0,1)
  break;

  default:
  VERIFY_SINGLE_VALUE(head.index, ==, 0)
  COLLECT_FINDINGS

  #undef LABEL
  #define LABEL(name) name ## _test_finish
  goto NAME;
}
#endif

#ifdef IMPLEMENTATION_MODE
if(!MEMORY_AT_ADDRESS(arguments[0]))
{
  #ifndef CORE_IMPLEMENTATION_ONLY
  SET_ERROR(INDEX_ACCESS_FAILED, head.array, head.index + 2)
  #endif

  #ifdef CORE_IMPLEMENTATION_ONLY
  test_counter++; goto SKIP_tests;
  #else
  goto advance_head;
  #endif
}

head.index += MEMORY_AT_ADDRESS(arguments[0])*(1 - 2*(MEMORY_AT_ADDRESS(arguments[1])));
#endif

#ifdef CORE_IMPLEMENTATION_ONLY
#undef IMPLEMENTATION_MODE
#endif

#ifdef IMPLEMENTATION_MODE
goto next_instruction;

#undef OVERFLOWN_INDEX
#undef UNDERFLOWN_INDEX

#define REDEF_IMPLEMENTATION_MODE
#undef IMPLEMENTATION_MODE
#endif

#define DESCRIPTION \
Tells the head to move backwards or forwards from the current position. \
First argument determines distance, second argument determines direction( 0 for forwards, 1 and greater for backwards). \
An error will be emitted if the first argument has a value of 0.

#include "../internal/instruction_post_template.c"
