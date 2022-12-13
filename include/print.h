#if !defined(PRINT_H_INCL)
#define PRINT_H_INCL

#include <vararg.h>
#include <stdio.h>

#define print__sep printf(" ")

// printf wrappers for print
int print____int(int x);
int print____uint(unsigned int x);
int print____short(short x);
int print____ushort(unsigned short x);
int print____long(long x);
int print____ulong(unsigned long x);
int print____double(double x);
int print____float(float x);
int print____string(const char * x);
int print____char(char x);

int print____unknown();

// print function macros
#define print____wn(n, toPrint) printwrap(toPrint)(toPrint) + ((n==1)?(printf("\n")):(0))
#define printwrap(x) _Generic((x),\
    default: (*print____unknown),\
    short: print____short,\
    unsigned short: print____ushort,\
    int: print____int,\
    unsigned int: print____uint,\
    long: print____long,\
    unsigned long: print____ulong,\
    float: print____float,\
    double: print____double,\
    char: print____char,\
    char *: print____string,\
    const char *: print____string\
)

// #define print____wn[n]
//(newline(n), a, b, c ...i, p, dummy(an)...)
// if v: print____wn[n-1](a,b,c,...,h) + print__sep + print____wn(n,p) else 0

#define print____wn1(n,p,an...) print____wn(n,p)
#define print____wn2(n,a,p,an...) print____wn(0,a) + print__sep + print____wn(n,p)
#define print____wn3(n,a,b,p,an...) print____wn2(0,a,b) + print__sep + print____wn(n,p)
#define print____wn4(n,a,b,c,p,an...) print____wn3(0,a,b,c) + print__sep + print____wn(n,p)
#define print____wn5(n,a,b,c,d,p,an...) print____wn4(0,a,b,c,d) + print__sep + print____wn(n,p)
#define print____wn6(n,a,b,c,d,e,p,an...) print____wn5(0,a,b,c,d,e) + print__sep + print____wn(n,p)
#define print____wn7(n,a,b,c,d,e,f,p,an...) print____wn6(0,a,b,c,d,e,f) + print__sep + print____wn(n,p)
#define print____wn8(n,a,b,c,d,e,f,g,p,an...) print____wn7(0,a,b,c,d,e,f,g) + print__sep + print____wn(n,p)
#define print____wn9(n,a,b,c,d,e,f,g,h,p,an...) print____wn8(0,a,b,c,d,e,f,g,h) + print__sep + print____wn(n,p)
#define print____wn10(n,a,b,c,d,e,f,g,h,i,p,an...) print____wn9(0,a,b,c,d,e,f,g,h,i)+ print__sep + print____wn(n,p)

/// @brief Prints given argument without newline
#define print_wn(args...) print____internal_wn(0, ## args)

/// @brief Prints given arguments
/// @param args the arguments to print
#define print(args...) print____internal_wn(1, ## args)

#define print____internal_wn(a, args...)                                \
vararg_start(int)                                                       \
    vararg_if(0, print____wn1(a,""), ##args)                                             \
    vararg_if(1, print____wn1(a, ##args, 0), ##args)                    \
    vararg_if(2, print____wn2(a, ##args, 0,0), ##args)                  \
    vararg_if(3, print____wn3(a, ##args, 0,0,0), ##args)                \
    vararg_if(4, print____wn4(a, ##args, 0,0,0,0), ##args)              \
    vararg_if(5, print____wn5(a, ##args, 0,0,0,0,0), ##args)            \
    vararg_if(6, print____wn6(a, ##args, 0,0,0,0,0,0), ##args)          \
    vararg_if(7, print____wn7(a, ##args, 0,0,0,0,0,0,0), ##args)        \
    vararg_if(8, print____wn8(a, ##args, 0,0,0,0,0,0,0,0), ##args)      \
    vararg_if(9, print____wn9(a, ##args, 0,0,0,0,0,0,0,0,0), ##args)    \
    vararg_if(10, print____wn10(a, ##args, 0,0,0,0,0,0,0,0,0,0), ##args)  \
vararg_end( printf("`print()` doesn't support more than 10 arguments.\n") )

#endif // PRINT_H_INCL
