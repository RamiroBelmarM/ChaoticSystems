/*

Implementation of the system found in the following paper for the NIST-STS.
Hua, Z., Zhou, Y., & Huang, H. (2019). Cosine-transform-based chaotic system for image encryption. Information Sciences, 480, 403-419.
https://doi.org/10.1016/j.ins.2018.12.048

*/
#include "./../../core/headers.h"

/*
Control parameters defined by the system
*/
double x_n;
double r_n;

/*
initialization of the system parameters in the interval that the cited paper recommends to get a chaotic trajectory
*/
void init_variables(){
    x_n=get_rand_crono(0.01,0.99);
    r_n=get_rand_crono(0.01,0.99);
    return;
}

/*
calculation of the system trajectory
*/
double get_point_from_system(){
    x_n=cos((4.0*r_n*x_n*(1.0-x_n)+(1.0-r_n)*sin(x_n*PI)-0.5)*PI);
    x_n=fmod(x_n,1.0);
    return x_n;
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
