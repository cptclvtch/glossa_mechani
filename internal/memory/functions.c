#include "grid.c"

#define resize_memory_to(x)       if(x <= MAX_ARRAY_INDEX) if(resize_grid(&interpreter->memory, x) == MEMORY_RESIZE_TOO_BIG) {SET_ERROR(MEMORY_RESIZE_FAILED, head.array, head.index)}
#define resize_array_to(target,x) if(resize_array(&ARRAY_AT(target), x) == ARRAY_RESIZE_TOO_BIG) {SET_ERROR(ARRAY_RESIZE_FAILED, head.array, head.index)}

#ifdef TESTING
  #undef INDENT
  #define INDENT "     "
  TEST_PRINT("NON-INSTRUCTION TESTS")
  ADD_SEPARATOR
#endif
#include "interpreter.c"

#ifdef TESTING
TEST_PRINT("\n")
#undef INDENT
#define INDENT "     "
TEST_PRINT("INTERNAL INSTRUCTION TESTS")
ADD_SEPARATOR
#endif
#include "internal.c"

#ifdef TESTING
TEST_PRINT("\n")
#endif
