#ifndef __HERMITE__
#define __HERMITE__
#include <cmath>
class Hermite{
    private:
        typedef unsigned int uint;
    private:
        double alpha_;
        uint n_;
        double this_pi=0.751125544465;
        double sqrt_2= 1.41421356237;
    public:
        Hermite(){
            alpha_=1.0;
            n_=0;
        }
        Hermite(double a, uint n){
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
            if (n_<0) return d_cast(0);
            x*=d_cast(1)/alpha_;
            switch (n_){
                case 0: return P0(x);
                case 1: return P1(x);
                default: return Pn(x);
            }
        }
        double get_DP(double x){
            if (n_<0) return d_cast(0);
            x*=d_cast(1)/alpha_;
            switch (n_){
                case 0: return -x*P0(x);
                case 1: return sqrt_2*P0(x)*(d_cast(1)-x*x);
                default: return DPn(x);
            }
        }
    private:
        double d_cast(uint input){
            return static_cast<double>(input);
        }
        double P0(double x){
            return this_pi*exp(-x*x/d_cast(2));
        }
        double P1(double x){
            return sqrt_2*x*P0(x);
        }
        double Pn(double x){
            double pn_next=P1(x);
            double pn_current=P0(x);
            double pn;
            for (auto m = 2u ; m <= n_ ; ++m){ 
                pn = (sqrt_2/sqrt( d_cast(m) )) *x *pn_next - sqrt(d_cast(m-1)/d_cast(m))*pn_current;
                pn_current = pn_next;
                pn_next = pn;
            }
            return pn;
        }
        double DPn(double x){
            double pn_next=P1(x);
            double pn_current=P0(x);
            double pn;
            for (auto m = 2u ; m <= n_ ; ++m){ 
                pn = (sqrt_2/sqrt( d_cast(m) )) *x *pn_next - sqrt(d_cast(m-1)/d_cast(m))*pn_current;
                pn_current = pn_next;
                pn_next = pn;
            }
            return -x*pn+sqrt(d_cast(2)*d_cast(n_))*pn_current;
        }
};
#endif