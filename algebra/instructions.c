#ifdef TESTING
retire_interpreter(interpreter);
setup_interpreter(interpreter);
resize_array_to(0, 19);
MEMORY_AT(0, 0) = 9999;
MEMORY_AT(0, 1) = 0;
MEMORY_AT(0, 2) = 1;
MEMORY_AT(0, 3) = 5;
MEMORY_AT(0, 4) = MAX_VALUE;
MEMORY_AT(0, 5) = 0;
MEMORY_AT(0, 6) = 0;

SPECIFY_ADDRESS(arguments[2], 0,5)
#endif

#ifdef GENERATE_DOCUMENTATION
#undef DOCUMENTATION_SECTION
#define DOCUMENTATION_SECTION Algebra
#include "../internal/documentation_header.c"
#endif

#include "ADD.c"
#include "SUBTRACT.c"
#include "MULTIPLY.c"
#include "DIVIDE.c"

#include "BITWISE_AND.c"
#include "BITWISE_OR.c"
#include "BITWISE_XOR.c"
#include "BITWISE_NOT.c"
#include "LOGICAL_SHIFT.c"

#include "AND.c"
#include "OR.c"
#include "NOT.c"

#include "EQUALS.c"
#include "GREATER_THAN.c"
#include "LESS_THAN.c"

#ifndef TESTING
#include "SET_RANDOM_SEED.c"
#endif
#include "GET_RANDOM.c"

#ifdef GENERATE_DOCUMENTATION
</details>
#endif

#ifdef TESTING
ADD_SEPARATOR
#endif
