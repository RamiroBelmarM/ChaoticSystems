#define Poly ChebyshevTwo
#include "./../../Core/Polynomials_headers/ChebyshevTwo.h"
#include "./../../Core/TJF_headers/TJF.h"
using namespace std;
int main(){
    double dt=0.01;
    double t_end=1000;
    TJF tjf;
    tjf.init_dt(dt);
    tjf.init_randomly();
    tjf.init_function();
    for (double t=0.0; t<t_end; t+=dt){
        cout<<t<<'\t'<<tjf.get_trajectory_point()<<endl;
    }
    return 0;
}