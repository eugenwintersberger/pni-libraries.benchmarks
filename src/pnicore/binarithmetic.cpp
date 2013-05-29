#include<pni/core/arrays.hpp>

using namespace pni::core;

int main(int argc,char **argv)
{
    typedef numarray<darray<float64> > narray_t;
    narray_t a,b,c;
    shape_t shape{10,3};
    a = narray_t(shape);
    b = narray_t(shape);
    c = narray_t(shape);

    std::fill(a.begin(),a.end(),1.f);
    std::fill(b.begin(),b.end(),2.f);
    std::fill(c.begin(),c.end(),0.);

    c = a+b;

    return 0;
}
