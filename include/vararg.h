#if !defined(VARARG_H_INCL)
#define VARARG_H_INCL

// define arg_length to calculate argument length
#ifdef __STRICT_ANSI__

/// @brief Returns the length of arguments given to it
/// @param args arguments to calculate length of
# define ARG_LENGTH(...) __builtin_choose_expr(sizeof (#__VA_ARGS__) == 1,  \
        0,                                                                  \
        ARG_LENGTH__(__VA_ARGS__))

#else /* !__STRICT_ANSI__ */

/// @brief Returns the length of arguments given to it
/// @param args arguments to calculate length of
# define ARG_LENGTH(...) ARG_LENGTH__(__VA_ARGS__)

#endif /* !__STRICT_ANSI__ */

// helper for arg length
# define ARG_LENGTH__(...) ARG_LENGTH_(,##__VA_ARGS__,                         \
    63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45,\
    44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26,\
    25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6,\
    5, 4, 3, 2, 1, 0)
// helper for arg length
# define ARG_LENGTH_(_, _63, _62, _61, _60, _59, _58, _57, _56, _55, _54, _53, \
    _52, _51, _50, _49, _48, _47, _46, _45, _44, _43, _42, _41, _40, _39, _38, \
    _37, _36, _35, _34, _33, _32, _31, _30, _29, _28, _27, _26, _25, _24, _23, \
    _22, _21, _20, _19, _18, _17, _16, _15, _14, _13, _12, _11, _10, _9, _8,   \
    _7, _6, _5, _4, _3, _2, _1, Count, ...) Count
    
/// @brief vararg_start starts vararg multiple argument check
/// @param return_type the type that it returns ( should be same throughout )
#define vararg_start(return_type) (0==1)?((return_type)0):

/// @brief if arg count is equal to no_of_args return, given value
/// @param no_of_args no of arg to equate on
/// @param return_what what to return if they are equal
/// @param args the arguments
#define vararg_if(no_of_args, return_what, args...) ((ARG_LENGTH(1,##args)-1)==no_of_args)?(return_what):

/// @brief if arg count is greater than no_of_args, return given value
/// @param no_of_args no of arg to check on
/// @param return_what what to return if condition is true
/// @param args the arguments
#define vararg_grt(greater_than, return_what, args...) ((ARG_LENGTH(1,##args)-1)>greater_than)?(return_what):

/// @brief if arg count is less than no_of_args, return given value
/// @param no_of_args no of arg to check on
/// @param return_what what to return if condition is true
/// @param args the arguments
#define vararg_less(less_than, return_what, args...) ((ARG_LENGTH(1,##args)-1)<less_than)?(return_what):

/// @brief end the vararg multiple argument check
/// @param return_what what to return if all conditions are false & it's the end
#define vararg_end(return_what) (return_what)

#endif // VARARG_H_INCL
