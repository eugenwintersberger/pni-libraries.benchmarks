

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
}
    

}
