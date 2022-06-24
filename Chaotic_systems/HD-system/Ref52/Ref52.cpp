/*

Implementation of the system found in the following paper for the NIST-STS.
Yu, F., Liu, L., Qian, S., Li, L., Huang, Y., Shi, C., ... & Wan, Q. (2020). Chaos-based application of a novel multistable 5D memristive hyperchaotic system with coexisting multiple attractors. Complexity, 2020.
DOI: https://doi.org/10.1155/2020/8034196

*/
#include "./../../core/headers.h"


/*
Control parameters defined by the system
*/
const unsigned int m=5;
const double dt=0.001;
double a;
double b=12.0;
double c=30;
double d=2.0;
double e=4.0;
double f=0.1;
double g=0.01;


/*
initialization of the system parameters in the interval that the cited paper recommends to get a chaotic trajectory
*/
std::vector<double> init_variables(){
    a=get_rand_crono(1.6, 2.2);
    std::vector<double> temp;
    for (size_t i=0; i<m; ++i)
        temp.push_back( get_rand_crono(1.0,2.0) );
    return temp;
}


/*
Definition of the chaotic system 
*/
std::vector<double> ode(std::vector<double> x){
    std::vector<double> temp;
    double *dxdt;
    dxdt = new double[m];

    dxdt[0] = -a*x[0]+x[1]*x[2];
    dxdt[1] = b*x[1]-x[0]*x[2];
    dxdt[2] = x[0]*x[1]-c*x[2]+d*x[3]*(f +3.0*g*x[4]*x[4]);
    dxdt[3] = x[0]*x[1]-e*x[3];
    dxdt[4] = -x[2];
    
    for (size_t i=0; i<m; i++){
        temp.push_back(dxdt[i]);
    }
    delete [] dxdt;
    return temp;
}

/*
Euler method for the integrations of the chaotic systems
*/
std::vector<double> rk1( std::vector<double> u0, int m,double dt){
    std::vector<double> f0;
    std::vector<double> u1;
    int i;

    f0 = ode( u0);

    for ( i = 0; i < m; i++ )
        u1.push_back(u0[i] + dt * f0[i] / 2.0);

    f0.clear();
    return u1;
}

int main(){
    std::vector<unsigned char>().swap(bytes);

    //Trajectory of the system
    std::vector<double> trajectory;

    for (size_t j=0; j<Num_cicles; ++j){

        //in every cicles the initial conditions of the system are recalculated
        trajectory=init_variables();

        //trajectory calculation, and data point to be ignored
        for (size_t i=0;i<Num_ignore; ++i){
            trajectory=rk1(trajectory,m,dt);
        }

        //trajectory calculation, points collection and transformation to bytes
        for (size_t i=0;i<Num_iterators; ++i){
            trajectory=rk1(trajectory,m,dt);
            to_int  =   fabs( fmod(trajectory[0],1.0))*P;
            to_byte =   to_int%256;
            bytes.push_back(to_byte);
        }
    }

    //saving the data in a binary file
    writeFileBytes("bitstream.dat",bytes);

    std::vector<unsigned char>().swap(bytes);
    
    return 0;
}
