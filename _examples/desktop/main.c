#include "../../glossa_mechani.c"

DATA_TYPE test_program[] = {
    #include "matrix_multiplication.txt"
    //#include "two_plus_two.txt"
};

int main()
{
  INTERPRETER_MEMORY main_interpreter;

  setup_interpreter(&main_interpreter);

  load_up_array(&main_interpreter, 0, test_program);

  //try defining CLT to view your program running in real time!

  // #ifdef CLT
  // read_out_memory(&main_interpreter);
  // #endif

  interpreter_loop(&main_interpreter);

  retire_interpreter(&main_interpreter);
}
