/*

Implementation of the system found in the following paper for the NIST-STS.
Tariq, S., Khan, M., Alghafis, A., & Amin, M. (2020). A novel hybrid encryption scheme based on chaotic Lorenz system and logarithmic key generation. Multimedia Tools and Applications, 79(31), 23507-23529.
DOI: https://doi.org/10.1007/s11042-020-09134-8

*/
#include "./../../core/headers.h"


/*
Control parameters defined by the system
*/
const unsigned int m=3;
const double dt=0.001;
const double sigma=10.0;
double rho;
const double beta = 8.0/3.0;


/*
initialization of the system parameters in the interval that the cited paper recommends to get a chaotic trajectory
*/
std::vector<double> init_variables(){
    std::vector<double> temp;
    rho=get_rand_crono(28.0,40.0);
    for (int i=0; i<m; ++i)
        temp.push_back( get_rand_crono(1.0,10.0) );
    return temp;
}


/*
Definition of the chaotic system 
*/
std::vector<double> ode(std::vector<double> x){
    std::vector<double> temp;
    double *dxdt;
    dxdt = new double[m];

    dxdt[0] = sigma * ( x[1] - x[0] );
    dxdt[1] = x[0] * ( rho - x[2] ) - x[1];
    dxdt[2] = x[0] * x[1] - beta * x[2];
    
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
