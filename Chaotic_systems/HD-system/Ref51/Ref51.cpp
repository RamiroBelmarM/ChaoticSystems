/*

Implementation of the system found in the following paper for the NIST-STS.
Zeng, J., & Wang, C. (2021). A novel hyperchaotic image encryption system based on particle swarm optimization algorithm and cellular automata. Security and Communication Networks, 2021.
DOI: https://doi.org/10.1155/2021/6675565

*/
#include "./../../core/headers.h"


/*
Control parameters defined by the system
*/
const unsigned int m=4;
const double dt=0.001;
double a=30.0;
double b=0.03;
double c=-1.2;
double d=50.0;
double e=0.32;
double f=0.1111;


/*
initialization of the system parameters in the interval that the cited paper recommends to get a chaotic trajectory
*/
std::vector<double> init_variables(){
    std::vector<double> temp;
    for (size_t i=0; i<m; ++i)
        temp.push_back( get_rand_crono(0.1,1.0) );
    return temp;
}


/*
Definition of the chaotic system 
*/
std::vector<double> ode(std::vector<double> x){
    std::vector<double> temp;
    double *dxdt;
    dxdt = new double[m];

    dxdt[0] = a*(x[1] -b*x[0]*x[0]*x[0]-(1.0+c)*x[0]);
    dxdt[1] = x[0]-x[1]+x[2];
    dxdt[2] = x[3]-d*x[1]-e*x[2];
    dxdt[3] = x[1]*x[2]-f*x[0];
    
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
