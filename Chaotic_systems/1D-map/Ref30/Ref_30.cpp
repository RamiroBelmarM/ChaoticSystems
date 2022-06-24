/*

Implementation of the system found in the following paper for the NIST-STS.
Pak, C., & Huang, L. (2017). A new color image encryption using combination of the 1D chaotic map. Signal Processing, 138, 129-137.
https://doi.org/10.1016/j.sigpro.2017.03.011

*/
#include "./../../core/headers.h"

/*
Control parameters defined by the system
*/
double x_n;
double r_n;

/*
d14 defined in the paper as 2^14
*/
#define d14 16384  //2^14

/*
initialization of the system parameters in the interval that the cited paper recommends to get a chaotic trajectory
*/
void init_variables(){
    x_n=get_rand_crono(0.01,0.99);
    r_n=get_rand_crono(1.01,9.99);
    return;
}

/*
calculation of the system trajectory
*/
double get_point_from_system(){
    x_n=r_n*sin(x_n*PI)*d14;
    x_n= fabs( x_n-floor(x_n) );
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
