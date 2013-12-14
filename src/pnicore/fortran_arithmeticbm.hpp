

namespace f90
{
extern "C"
{
    extern void deallocate_data();
    extern void allocate_data(int,int);

    extern void binary_run_add();
    extern void binary_run_sub();
    extern void binary_run_div();
    extern void binary_run_mult();
    extern void binary_run_all();

    extern void unary_run_add_array();
    extern void unary_run_add_scalar();
    extern void unary_run_sub_array();
    extern void unary_run_sub_scalar();
    extern void unary_run_div_array();
    extern void unary_run_div_scalar();
    extern void unary_run_mult_array();
    extern void unary_run_mult_scalar();
}
    

}
