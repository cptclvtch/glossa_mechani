
# API Guide

Before reading this guide, please refer to the language standard to insure a better understanding of the language.

To use this API, simply `#include "glossa_mechani.c"` into your project.

If you would like to get program execution readouts, please `#define CLT` beforehand.

## Interpreter Functions

These functions rely on the following types:
- `DATA_TYPE` - holds any atomic interpreter data (`DATA_TYPE var = 0;`)
- `INTERPRETER_MEMORY` - struct that refers to the interpreter

Getting an interpreter to run is pretty straight-forward. The usual path of achieving this is:
- `setup_interpreter(&<INTERPRETER_MEMORY struct>)` - Allocates initial memory for the interpreter.
- `interpreter_loop(&<INTERPRETER_MEMORY struct>)` - Starts the head movement.
- `retire_interpreter(&<INTERPRETER_MEMORY struct>)` - Deallocates all interpreter memory.

## Code Loading

In order to populate the interpreter memory with code, a simple function can be used:
- `load_up_array(&<INTERPRETER_MEMORY struct>, <DATA_TYPE value>, <DATA_TYPE[] array>)` - NOTE: The array being loaded needs to be in the same scope as this function call.

## Compatibility

The API is currently compatible with the following OSs:
- Windows
- MacOS
- iOS
- Linux
- Android

And the following compilers:
- tcc
- gcc
- clang
- msvc