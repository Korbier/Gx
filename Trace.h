#pragma once
#ifdef ENABLE_TRACE
#define TRACE( message, ... ) \
	do { \
		fprintf(stdout, "%s (%d)\t"message"\n",__FILE__,__LINE__,__VA_ARGS__); \
	} while (0)
#define ERROR( message, ... ) \
	do { \
		fprintf(stderr, "%s (%d)\t"message"\n",__FILE__,__LINE__,__VA_ARGS__); \
	} while (0)
#else
#define TRACE( message, ... )
#define ERROR( message, ... )
#endif