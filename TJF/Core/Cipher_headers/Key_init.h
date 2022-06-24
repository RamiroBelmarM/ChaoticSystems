#ifndef __STUFF__
#define __STUFF__
#include "ARX.h"
#include <string>
#include <bitset>
#include <vector>
#include <cmath>
class Key_Init{
    private:
        double alpha;
        double beta;
        double gamma;
        double lambda;
        double a0;
        double b0;
        double d0;
        double l0;
        unsigned int key_left[8];
        unsigned int key_right[8];
        ARX arx;
        std::string pass;
        unsigned int h_left[8]={
            0x6a09e667,
            0xbb67ae85,
            0x3c6ef372,
            0xa54ff53a,
            0x510e527f,
            0x9b05688c,
            0x1f83d9ab,
            0x5be0cd19
        };
        unsigned int h_right[8]={
            0xc1059ed8,
            0x367cd507,
            0x3070dd17,
            0xf70e5939,
            0xffc00b31,
            0x68581511,
            0x64f98fa7,
            0xbefa4fa4,
        };

    public:
        void init(std::string &input){
            pass=input;
            StrToBin();
            Padding();
            arx_diffusion();
            BinToDouble();
            return;
        }
        void clear(){
            alpha=0.0;
            beta=0.0;
            gamma=0.0;
            lambda=0.0;
            a0=0.0;
            b0=0.0;
            d0=0.0;
            l0=0.0;
            std::string().swap(pass);
        }
        double get_alpha(){
            return alpha;
        }
        double get_beta(){
            return beta;
        }
        double get_gamma(){
            return gamma;
        }
        double get_lambda(){
            return lambda;
        }
        double get_a0(){
            return a0;
        }
        double get_b0(){
            return b0;
        }
        double get_d0(){
            return d0;
        }
        double get_l0(){
            return l0;
        }
        unsigned int * get_left_key(){
            return key_left;
        }
        unsigned int * get_right_key(){
            return key_right;
        }
    private:
        void StrToBin(){
            std::string out;
            std::string().swap(out);
            for(size_t i=0; i<pass.size(); ++i){
                out+= std::bitset<8>(pass.c_str()[i]).to_string();
            }
            pass=out;
        }
        void Padding(){
            if (pass.size()>512)
                for (;pass.size()>512;)
                    pass.pop_back();
            else
                for(;pass.size()<512;)
                    pass.push_back('0');
        }
        void arx_diffusion(){
            for (int i=0; i<8; i++){
                key_left[i]=std::bitset<32>(pass.substr((i<<5),32)).to_ulong();
                key_right[i]=std::bitset<32>(pass.substr(((i+8)<<5),32)).to_ulong();
            }
            arx.ARXN(key_left,4);
            arx.ARXN(key_right,4);
            for(size_t i=0; i<8; ++i){
                key_left[i]^=h_left[i];
                key_right[i]^=h_right[i];
            }
            arx.ARXN(key_left,6);
            arx.ARXN(key_right,6);
            std::string out;
            std::string().swap(out);
            for(size_t i=0; i<8; ++i){
                out+=std::bitset<32>(key_left[i]).to_string();
                out+=std::bitset<32>(key_right[i]).to_string();
            }
            pass=out;
            return;
        }

        
        void BinToDouble(){
            std::vector<double> sub_double;
            for (int i=0; i<16; ++i){
                sub_double.push_back(to_double(pass.substr((i<<5),32)));
            }
            a0=0.5*(sub_double[0]+sub_double[1]);
            b0=0.5*(sub_double[2]+sub_double[3]);
            d0=0.5*(sub_double[4]+sub_double[5]);
            l0=0.5*(sub_double[6]+sub_double[7]);
            alpha=0.5*(sub_double[8]+sub_double[9]);
            beta=0.5*(sub_double[10]+sub_double[11]);
            gamma=0.5*(sub_double[12]+sub_double[13]);
            lambda=0.5*(sub_double[14]+sub_double[15]);
            a0=10.0*a0;
            b0=1.0+5.0*b0;
            d0=0.001+0.998*d0;
            l0=0.001+0.998*l0;
            alpha=1.0+alpha;
            beta=0.001+0.998*beta;
            gamma=3.0+2.0*gamma;
            lambda=0.001+0.998*lambda;
        }
        double to_double(std::string input){
            double out=0.0;
            for (int i=0; i<input.size(); ++i){
                out+=cast_bin(input[i])/pow(2.0,1.0+i);
            }
            return out;
        }
        double cast_bin(const char input){
            if (input=='1')
                return 1.0;
            return 0.0;
        }

};

#endif