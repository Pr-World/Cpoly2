#include <cpoly.h>
#include <print.h>

// finished product
#define example(args...) example_polyfunc( cpoly(1, ##args) )

// wrapper function for polymorphism
void example_polyfunc(cpoly_fmt_type fmt, ...)
{
    cpolyarg_start(args, fmt); // start polyarg in args

    print("----------- Example ----------------");
    // -=-=-=-=- Polymorphism in Argument Count -=-=-=-=-
    
    switch( cpoly_arg_len(fmt) ) {

        case CTYPE_UNSUPPORTED:
            print("too many arguments."); goto end; // too many arguments
        case 0:
            print("No arguments!"); goto end; // 0 arguments
        case 1:
            print("1 argument"); break; // 1 argument
        default:
            print("more than 1 argument"); break; // and so on...
        
    }

    // -=-=-=-=- Polymorphism in Argument Type -=-=-=-=

    // print argument type and their values,
    int i = 0;
    do {
        cpoly_type typ = cpoly_get_type(fmt);
        switch(typ) {
            case CTYPE_INT:
                print("Its an int!");
                break;
            default:
                print("It is not int but `",ctype2str(typ),"`");
        }
    } while( cpoly_next_fmt(fmt) );

    end:
    print("------------------------------\n");

    cpolyarg_end(args);
}

int main()
{
    example(); // no arguments
    example(1); // one argument : integer
    example("string1", "string2"); // two arguments : string
    example(1, "string", -99, 89.56); // multiple types
    example(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20); // too many arguments!
    
    return 0;
}