/*

Implementation of the system found in the following paper for the NIST-STS.
Shokouh Saljoughi, A., & Mirvaziri, H. (2019). A new method for image encryption by 3D chaotic map. Pattern Analysis and Applications, 22(1), 243-257.
DOI: https://doi.org/10.1007/s10044-018-0765-5

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
    pt=get_rand_crono(0.1,0.9);
    qt=get_rand_crono(0.1,0.9);
    rt=get_rand_crono(0.1,0.9);

    u1=get_rand_crono(3.53,3.81);
    u2=get_rand_crono(0.01,0.020);
    u3=get_rand_crono(0.01,0.014);
    return;
}


/*
calculation of the system trajectory
*/
double get_point_from_system(){
    double p0=pt;
    double q0=qt;
    pt= u1*pt*(1.0-pt)+u2*qt*qt*pt+u3*rt*rt;
    qt= u1*qt*(1.0-qt)+u2*rt*rt*qt+u3*p0*p0;
    rt= u1*rt*(1.0-rt)+u2*p0*p0*rt+u3*q0*q0;
    pt=fabs(fmod(pt,1.0));
    qt=fabs(fmod(qt,1.0));
    rt=fabs(fmod(rt,1.0));
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
