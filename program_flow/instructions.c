#ifdef GENERATE_DOCUMENTATION
#undef DOCUMENTATION_SECTION
#define DOCUMENTATION_SECTION Program Flow
#include "../internal/documentation_header.c"
#endif

#ifndef TESTING
#include "EMPTY.c"
#include "DECAPITATE.c"
#include "IF.c"
#endif

#include "GO_TO.c"
#include "GO_TO_INDEX.c"
#include "SKIP.c"
#ifndef TESTING
#include "SET_HEAD.c"
#include "GET_HEAD.c"

#include "SET_ERROR_TRAP.c"
#include "GET_PLATFORM.c"
#endif
#include "GET_INSTRUCTION_INFO.c"

#ifdef GENERATE_DOCUMENTATION
</details>
#endif

#ifdef TESTING
ADD_SEPARATOR
#endif
