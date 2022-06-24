#define Poly Legendre
#include "./../../Core/Polynomials_headers/Legendre_polynomials.h"
#include "./../../Core/TJF_headers/TJF.h"
#include "./../../Core/Plot_headers/Mutual_information.h"
using namespace std;
int main(){
    double dt=0.02;
    double t_end=2000;
    TJF tjf;
    tjf.init_dt(dt);
    tjf.init_randomly();
    tjf.init_function();

    std::vector<double> dat;
    for (double t=0.0; t<t_end; t+=dt){
        dat.push_back(tjf.get_trajectory_point());
    }

    MuttInf mutual;
    mutual.set(dat,dt);
    mutual.init();
    mutual.make();
    int tau=mutual.get_tau();

    for (int i=0; i<dat.size()-tau; ++i)
        cout<< dat[i]<<'\t'<<dat[i+tau]<<endl;

    return 0;
}