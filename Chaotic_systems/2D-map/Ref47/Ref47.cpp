/*

Implementation of the system found in the bellow paper for the NIST-STS.
Chen, C., Sun, K., & Xu, Q. (2020). A color image encryption algorithm based on 2D-CIMM chaotic map. China Communications, 17(5), 12-20.
DOI: 10.23919/JCC.2020.05.002

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
    y_n =   get_rand_crono(-1.0,1.0);
    a_  =   get_rand_crono(0.1,8.0);
    b_  =   get_rand_crono(2.3,3.0);
    return;
}


/*
calculation of the system trajectory
*/
double get_point_from_system(){
    x_n= sin(PI/y_n)*(a_*x_n*x_n*x_n - b_*x_n );
    y_n= sin(PI/x_n)*(a_*y_n*y_n*y_n - b_*y_n );
    x_n=fmod(x_n,1.0);
    y_n=fmod(y_n,1.0);
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
