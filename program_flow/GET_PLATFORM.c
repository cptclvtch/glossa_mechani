#define NAME LABEL(GET_PLATFORM)
#define ARGUMENTS 3

#include "../internal/instruction_pre_template.c"

#ifdef IMPLEMENTATION_MODE
MEMORY_AT_ADDRESS(arguments[0]) = PRIMARY_PLATFORM;
MEMORY_AT_ADDRESS(arguments[1]) = SECONDARY_PLATFORM;
MEMORY_AT_ADDRESS(arguments[2]) = TERTIARY_PLATFORM;
#endif

#define DESCRIPTION \
Places platform codes into the provided arguments.\
Each code represents a new branch in the following encoding tree:\
\
0 - desktop\
  0 - Windows\
    0 - 10\
    1 - 11\
  1 - Linux\
  2 - MacOS\
1 - mobile\
  0 - Android\
  1 - iOS\
2 - console\
  0 - XBox\
    0 - One\
    1 - Series X\
  1 - PS\
    0 - 4\
    1 - 5\
  2 - Nintendo\
    0 - Switch\
4 - VR\
5 - other\

#include "../internal/instruction_post_template.c"
