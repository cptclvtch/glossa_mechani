#define LABEL(name) name

#define retrieve(content) content

#ifdef TURN_TO_LABEL
#undef retrieve
#define retrieve(content) &&content
#endif

#ifdef TURN_TO_STRING
#undef retrieve
#define retrieve(content) internal_retrieve(content)
#endif

#ifdef NAME_MODE
retrieve(NAME)
#endif

#ifdef ARGUMENTS_MODE
#ifdef ARGUMENTS
retrieve(ARGUMENTS)
#else
0
#endif
#endif

#ifdef REDEF_IMPLEMENTATION_MODE
#undef IMPLEMENTATION_MODE
#endif

#ifdef IMPLEMENTATION_MODE
	#ifndef __labels_as_values__
case
	#endif
NAME:
#endif

#ifdef CORE_IMPLEMENTATION_ONLY
#define IMPLEMENTATION_MODE
#endif

#ifdef TESTING
#undef TITLE
#define TITLE unit_test_retrieve(NAME)
POST_TITLE
//---------------------------------
test_counter = 0;
#undef LABEL
#define LABEL(name) name ## _tests
NAME:
#undef LABEL
#define LABEL(name) name
#endif
