/*

Implementation of the system found in the following paper for the NIST-STS.
Seyedzadeh, S. M., & Mirzakuchaki, S. (2012). A fast color image encryption algorithm based on coupled two-dimensional piecewise chaotic map. Signal processing, 92(5), 1202-1215.
DOI: https://doi.org/10.1016/j.sigpro.2011.11.004

*/
#include "./../../core/headers.h"


/*
Control parameters defined by the system
*/
double x1,x2,x3;
double y1_,y2,y3;
double a_,b1_,b2_;
double epsilon=0.02;


/*
initialization of the system parameters in the interval that the cited paper recommends to get a chaotic trajectory
*/
void init_variables(){
    x1=get_rand_crono(0.0,1.0);
    x2=get_rand_crono(0.0,1.0);
    x3=get_rand_crono(0.0,1.0);

    y1_=get_rand_crono(0.0,1.0);
    y2=get_rand_crono(0.0,1.0);
    y3=get_rand_crono(0.0,1.0);
    
    a_=get_rand_crono(0.0,1.0);
    b1_=get_rand_crono(0.0,1.0);
    b2_=get_rand_crono(0.0,1.0);
    return;
}

/*
Phi_1 is defined in the cited paper
*/
double phi_1(double xn, double alpha){
    double top=4.0*alpha*alpha*xn*(1.0-xn);
    double bottom=1+4.0*(alpha*alpha-1.0)*xn*(1.0-xn);
    return top/bottom;
}

/*
Phi_2 is defined in the cited paper
*/
double phi_2(double yn, double xn, double b1, double b2){
    if (xn<0.5){
        return phi_1(yn,b1);
    }
    return phi_1(yn,b2);
}


/*
calculation of the system trajectory
*/
double get_point_from_system(){
    double x1_t=x1;
    double y1_t=y1_;
    x1=(1.0-epsilon)*phi_1(x1,a_)+epsilon*phi_1(x2,a_);
    y1_=(1.0-epsilon)*phi_2(y1_,x1_t,b1_,b2_)+epsilon*phi_2(y2,x2,b1_,b2_);
    x1=fabs(fmod(x1,1.0));
    y1_=fabs(fmod(y1_,1.0));

    double x2_t=x2;
    x2=(1.0-epsilon)*phi_1(x2,a_)+epsilon*phi_1(x3,a_);
    y2=(1.0-epsilon)*phi_2(y2,x2_t,b1_,b2_)+epsilon*phi_2(y3,x3,b1_,b2_);
    x2=fabs(fmod(x2,1.0));
    y2=fabs(fmod(y2,1.0));

    double x3_t=x3;
    x3=(1.0-epsilon)*phi_1(x3,a_)+epsilon*phi_1(x1_t,a_);
    y3=(1.0-epsilon)*phi_2(y3,x3_t,b1_,b2_)+epsilon*phi_2(y1_t,x1_t,b1_,b2_);
    x3=fabs(fmod(x3,1.0));
    y3=fabs(fmod(y3,1.0));
    return y1_;
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
