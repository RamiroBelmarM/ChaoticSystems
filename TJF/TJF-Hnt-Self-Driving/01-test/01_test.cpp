#define Poly Hermite
#include "./../../Core/Polynomials_headers/Hermite_function.h"
#include "./../../Core/Plot_headers/01-test.h"
#include "./../../Core/TJF_headers/TJF-Self-Driving.h"
int main(){
    TJF tjf;
    double t_end=600;
    double dt=0.5;
    std::vector<double> dat;
    tjf.init_dt(dt);
    tjf.init_randomly();
    tjf.init_function();
    for (size_t i=0; i<2000; ++i){
        dat.push_back(tjf.get_trajectory_point());
    }
    test01 test;
    test.init(dat,dt);
    test.make_test();
    std::cout<<"01 test result using randomly initial conditions: "<<test.get_value()<<std::endl;
    return 0;
}