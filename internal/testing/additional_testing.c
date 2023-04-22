#undef INDENT
#define INDENT ""
TEST_PRINT("PERFORMING ADDITIONAL TESTS")
ADD_SEPARATOR

#undef TESTING

test_counter = 1;
setup_interpreter(interpreter);

resize_memory_to(5);

resize_array_to(0, 1 + 2 + 2 + 3);

DATA_TYPE set_random_seed_test[] = {
  SET_RANDOM_SEED, IMMEDIATE, 2,
  GET_RANDOM, 0,0
};
load_up_array(interpreter, test_counter++, set_random_seed_test);

DATA_TYPE if_test[] = {
 IF, IMMEDIATE, 1,
 ADD, 0,1, IMMEDIATE, 1, IMMEDIATE, 0,
 IF, IMMEDIATE, 0,
 SUBTRACT, 0,1, IMMEDIATE,1, IMMEDIATE, 0,
 OVERWRITE, 0,2, IMMEDIATE, 1
};
load_up_array(interpreter, test_counter++, if_test);

DATA_TYPE get_head_test[] = {
  GET_HEAD, 0,3, 0,4
  //3,0
};
load_up_array(interpreter, test_counter++, get_head_test);

DATA_TYPE set_error_trap_test[] = {
  SET_ERROR_TRAP, 0,5, 0,6, 0,7,
  OVERWRITE, MAX_ARRAY_INDEX, 0, IMMEDIATE, 0
};
load_up_array(interpreter, test_counter++, set_error_trap_test);

// DATA_TYPE get_platform_test[] = {
//   GET_PLATFORM, 0,8, 0,9, 0,10,
// };
// load_up_array(interpreter, 5, get_platform_test);

// DATA_TYPE set_head_test[] = {
//
// };
// load_up_array(interpreter, 3, set_head_test);

DATA_TYPE test_exit[] = {DECAPITATE};
load_up_array(interpreter, test_counter++, test_exit);

//-------------------------------
#ifdef CLT
read_out_memory(interpreter);
#endif

//-------------------------------
interpreter_loop(interpreter);

#undef TITLE
#define TITLE "SET_RANDOM_SEED"
POST_TITLE
//-------------------------------
#undef SUBTITLE
#define SUBTITLE "Best Case Scenario"

VERIFY_SINGLE_VALUE(MEMORY_AT(0,0), ==, 2 * 214013 + 2531011)
COLLECT_FINDINGS


#undef TITLE
#define TITLE "IF"
POST_TITLE
//-------------------------------
#undef SUBTITLE
#define SUBTITLE "True"

VERIFY_SINGLE_VALUE(MEMORY_AT(0,1), ==, 1)
COLLECT_FINDINGS

#undef SUBTITLE
#define SUBTITLE "False"

VERIFY_SINGLE_VALUE(MEMORY_AT(0,2), ==, 1)
COLLECT_FINDINGS


#undef TITLE
#define TITLE "GET_HEAD"
POST_TITLE
//-------------------------------
#undef SUBTITLE
#define SUBTITLE "Best Case Scenario"

VERIFY_SINGLE_VALUE(MEMORY_AT(0,3), ==, 3)
VERIFY_SINGLE_VALUE(MEMORY_AT(0,4), ==, 0)
COLLECT_FINDINGS


#undef TITLE
#define TITLE "SET_ERROR_TRAP"
POST_TITLE
//-------------------------------
#undef SUBTITLE
#define SUBTITLE "Best Case Scenario"

VERIFY_SINGLE_VALUE(MEMORY_AT(0,5), ==, ARRAY_ACCESS_FAILED)
VERIFY_SINGLE_VALUE(MEMORY_AT(0,6), ==, 4)
VERIFY_SINGLE_VALUE(MEMORY_AT(0,7), ==, 8)
COLLECT_FINDINGS

retire_interpreter(interpreter);

//-------------------------------

ADD_SEPARATOR
INTERPRETER_MEMORY* second_interpreter;
INTERPRETER_MEMORY second_temp_interpreter;
second_interpreter = &second_temp_interpreter;

setup_interpreter(second_interpreter);
setup_interpreter(interpreter);

DATA_TYPE interpreter_a_test[] = {
  OVERWRITE, IMMEDIATE, 0, IMMEDIATE, 1,
  DECAPITATE
};
load_up_array(interpreter, 0, interpreter_a_test);

DATA_TYPE interpreter_b_test[] = {
  OVERWRITE, IMMEDIATE, 0, IMMEDIATE, 2,
  DECAPITATE
};
load_up_array(second_interpreter, 0, interpreter_b_test);
//-------------------------------

interpreter_loop(interpreter);
interpreter_loop(second_interpreter);
//-------------------------------

#undef TITLE
#define TITLE "API for multiple interpreters"
POST_TITLE
//-------------------------------
#undef SUBTITLE
#define SUBTITLE "Best Case Scenario"

VERIFY_SINGLE_VALUE(MEMORY_AT(0,2), ==, 1)
VERIFY_SINGLE_VALUE(second_interpreter->memory.data[0].data[2], ==, 2)

COLLECT_FINDINGS

retire_interpreter(interpreter);
retire_interpreter(second_interpreter);

//-------------------------------

#undef TITLE
#define TITLE "Unorthodox Head Movement"
POST_TITLE
//-------------------------------

setup_interpreter(interpreter);

resize_memory_to(4);
resize_array_to(0,30);

DATA_TYPE uhm_test[] = {
  SET_ERROR_TRAP, 0,28, 0,29, 0,30, //0,1,2,3,4
  // MOVE_ARRAY_RANGE
  MOVE_ARRAY_RANGE, 2,0, 3,0, 1,0,  //0,2,3,1,4
  GET_HEAD, 0,0, 0,1,
  MOVE_ARRAY_RANGE, 3,0, 3,0, 2,0,  //0,2,1,3,4
  GET_HEAD, 0,1, 0,2,
  MOVE_ARRAY_RANGE, 1,0, 1,0, 2,0,  //0,1,2,3,4
  GET_HEAD, 0,2, 0,3,

  // COPY_ARRAY_RANGE
  COPY_ARRAY_RANGE, 1,0, 1,0, 4,0,  //0,1,2,3,1,4
  GET_HEAD, 0,3, 0,4,
  COPY_ARRAY_RANGE, 5,0, 5,0, 1,0,  //0,4,1,2,3,1,4
  COPY_ARRAY_RANGE, 1,0, 1,0, 1,0,  //0,4,4,1,2,3,1,4
  GET_HEAD, 0,4, 0,5,

  // CONJOIN_ARRAY_RANGE
  CONJOIN_ARRAY_RANGE, 1,0, 2,0,    //0,4.4,1,2,3,1,4
  GET_HEAD, 0,5, 0,6,
  CONJOIN_ARRAY_RANGE, 1,0, 2,0,    //0,4.4.1,2,3,1,4
  GET_HEAD, 0,6, 0,7,

  // SPLIT_ARRAY
  SPLIT_ARRAY, 1,2,                 //0,4.4,1,2,3,1,4
  GET_HEAD, 0,8, 0,9,
  SPLIT_ARRAY, 1,1,                 //0,4,4,1,2,3,1,4
  GET_HEAD, 0,10, 0,11,

  // DELETE_ARRAY_RANGE
  DELETE_ARRAY_RANGE, 1,0, 2,0,     //0,1,2,3,1,4
  GET_HEAD, 0,11, 0,12,

  ADD, 0,12, IMMEDIATE, 26, IMMEDIATE, 0,
  OVERWRITE, POSITIVE_RELATIVE, 9, 0,12,
  DELETE_INDEX_RANGE, 4,0, 4,0,

  DELETE_ARRAY_RANGE, 1,0, 3,0,     //0,1,4
  GET_HEAD, 0,12, 0,13,

  // MOVE_INDEX_RANGE
  MOVE_INDEX_RANGE, POSITIVE_RELATIVE,12, POSITIVE_RELATIVE,12, POSITIVE_RELATIVE,0, //move next EMPTY backward
  GET_HEAD, 0,16, 0,17,
  EMPTY,

  EMPTY,
  MOVE_INDEX_RANGE, NEGATIVE_RELATIVE,1, NEGATIVE_RELATIVE,1, POSITIVE_RELATIVE,11, //move previous EMPTY forward
  GET_HEAD, 0,15, 0,16,

  MOVE_INDEX_RANGE, POSITIVE_RELATIVE,0, POSITIVE_RELATIVE,11, NEGATIVE_RELATIVE,1, //move self before previous EMPTY
  GET_HEAD, 0,14, 0,15,

  // COPY_INDEX_RANGE
  COPY_INDEX_RANGE, NEGATIVE_RELATIVE,1, NEGATIVE_RELATIVE,1, POSITIVE_RELATIVE,0,
  GET_HEAD, 0,19, 0,18,

  // DELETE_INDEX_RANGE
  DELETE_INDEX_RANGE, NEGATIVE_RELATIVE,5, NEGATIVE_RELATIVE,1,
  GET_HEAD, 0,20, 0,19,

  DELETE_INDEX_RANGE, POSITIVE_RELATIVE,0, POSITIVE_RELATIVE,4,
  GET_HEAD, 0,21, 0,20,

  DECAPITATE
};
load_up_array(interpreter, 1, uhm_test);

interpreter_loop(interpreter);

#undef SUBTITLE
#define SUBTITLE "Move array range"

VERIFY_SINGLE_VALUE(MEMORY_AT(0,0), ==, 3)
VERIFY_SINGLE_VALUE(MEMORY_AT(0,1), ==, 2)
VERIFY_SINGLE_VALUE(MEMORY_AT(0,2), ==, 1)
COLLECT_FINDINGS

#undef SUBTITLE
#define SUBTITLE "Copy array range"
VERIFY_SINGLE_VALUE(MEMORY_AT(0,3), ==, 1)
VERIFY_SINGLE_VALUE(MEMORY_AT(0,4), ==, 3)
COLLECT_FINDINGS

#undef SUBTITLE
#define SUBTITLE "Conjoin array range"
VERIFY_SINGLE_VALUE(MEMORY_AT(0,5), ==, 2)
VERIFY_SINGLE_VALUE(MEMORY_AT(0,6), ==, 1)
VERIFY_SINGLE_VALUE(MEMORY_AT(0,7), ==, 91) //89 + 1 + 1
COLLECT_FINDINGS

#undef SUBTITLE
#define SUBTITLE "Split array"
VERIFY_SINGLE_VALUE(MEMORY_AT(0,8), ==, 2)
VERIFY_SINGLE_VALUE(MEMORY_AT(0,9), ==, 97) //91 + 5 + 3 - 2
VERIFY_SINGLE_VALUE(MEMORY_AT(0,10), ==, 3)
COLLECT_FINDINGS

#undef SUBTITLE
#define SUBTITLE "Delete array range"
VERIFY_SINGLE_VALUE(MEMORY_AT(0,11), ==, 1)
VERIFY_SINGLE_VALUE(MEMORY_AT(0,12), ==, 1)
VERIFY_SINGLE_VALUE(MEMORY_AT(0,13), ==, 0)
COLLECT_FINDINGS

#undef SUBTITLE
#define SUBTITLE "Move index range"
VERIFY_SINGLE_VALUE(MEMORY_AT(0,17), ==, 13)
VERIFY_SINGLE_VALUE(MEMORY_AT(0,16), ==, 25)
VERIFY_SINGLE_VALUE(MEMORY_AT(0,15), ==, 37)
COLLECT_FINDINGS

#undef SUBTITLE
#define SUBTITLE "Copy index range"
VERIFY_SINGLE_VALUE(MEMORY_AT(0,18), ==, 51)
COLLECT_FINDINGS

#undef SUBTITLE
#define SUBTITLE "Delete index range"
VERIFY_SINGLE_VALUE(MEMORY_AT(0,19), ==, 56)
VERIFY_SINGLE_VALUE(MEMORY_AT(0,20), ==, 61)
COLLECT_FINDINGS

retire_interpreter(interpreter);
