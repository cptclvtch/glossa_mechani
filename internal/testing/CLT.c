//Command Line Testing

unsigned int no_of_messages = 0;
#ifdef __ANDROID__
#define ENTER_TO_CONTINUE no_of_messages = 0;
#else
#define ENTER_TO_CONTINUE {PRINT_FN("\nPress Enter to continue...\n");while(getchar() != '\n'); no_of_messages = 0;}
#endif

#define SCREEN_LIMIT 45
#define PRINT(...) {PRINT_FN(__VA_ARGS__); no_of_messages++;}
#define CHECK_FOR_LIMIT if(no_of_messages > SCREEN_LIMIT) ENTER_TO_CONTINUE
#define CHECK_FOR_SKIP(message, code) PRINT_FN("\nSkip %s?(y/n)\n", message); if(getchar() == 'n' && getchar() == '\n'){code}

#define CLEAR_SCREEN {PRINT_FN("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); no_of_messages = 0;} //ghetto cls
