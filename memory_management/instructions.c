#ifdef GENERATE_DOCUMENTATION
#undef DOCUMENTATION_SECTION
#define DOCUMENTATION_SECTION Memory Management
#include "../internal/documentation_header.c"
#endif

#include "RESIZE_MEMORY_TO.c"
#include "GET_MEMORY_MAX_INDEX.c"

#include "RESIZE_ARRAY_TO.c"
#include "GET_ARRAY_MAX_INDEX.c"

#include "DELETE_ARRAY_RANGE.c"
#include "DELETE_INDEX_RANGE.c"

#include "COPY_ARRAY_RANGE.c"
#include "COPY_INDEX_RANGE.c"
#include "OVERWRITE.c"
#include "OVERWRITE_INDEX_RANGE.c"

#include "MOVE_ARRAY_RANGE.c"
#include "MOVE_INDEX_RANGE.c"

#include "SPLIT_ARRAY.c"
#include "CONJOIN_ARRAY_RANGE.c"

#ifdef GENERATE_DOCUMENTATION
</details>
#endif

#ifdef TESTING
ADD_SEPARATOR
#endif
