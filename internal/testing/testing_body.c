
INTERPRETER_MEMORY* interpreter;

INTERPRETER_MEMORY interpreter_temp;
interpreter = &interpreter_temp;

ADDRESS    arguments[16];
//void*      return_to_implementation;
DATA_TYPE  /*instruction, argument_index,*/ array_left;
DATA_TYPE  working_variable;
#define VARIABLE_MODE
#include "../error_handling.c"
#include "../instructions.c"

ADDRESS head;
#define TESTING
TEST_PRINT("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"\
"PERFORMING INTERNAL TESTS")
TEST_PRINT("----------------------------------------------\n")

//---------------------------------

#include "../memory/functions.c"

//---------------------------------
#undef INDENT
#define INDENT ""
TEST_PRINT("\nPERFORMING INSTRUCTION TESTS")
TEST_PRINT("----------------------------------------------\n")

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

#undef INDENT
#define INDENT "     "
#define CORE_IMPLEMENTATION_ONLY
#include "../instructions.c"

#include "additional_testing.c"

DEBRIEF