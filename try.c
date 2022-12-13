#include <cpoly.h>
#include <print.h>

#define example(args...) example_wrap ( cpoly(1, ##args), ##args)

void example_wrap(cpoly_fmt_type fmt, ...) {
    print("--------- Example --------");

    // arg count
    unsigned int count = cpoly_arg_len(fmt); 

    if ( count == CTYPE_UNSUPPORTED ) {
        print("too many args!");
    } else {
        if ( count == 0 ) {
            print("No arguments!");
        } else {
            int i = 0;
            print("Arg count: ", count);
            do {
                print("arg", ++i, "is of type", ctype2str(cpoly_get_type(fmt)) );
            } while( cpoly_next_fmt(fmt) );
        }
    }

    print("-------------------------\n");
}

int main() {
    example(); // no args
    example(1,"s",5.89,5.89);
    return 0;
}