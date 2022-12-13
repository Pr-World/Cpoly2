#include <cpoly.h>
#include <print.h>

cpoly_fmt_type cpoly_too_many_args() {
    print("Too many arguments in a `cpoly` function.");
    return -1;
}

/// @brief Calculate max arg supported by cpoly
/// @return the max no of arguments supported by cpoly
unsigned int cpoly_max_args() {
    unsigned long ul = -1;
    unsigned int i;
    for(i = 1; ul >>= 4; i++) {}
    return i;
}

unsigned int cpoly_arg_len(cpoly_fmt_type fmt) {
    if (fmt == (unsigned long)-1) {
        return CTYPE_UNSUPPORTED;
    }
    if ( !fmt ) { return 0; }
    unsigned int i;
    for(i = 1; fmt >>= 4; i++) {}
    return i;
}

const char* CTYP2STR[] = {
    "none", "short", "unsigned short", "int", "unsigned int",
    "long", "unsigned long", "char", "string (char*, const char*)",
    "float", "double", "unknown ( custom )", "(too many arguments.)"
};

const char* ctype2str(cpoly_type typ) {
    return CTYP2STR[typ];
}