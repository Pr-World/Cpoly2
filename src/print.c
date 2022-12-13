#include<print.h>

int print____int(int x) { return printf("%d", x); }
int print____uint(unsigned int x) { return printf("%u", x); }
int print____short(short x) { return printf("%hi", x); }
int print____ushort(unsigned short x) { return printf("%hu", x); }
int print____long(long x) { return printf("%li", x); }
int print____ulong(unsigned long x) { return printf("%lu", x); }
int print____double(double x) { return printf("%.15g", x); }
int print____float(float x) { return print____double((double)x); }
int print____string(const char * x) { return printf("%s", x); }
int print____char(char x) { return printf("%c", x); }

int print____unknown() { return printf("\n`print()` doesn't recognize the type to print.\n"); }