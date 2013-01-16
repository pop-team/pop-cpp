#ifndef DEBUG_H
#define DEBUG_H

#ifdef NDEBUG

#ifdef __GNUC__

#define DEBUG(format,args...)

#define DEBUGIF(cond,format,args...)

#else

#define DEBUG printdebug

#define DEBUGIF printdebugif

inline int printdebug(const char *format,...) {};
inline int printndebug(int n, const char*format,...) {};
inline int printdebugif(int cond, const char *format,...) {};

#endif //__GNUC__

#else


#ifdef __GNUC__

#define DEBUG(format,args...) { if(getenv("POPC_DEBUG")){fprintf(stderr,"[%s:%d]",__FILE__,__LINE__) ; \
                        fprintf(stderr,format, ##args); fprintf(stderr,"\n"); }}

#define DEBUGIF(cond,format,args...) if (getenv("POPC_DEBUG")&&cond) {\
                         fprintf(stderr,"[%s:%d]",__FILE__,__LINE__) ;\
                         fprintf(stderr,format, ##args);  fprintf(stderr,"\n");}

#else //if not __GNUC__

extern char *thisfile_debug;
extern int thisline_debug;

#define DEBUG (thisfile_debug=__FILE__) && (thisline_debug=__LINE__)  &&  printdebug

#define DEBUGIF  (thisfile_debug=__FILE__) && (thisline_debug=__LINE__)  &&  printdebugif


int printdebug(const char *format,...);
int printdebugif(int cond, const char *format,...);

#endif //__GNUC__



#endif /* __DEBUG */

#endif
