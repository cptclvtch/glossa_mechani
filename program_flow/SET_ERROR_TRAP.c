#define NAME LABEL(SET_ERROR_TRAP)
#define ARGUMENTS 3

#include "../internal/instruction_pre_template.c"

#ifdef IMPLEMENTATION_MODE
for(working_variable = 0; working_variable <= 2; working_variable++)
  error_storage[working_variable] = arguments[working_variable];
#endif

#define DESCRIPTION \
Sets the locations for capturing errors, as specified by the first three arguments. \
The error information is type, array and index location respectively. \
If the error trap itself is faulty, it will overwrite the error info onto itself.

#include "../internal/instruction_post_template.c"
