#define Poly Hermite
#include "./../../Core/Polynomials_headers/Hermite_function.h"
#include "./../../Core/TJF_headers/TJF.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>

#define P 4294967296
#define bitstream 131072
#define N_cycles 1000
using namespace std;

void writeFileBytes(const char* filename, std::vector<unsigned char>& fileBytes){
    std::ofstream file(filename, std::ios::out|std::ios::binary);
    std::copy(fileBytes.cbegin(), fileBytes.cend(),
        std::ostream_iterator<unsigned char>(file));
    return;
}

int main(){
    double dt=0.01;
    double temp;
    unsigned char a;
    std::vector<unsigned char> bytes;
    TJF tjf;
    tjf.init_dt(dt);
    for (int j=0; j<N_cycles; ++j){
        tjf.init_randomly();
        tjf.init_function();
        for (size_t i=0; i<1000; i++)
            tjf.get_trajectory_point();
        
        for (int i=0; i<bitstream; ++i){
            temp=tjf.get_trajectory_point();
            a=((unsigned int)(temp*P))%256;
            bytes.push_back(a);
        }
        tjf.clear();
    }
    writeFileBytes("bitstream.dat",bytes);
    return 0;
}