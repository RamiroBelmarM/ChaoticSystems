#include <iostream>
#include <chrono>
#include <random>
#include <cmath>
#include <vector>
#include <fstream>
#include <iterator>
/*
Num_iterators   -  is the number of iterations to achieve the 2^20 bits
Num_cicles      -  1000 cicles to be tested
Num_ignore      -  data points to be ignored before starting the data collection
P               -  2^32
N               -  2^8  to generate a byte in every iteration
*/
#define Num_iterators   131072   // 2^20/8
#define Num_cicles      1000       // 1000 bit-stream
#define Num_ignore      1000        // Data points to be ignore
#define P               4294967296          
#define N               256
#define PI              3.14159265359


/*
WriteFileBytes is a functions that allows the data contained in a bytes vector to be saved in a binary file.
*/
void writeFileBytes(const char* filename, std::vector<unsigned char>& fileBytes){
    std::ofstream file(filename, std::ios::out|std::ios::binary);
    std::copy(fileBytes.cbegin(), fileBytes.cend(),
        std::ostream_iterator<unsigned char>(file));
    return;
}


/*
For the random choices in the initial conditions, using an specific interval with the bounds defined by min and max values 
*/
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
double get_rand_crono(double min, double max){
    return std::uniform_real_distribution<double>(min,max)(rng);
}

/*
Vector that will contain the generating bytes by the chaotic system
*/
std::vector<unsigned char> bytes;


/*
temporary containers
*/
unsigned int to_int;
unsigned char to_byte;