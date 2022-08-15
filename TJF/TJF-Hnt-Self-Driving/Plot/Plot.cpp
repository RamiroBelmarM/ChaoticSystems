#define Poly Hermite
#include "./../../Core/Polynomials_headers/Hermite_function.h"
#include "./../../Core/TJF_headers/TJF-Self-Driving.h"
using namespace std;
int main(){
    double dt=0.01;
    double t_end=1000;
    TJF_SD tjf;
    tjf.init_dt(dt);
    tjf.init_randomly();
    tjf.init_function();
    for (double t=0.0; t<t_end; t+=dt){
        cout<<t<<'\t'<<tjf.get_value()<<endl;
    }
    return 0;
}