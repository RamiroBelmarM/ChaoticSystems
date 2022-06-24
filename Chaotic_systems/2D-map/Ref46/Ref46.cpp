/*

Implementation of the system founded in the bellow paper for the NIST-STS.
Cao, W., Mao, Y., & Zhou, Y. (2020). Designing a 2D infinite collapse map for image encryption. Signal Processing, 171, 107457.
https://doi.org/10.1016/j.sigpro.2020.107457

*/
#include "./../../core/headers.h"

/*
Control parameters defined by the system
*/
double x_n;
double y_n;
double a_;
double b_;


/*
initialization of the system parameters in the interval that the cited paper recommends to get a chaotic trajectory
*/
void init_variables(){
    x_n =   get_rand_crono(-1.0,1.0);
    a_  =   get_rand_crono(16.0,21.0);
    y_n =   get_rand_crono(-1.0,1.0);
    b_  =   get_rand_crono(16.0,21.0);
    return;
}

/*
calculation of the system trajectory
*/
double get_point_from_system(){
    double x_n_t=x_n;
    x_n=sin(a_/y_n)*sin(b_/x_n);
    y_n=sin(a_/x_n_t)*sin(b_/y_n);
    return fabs( y_n );
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
