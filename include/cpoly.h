#if !defined(CPOLY_H_INCL)
#define CPOLY_H_INCL

#include <vararg.h>
#include <stdarg.h>

typedef unsigned long cpoly_fmt_type;
typedef enum cpoly_type {
    CTYPE_NONE, CTYPE_SHORT, CTYPE_USHORT, CTYPE_INT,
    CTYPE_UINT, CTYPE_LONG, CTYPE_ULONG, CTYPE_CHAR,
    CTYPE_STRING, CTYPE_FLOAT, CTYPE_DOUBLE, CTYPE_UNKNOWN, CTYPE_UNSUPPORTED
} cpoly_type;

cpoly_fmt_type cpoly_too_many_args();
unsigned int cpoly_max_args();
unsigned int cpoly_arg_len(cpoly_fmt_type fmt);
const char* ctype2str(cpoly_type typ);

#define cpolyarg_start(var, last_param) va_list var; va_start(var, last_param)
#define cpolyarg_get(var, type) va_arg(var, type)
#define cpolyarg_end(var) va_end(var)

#define cpoly_switch_type(var, args...) _Generic(var, ##args)
#define cpoly_get_type(fmtvar) ((fmtvar)%16)
#define cpoly_next_fmt(fmtvar) (fmtvar >>= 4)

#define cpoly__1(var) (unsigned long)cpoly__1_wrap(var)
#define cpoly__1_wrap(var) cpoly_switch_type(var,                                \
    short: CTYPE_SHORT, unsigned short: CTYPE_USHORT,                       \
    int: CTYPE_INT, unsigned int: CTYPE_UINT, long: CTYPE_LONG,              \
    unsigned long: CTYPE_ULONG, char: CTYPE_CHAR, char*: CTYPE_STRING,      \
    const char*: CTYPE_STRING, float: CTYPE_FLOAT, double: CTYPE_DOUBLE,    \
    default: CTYPE_UNKNOWN                                                  \
)

#define cpoly__1n(Z,P,D...) cpoly__1(P)
#define cpoly__2(Z,a,P,D...) (cpoly__1(P)<<4)+cpoly__1(a)
#define cpoly__3(Z,a,b,P,D...) ((cpoly__2(Z,b,P))<<4)+cpoly__1(a)
#define cpoly__4(Z,a,b,c,P,D...) ((cpoly__3(Z,b,c,P))<<4)+cpoly__1(a)
#define cpoly__5(Z,a,b,c,d,P,D...) ((cpoly__4(Z,b,c,d,p))<<4)+cpoly__1(a)
#define cpoly__6(Z,a,b,c,d,e,P,D...) ((cpoly__5(Z,b,c,d,e,P))<<4)+cpoly__1(a)
#define cpoly__7(Z,a,b,c,d,e,f,P,D...) ((cpoly__6(Z,P,f,e,d,c,b))<<4)+cpoly__1(a)
#define cpoly__8(Z,a,b,c,d,e,f,g,P,D...) ((cpoly__7(Z,P,g,f,e,d,c,b))<<4)+cpoly__1(a)
#define cpoly__9(Z,a,b,c,d,e,f,g,h,P,D...) ((cpoly__8(Z,P,h,g,f,e,d,c,b))<<4)+cpoly__1(a)

#define cpoly__10(Z,a,b,c,d,e,f,g,h,i,P,D...) ((cpoly__9(Z,P,i,h,g,f,e,d,c,b))<<4)+cpoly__1(a)
#define cpoly__11(Z,a,b,c,d,e,f,g,h,i,j,P,D...) ((cpoly__10(Z,P,j,i,h,g,f,e,d,c,b))<<4)+cpoly__1(a)
#define cpoly__12(Z,a,b,c,d,e,f,g,h,i,j,k,P,D...) ((cpoly__11(Z,P,k,j,i,h,g,f,e,d,c,b))<<4)+cpoly__1(a)
#define cpoly__13(Z,a,b,c,d,e,f,g,h,i,j,k,l,P,D...) ((cpoly__12(Z,P,l,k,j,i,h,g,f,e,d,c,b))<<4)+cpoly__1(a)
#define cpoly__14(Z,a,b,c,d,e,f,g,h,i,j,k,l,m,P,D...) ((cpoly__13(Z,P,m,l,k,j,i,h,g,f,e,d,c,b))<<4)+cpoly__1(a)
#define cpoly__15(Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,P,D...) ((cpoly__14(Z,P,n,m,l,k,j,i,h,g,f,e,d,c,b))<<4)+cpoly__1(a)

#define cpoly(dummy, args...) cpoly__wrap(16,##args,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)

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
