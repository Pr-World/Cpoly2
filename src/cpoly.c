#include <cpoly.h>
#include <print.h>

cpoly_fmt_type cpoly_too_many_args() {
    print("Cpoly Warn: too many arguments in a `cpoly` function.");
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

/// @brief Returns no of arguments inside a packed cpoly_fmt
/// @param fmt the packed cpoly_fmt
/// @return no of arguments inside cpoly_fmt, CTYPE_UNSUPPORTED if too many arguments
unsigned int cpoly_arg_len(cpoly_fmt_type fmt) {
    if (fmt == (unsigned long)-1) {
        return CTYPE_UNSUPPORTED;
    }
    if(!fmt) { return 0; }
    unsigned int i = 0;
    do { ++i; } while(cpoly_next_fmt(fmt));
    return i;
}

const char* CTYP2STR[] = {
    "none", "short", "unsigned short", "int", "unsigned int",
    "long", "unsigned long", "char", "string (char*, const char*)",
    "float", "double", "unknown ( custom )", "(too many arguments.)"
};


/// @brief Convert ctype to string
/// @param typ the ctype to convert
/// @return string equivalent of CTYPE_type enums
const char* ctype2str(cpoly_type typ) {
    return CTYP2STR[typ];
}