unsigned int test_counter = 0;
unsigned int test_loop = 0;
unsigned int result = 0;
const char* test_string;
const char* type_string;
unsigned long actual_input;
unsigned long target_value;

#define unit_test_stringify(content) #content
#define unit_test_retrieve(content) unit_test_stringify(content)

#define INDENT ""
#define CRITICAL ;
#define TEST_PRINT(...) PRINT_FN("\n" INDENT __VA_ARGS__);
#define POST_TITLE TEST_PRINT("Testing %-32s ", TITLE)
#define ADD_SEPARATOR TEST_PRINT("----------------------------------------------\n")
unsigned int test_flag = 0;
#define VERIFY_SINGLE_VALUE(input, type, target) if(!((input) type (target))) {test_flag++; type_string = unit_test_retrieve(type); test_string = unit_test_retrieve(input type target); actual_input = (unsigned long)input; target_value = (unsigned long)target;}

unsigned int test_iterator = 0;
#define VERIFY_ARRAY_OF_VALUES(input, type, target, max_index) \
for(test_iterator = 0; test_iterator <= max_index; test_iterator++){ VERIFY_SINGLE_VALUE(input, type, target) }

unsigned int total_tests = 0;
unsigned int tests_failed = 0;
#define COLLECT_FINDINGS \
if(test_flag){TEST_PRINT("\n------------" TITLE " (" SUBTITLE ") has failed the test.\n------------( %s )\n------------( %lu %s %lu )\n------------File " __FILE__ " - line " unit_test_retrieve(__LINE__) "\n", test_string, actual_input, type_string, target_value) tests_failed++;}\
else PRINT_FN("+");\
total_tests++; test_flag = 0;

#define DEBRIEF PRINT_FN("\n\n%u failed tests   ---   out of %u tests.\n", tests_failed, total_tests);
