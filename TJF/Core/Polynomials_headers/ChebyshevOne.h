#ifndef __CHEBYSHEVONE__
#define __CHEBYSHEVONE__
#include <cmath>
#include <math.h>
class ChebyshevOne{
    private:
        typedef unsigned int uint;
    private:
        double alpha_;
        uint n_;
    public:
        ChebyshevOne(){
            alpha_=2.0;
            n_=0;
        }
        ChebyshevOne(double a, uint n){
            alpha_=a;
            n_=n;
        }
        
        void set_alpha(double a){
            alpha_=a;
        }
        void set_n(uint n){
            n_=n;
        }
        void set(double a, uint n){
            alpha_=a;
            n_=n;
        }
        double get_P(double x){
            if (n_<0) return 0.0;
            if (n_==0) return 1.0;
            x*=d_cast(2)/alpha_;
            if (n_==1) return x;
            return cos(d_cast(n_) *acos(x));
        }
        double get_DP(double x){
            if (n_<=0) return d_cast(0);
            if (n_==1) return 1.0;
            x*=d_cast(2)/alpha_;
            return d_cast(n_)*sin(d_cast(n_)*acos(x))/(sqrt(d_cast(1)-x*x));
        }
    private:
        double d_cast(uint input){
            return static_cast<double>(input);
        }
};
#endif