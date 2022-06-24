/*

“Commons Clause” License Condition v1.0

The Software is provided to you by the Licensor under the License, as defined below, 
subject to the following condition.

Without limiting other conditions in the License, the grant of rights under the License 
will not include, and the License does not grant to you, the right to Sell the Software.

For purposes of the foregoing, “Sell” means practicing any or all of the rights granted 
to you under the License to provide to third parties, for a fee or other consideration 
(including without limitation fees for hosting or consulting/ support services related 
to the Software), a product or service whose value derives, entirely or substantially, 
from the functionality of the Software. Any license notice or attribution required by 
the License must also include this Commons Clause License Condition notice.

Software: TJF_ARX_cipher library.

License: BSD 3-Clause License.

Licensor: Ramiro Belmar Monterrubio.

*/
#ifndef __TJF_ARX__
#define __TJF_ARX__
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <stdlib.h>
#include <chrono>
#include <iterator>
#include <algorithm>
#include "./../TJF_headers/TJF.h"
#include "ARX.h"
#include "Key_init.h"
#include "Stuff.h"
class TJF_ARX_cipher{
    private:
        TJF tjf;
        ARX arx;
        Key_Init key_init;
        std::string password;
        unsigned int *key_left;
        unsigned int *key_right;
        unsigned long counter;
        #define STR_PACK32(str, x)                   \
        {                                             \
            *(x) =   ((uint32_t) *((str) + 3)      )    \
                | ((uint32_t) *((str) + 2) <<  8)    \
                | ((uint32_t) *((str) + 1) << 16)    \
                | ((uint32_t) *((str) + 0) << 24);   \
        }
        #define STR_UNPACK32(x, str)                 \
        {                                             \
            *((str) + 3) = (uint8_t) ((x)      );       \
            *((str) + 2) = (uint8_t) ((x) >>  8);       \
            *((str) + 1) = (uint8_t) ((x) >> 16);       \
            *((str) + 0) = (uint8_t) ((x) >> 24);       \
        }
        unsigned int x[8];
        std::vector<unsigned char> nonce;
        unsigned int w[8];
        unsigned int mu[8];
        unsigned int nu[8];
        unsigned char *sub_block;
        int i,j;
        std::string key_stream =  "                                                                ";
    public:
        void cipher(std::string input_name, std::string output_name, bool type){
            std::ifstream input(input_name, std::ios::binary );
            if (!input.is_open()){
                std::cout<<"Error opening file"<<std::endl;
                return;
            }
            init_cipher();
            std::vector<unsigned char> raw(std::istreambuf_iterator<char>(input), {});
            if (raw.size()<32){
                std::cout<<"File size less than 32 bytes"<<std::endl;
                return;
            }
            unsigned char *raw_pointer = &raw[0];
            if (type){
                set_nonce();
                std::cout<<"Encryption time: "<<CTR_mode(raw_pointer,raw.size())<<" ms"<<std::endl;
                for(size_t i=0; i<16; ++i)
                    raw.push_back(nonce[i]);
            }
            else{
                std::vector<unsigned char>().swap(nonce);
                for (size_t i=0; i<16; i++){
                    nonce.push_back(raw.back());
                    raw.pop_back();
                }
                std::reverse(nonce.begin(), nonce.end());
                for (int i=0; i<4; ++i)
                    STR_PACK32(&nonce[i<<2], &x[i+4]);
                std::cout<<"Decryption time: "<<CTR_mode(raw_pointer,raw.size())<<" ms"<<std::endl;
            }
            writeFileBytes(output_name.c_str(),raw);
            clear();
            return;
        }
        
    private:
        void init_cipher(){
            std::cout<<"Password: ";
            getline(std::cin, password);
            key_init.init(password);
            tjf.init_dt(0.1);
            tjf.init_val(   
                key_init.get_alpha(),   key_init.get_beta(), 
                key_init.get_gamma(),   key_init.get_lambda(), 
                key_init.get_a0(),      key_init.get_b0(), key_init.get_d0() , 
                key_init.get_l0()
            );
            tjf.init_function();
            key_left=key_init.get_left_key();
            key_right=key_init.get_right_key();
            key_init.clear();
            std::string ().swap(password);
            for (size_t i=0; i<1000; ++i)
                tjf.get_rand_from_system();
            return;
        }
        void mu_nu_init(){
            for (i = 0; i < 8; i++) {
                mu[i]=  (tjf.get_rand_from_system()%256) +
                        ((tjf.get_rand_from_system()%256)<<8) +
                        ((tjf.get_rand_from_system()%256)<<16) +
                        ((tjf.get_rand_from_system()%256)<<24);
                mu[i]^= key_left[i];
                key_left[i]=0;

                nu[i]=  (tjf.get_rand_from_system()%256) +
                        ((tjf.get_rand_from_system()%256)<<8) +
                        ((tjf.get_rand_from_system()%256)<<16) +
                        ((tjf.get_rand_from_system()%256)<<24);
                nu[i]^= key_right[i];
                key_right[i]=0;
            }
            return;
        }
        void generate_keystream(){
            x[0]=tjf.get_rand_from_system();
            x[1]=tjf.get_rand_from_system();
            x[2]=counter;
            x[3]=(counter>>32);
            for (j=0; j<8; ++j)
                w[j]= x[j]^mu[j];
            arx.ARX8(w);
            for (j = 0 ; j < 8; ++j){
                w[j]+=nu[j];
                STR_UNPACK32(w[j], &key_stream[j << 2]);
            }
            return;
        }
        size_t CTR_mode(unsigned char *input, int input_size){
            mu_nu_init();
            tjf.init_dt(0.001);
            int num_block=input_size/32;
            counter=0;
            auto start = std::chrono::steady_clock::now();
            for (i=0; i<num_block; ++i, ++counter){
                generate_keystream();
                sub_block=input+(i << 5);
                for (j=0; j<32; ++j)
                    sub_block[j]=sub_block[j]^key_stream[j];
            }
            auto end = std::chrono::steady_clock::now();
            if ((input_size%32)>0){
                generate_keystream();
                sub_block=input+(i << 5);
                for (j=0; j<(input_size%32); ++j)
                    sub_block[j]=sub_block[j]^key_stream[j];
            }
            return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        }
        void set_nonce(){
            for (int i=0; i<16; ++i)
                nonce.push_back(static_cast<unsigned char>(random_nonce()%256));
            for (int i=0; i<4; ++i)
                STR_PACK32(&nonce[i<<2], &x[i+4]);
            return;
        }
        void clear(){
            tjf.clear();
            for (i=0; i<8; ++i){
                x[i]=0;
                mu[i]=0;
                nu[i]=0;
                w[i]=0;
            }
            return;
        }
    
};

#endif