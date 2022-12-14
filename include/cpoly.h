#if !defined(CPOLY_H_INCL)
#define CPOLY_H_INCL

#include <vararg.h>
#include <stdarg.h>

// fmt_type
typedef unsigned long cpoly_fmt_type;

/// @brief enum containing types of arguments
typedef enum cpoly_type {
    CTYPE_NONE, CTYPE_SHORT, CTYPE_USHORT, CTYPE_INT,
    CTYPE_UINT, CTYPE_LONG, CTYPE_ULONG, CTYPE_CHAR,
    CTYPE_STRING, CTYPE_FLOAT, CTYPE_DOUBLE, CTYPE_POINTER,
    CTYPE_UNKNOWN, CTYPE_UNSUPPORTED = 16
} cpoly_type;

/// @brief Function to be called to notify user of using too many arguments
/// @return fmt_type indicating too many arguments
cpoly_fmt_type cpoly_too_many_args();

/// @brief Calculate the maximum arg supported ( different across systems )
/// @return no of max args supported in cpoly
unsigned int cpoly_max_args();

/// @brief Calculate the no of arguments packed inside fmt
/// @param fmt the cpoly_fmt format variable / value
/// @return no of args present in fmt / CTYPE_UNSUPPORTED if too many args.
unsigned int cpoly_arg_len(cpoly_fmt_type fmt);

/// @brief Convert ctype to string
/// @param typ ctype type to convert
/// @return string equivalent of ctype enum
const char* ctype2str(cpoly_type typ);

/// @brief Start of cpolyarg for different types of value
/// @param var variable to store arguments on
/// @param last_param last non-variadic parameter ( or parameter before `...` )
#define cpolyarg_start(var, last_param) va_list var; va_start(var, last_param)

/// @brief get value from stored arguments
/// @param var the stored argument variable
/// @param type type to get value as
#define cpolyarg_get(var, type) va_arg(var, type)

/// @brief end the cpolyarg
/// @param var the stored argument variable
#define cpolyarg_end(var) va_end(var)

/// @brief switch(type) in macros
#define cpoly_switch_type(var, args...) _Generic(var, ##args)

/// @brief get current type in `ctype` enum of a format variable
/// @param fmtvar the format variable
#define cpoly_get_type(fmtvar) ((fmtvar)%16)

/// @brief advance the format or change the format to next argument
/// @param fmtvar the format variable
#define cpoly_next_fmt(fmtvar) (fmtvar >>= 4)

/// @brief internal cpoly function to return type of 1 arg
#define cpoly__1(var) (unsigned long)cpoly__1_wrap(var)
#define cpoly__1_wrap(var) cpoly_switch_type(var,                           \
    short: CTYPE_SHORT, unsigned short: CTYPE_USHORT,                       \
    int: CTYPE_INT, unsigned int: CTYPE_UINT, long: CTYPE_LONG,             \
    unsigned long: CTYPE_ULONG, char: CTYPE_CHAR, char*: CTYPE_STRING,      \
    const char*: CTYPE_STRING, float: CTYPE_FLOAT, double: CTYPE_DOUBLE,    \
    int*: CTYPE_POINTER, unsigned int*: CTYPE_POINTER,                      \
    void*: CTYPE_POINTER, long*: CTYPE_POINTER,                             \
    unsigned long*:CTYPE_POINTER, short*:CTYPE_POINTER,                     \
    unsigned short*: CTYPE_POINTER,                                         \
    double*: CTYPE_POINTER, float*:CTYPE_POINTER,                           \
    default: CTYPE_UNKNOWN                                                  \
)

// internal cpoly function to return type upto 15 arguments

// Z & D... are dummy variables
// P -> present argument
// a,b,... -> argument upto P

// packing is done like this :-
// because arguments packed are from last to first,
// this type of design fetches first argument first and so on... till last at the last
// ((((( last << 4 ) + second_last ) << 4 ) + third_last ) << 4 ) + first

#define cpoly__1n(Z,P,D...) cpoly__1(P)
#define cpoly__2(Z,a,P,D...) (cpoly__1(P)<<4)+cpoly__1(a)
#define cpoly__3(Z,a,b,P,D...) ((cpoly__2(Z,b,P))<<4)+cpoly__1(a)
#define cpoly__4(Z,a,b,c,P,D...) ((cpoly__3(Z,b,c,P))<<4)+cpoly__1(a)
#define cpoly__5(Z,a,b,c,d,P,D...) ((cpoly__4(Z,b,c,d,P))<<4)+cpoly__1(a)
#define cpoly__6(Z,a,b,c,d,e,P,D...) ((cpoly__5(Z,b,c,d,e,P))<<4)+cpoly__1(a)
#define cpoly__7(Z,a,b,c,d,e,f,P,D...) ((cpoly__6(Z,b,c,d,e,f,P))<<4)+cpoly__1(a)
#define cpoly__8(Z,a,b,c,d,e,f,g,P,D...) ((cpoly__7(Z,b,c,d,e,f,g,P))<<4)+cpoly__1(a)
#define cpoly__9(Z,a,b,c,d,e,f,g,h,P,D...) ((cpoly__8(Z,b,c,d,e,f,g,h,P))<<4)+cpoly__1(a)

#define cpoly__10(Z,a,b,c,d,e,f,g,h,i,P,D...) ((cpoly__9(Z,b,c,d,e,f,g,h,i,P))<<4)+cpoly__1(a)
#define cpoly__11(Z,a,b,c,d,e,f,g,h,i,j,P,D...) ((cpoly__10(Z,b,c,d,e,f,g,h,i,j,P))<<4)+cpoly__1(a)
#define cpoly__12(Z,a,b,c,d,e,f,g,h,i,j,k,P,D...) ((cpoly__11(Z,b,c,d,e,f,g,h,i,j,k,P))<<4)+cpoly__1(a)
#define cpoly__13(Z,a,b,c,d,e,f,g,h,i,j,k,l,P,D...) ((cpoly__12(Z,b,c,d,e,f,g,h,i,j,k,l,P))<<4)+cpoly__1(a)
#define cpoly__14(Z,a,b,c,d,e,f,g,h,i,j,k,l,m,P,D...) ((cpoly__13(Z,b,c,d,e,f,g,h,i,j,k,l,m,P))<<4)+cpoly__1(a)
#define cpoly__15(Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,P,D...) ((cpoly__14(Z,b,c,d,e,f,g,h,i,j,k,l,m,n,P))<<4)+cpoly__1(a)

/// @brief polyform your macro function
/// @param dummy dummy argument ( anything here )
/// @param args the arguments in your macro ( ##args )
/// @returns packed fmt to redirect to a function
#define cpoly(dummy, args...) cpoly__wrap(16,##args,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)

/// @brief cpoly wrap internal function
/// @param n initial no of arguments
/// @param args arguments
#define cpoly__wrap(n, args...)                         \
vararg_start(cpoly_fmt_type)                            \
    vararg_if(n, 0, ##args)                             \
    vararg_if(n+1, cpoly__1n(1,##args), ##args)         \
    vararg_if(n+2, cpoly__2(1,##args), ##args)          \
    vararg_if(n+3, cpoly__3(1,##args), ##args)          \
    vararg_if(n+4, cpoly__4(1,##args), ##args)          \
    vararg_if(n+5, cpoly__5(1,##args), ##args)          \
    vararg_if(n+6, cpoly__6(1,##args), ##args)          \
    vararg_if(n+7, cpoly__7(1,##args), ##args)          \
    vararg_if(n+8, cpoly__8(1,##args), ##args)          \
    vararg_if(n+9, cpoly__9(1,##args), ##args)          \
    vararg_if(n+10, cpoly__10(1,##args), ##args)        \
    vararg_if(n+11, cpoly__11(1,##args), ##args)        \
    vararg_if(n+12, cpoly__12(1,##args), ##args)        \
    vararg_if(n+13, cpoly__13(1,##args), ##args)        \
    vararg_if(n+14, cpoly__14(1,##args), ##args)        \
    vararg_if(n+15, cpoly__15(1,##args), ##args)        \
\
    vararg_grt(n+cpoly_max_args(), cpoly_too_many_args(), ##args)   \
\
vararg_end(cpoly_too_many_args())

#endif // CPOLY_H_INCL
