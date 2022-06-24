/*

Implementation of the system found in the following paper for the NIST-STS.
Sahari, M. L., & Boukemara, I. (2018). A pseudo-random numbers generator based on a novel 3D chaotic map with an application to color image encryption. Nonlinear Dynamics, 94(1), 723-744.
DOI: https://doi.org/10.1007/s11071-018-4390-z


*/
#include "./../../core/headers.h"


/*
Control parameters defined by the system
*/
double pt;
double qt;
double rt;
double u1;
double u2;
double u3;


/*
initialization of the system parameters in the interval that the cited paper recommends to get a chaotic trajectory
*/
void init_variables(){
    pt  =   get_rand_crono(0.0,1.0);
    qt  =   get_rand_crono(0.0,1.0);
    rt  =   get_rand_crono(0.0,1.0);
    u1  =   get_rand_crono(2.0,20.0);
    u2  =   get_rand_crono(2.0,20.0);
    return;
}

/*
Psi is a function defined in the cited paper
*/
double psi(double x){
    return fabs( 1.0-u1*x);
}

/*
Lambda is a function defined in the cited paper
*/
double lambda(double a, double b){
    return u2*a*(1.0-b);
}


/*
calculation of the system trajectory
*/
double get_point_from_system(){
    double p0=pt;
    double q0=qt;
    pt=fabs(psi(pt)+lambda(qt,rt));
    qt=fabs(psi(qt)+lambda(rt,p0));
    rt=fabs(psi(rt)+lambda(p0,q0));
    pt=fmod(pt,1.0);
    qt=fmod(qt,1.0);
    rt=fmod(rt,1.0);
    return pt;
}

int main(){

    std::vector<unsigned char>().swap(bytes);

    for (size_t j=0; j<Num_cicles; ++j){

        //in every cicles the initial conditions of the system are recalculated
        init_variables();

        //data point to be ignored
        for (size_t i=0;i<Num_ignore; ++i){
            get_point_from_system();
        }

        //points collection and transformation to bytes
        for (size_t i=0;i<Num_iterators; ++i){
            to_int  =   get_point_from_system()*P;
            to_byte =   to_int%256;
            bytes.push_back(to_byte);
        }
    }

    //saving the data in a binary file
    writeFileBytes("bitstream.dat",bytes);

    
    std::vector<unsigned char>().swap(bytes);
    return 0;
}
