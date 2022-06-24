#ifndef __ChebyshevTwo__
#define __ChebyshevTwo__
#include <cmath>
#include <math.h>
class ChebyshevTwo{
    private:
        typedef unsigned int uint;
    private:
        double alpha_;
        uint n_;
    public:
        ChebyshevTwo(){
            alpha_=2.0;
            n_=0;
        }
        ChebyshevTwo(double a, uint n){
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
            if (n_==1) return d_cast(2)*x;
            return get_Poly(x);
        }
        double get_DP(double x){
            if (n_<=0) return d_cast(0);
            if (n_==1) return d_cast(2);
            x*=d_cast(2)/alpha_;
            return get_DPoly(x);
        }
    private:
        double d_cast(uint input){
            return static_cast<double>(input);
        }
        double get_Poly(double x){
            double temp=sin(d_cast(n_+1)*acos(x))/sin(acos(x));
            return temp;
        }
        double get_DPoly(double x){
            double A=d_cast(n_+1)*acos(x);
            double B=d_cast(1)-x*x;
            double C=sqrt(B);
            double temp=x*sin(A)/sqrt(B*B*B)-d_cast(n_+1)*cos(A)/B;
            return temp;
        }
};
#endif