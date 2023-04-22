#ifdef TESTING
test_counter++;
#undef LABEL
#define LABEL(name) name ## _tests
goto NAME;
#undef LABEL
#define LABEL(name) name ## _test_finish
NAME:
#endif

#ifdef CORE_IMPLEMENTATION_ONLY
#undef IMPLEMENTATION_MODE
#endif

#ifdef IMPLEMENTATION_MODE
	#ifndef __labels_as_values__
break;
	#else
goto advance_head;
	#endif
#endif

#ifdef ENUMERATE
,
#endif

#ifdef CSV
;
#endif

#ifdef GENERATE_DOCUMENTATION
#ifndef ARGUMENTS
	#define ARGUMENTS 0
#endif

NAME | ARGUMENTS | DESCRIPTION

#endif

#undef NAME
#undef ARGUMENTS
#undef DESCRIPTION
#undef LABEL
#undef retrieve

#ifdef REDEF_IMPLEMENTATION_MODE
#define IMPLEMENTATION_MODE
#undef REDEF_IMPLEMENTATION_MODE
#endif
