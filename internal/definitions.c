//---------This is what defines the structure of the interpreter---------

//Smallest unit of information
#define DATA_TYPE           uint32_t
#define MAX_VALUE           0xFFFFFFFF

//Dynamic array
typedef struct s_ARRAY{
  DATA_TYPE* data;
  DATA_TYPE  max_index;
} ARRAY;

//Dynamic grid
typedef struct s_GRID{
  ARRAY*    data;
  DATA_TYPE max_index;
} GRID;
//

//Top-level program representation
typedef struct s_INTERPRETER_MEMORY{
  GRID memory;
  GRID instruction_info;
} INTERPRETER_MEMORY;


//Instruction info elements
enum{
  NUMBER_OF_ARGUMENTS,

  NUMBER_OF_INSTRUCTION_INFO_ELEMENTS
};


//---------Some utility definitions---------

//Instruction enums, in case you'd like to write a GM program inside a C program
enum{
#define NAME_MODE
#define ENUMERATE
#include "instructions.c"

NUMBER_OF_CORE_INSTRUCTIONS
};

//A tuple struct for working with addresses
typedef struct s_ADDRESS{
  DATA_TYPE array;
  DATA_TYPE index;
} ADDRESS;
//

#define ARGUMENT_SIZE 2

#define MAX_ARRAY_INDEX   MAX_VALUE - 4
//ADDRESSING TYPES
#define NEGATIVE_RELATIVE MAX_VALUE - 3
#define POSITIVE_RELATIVE MAX_VALUE - 2
#define CURRENT_ARRAY     MAX_VALUE - 1
#define IMMEDIATE         MAX_VALUE

// ERROR TYPES
enum{
  ARRAY_RESIZE_FAILED,
  MEMORY_RESIZE_FAILED,

  ARRAY_ACCESS_FAILED,
  INDEX_ACCESS_FAILED,
  INVALID_INSTRUCTION,

  NUMBER_OF_ERROR_TYPES
};

#define MEMORY_RESIZE_SUCCESSFUL    ARRAY_RESIZE_SUCCESSFUL
#define MEMORY_RESIZE_TOO_BIG       ARRAY_RESIZE_TOO_BIG
#define MEMORY_RESIZE_UNTARGETABLE  ARRAY_RESIZE_UNTARGETABLE


//---------Implementation specific definitions---------
#include "shortcuts.c"

#define internal_retrieve(content) #content