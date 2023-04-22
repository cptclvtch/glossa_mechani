#ifdef __labels_as_values__
#define GO_TO_INSTRUCTION goto *instruction_table[instruction];

#define EMPTY_AND_DECAPITATE_INSTRUCTIONS EMPTY:;
#endif

#ifndef __labels_as_values__
#define GO_TO_INSTRUCTION switch(instruction){

#define EMPTY_AND_DECAPITATE_INSTRUCTIONS case DECAPITATE: goto DECAPITATE; case EMPTY: break; }
#endif