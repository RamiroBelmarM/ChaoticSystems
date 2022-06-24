#define Poly Hermite
#include "./../../Core/Polynomials_headers/Hermite_function.h"
#include "./../../Core/Cipher_headers/TJF-ARX-cipher.h"
void print_help(char *file_name){
    std::cout<<std::endl;
    std::cout<<"The Software is provided to you by the Licensor under the License, as defined below, subject to “Commons Clause” License Condition v1.0"<<std::endl;
    std::cout<<"Software:   TJF_ARX_cipher library."<<std::endl;
    std::cout<<"License:    BSD 3-Clause License."<<std::endl;
    std::cout<<"Licensor:   Ramiro Belmar Monterrubio. "<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Usage:"<<std::endl;
    std::cout<<'\t'<<file_name<<" [option] input_file output_file"<<std::endl;
    std::cout<<"option:"<<std::endl;
    std::cout<<'\t'<<"-h    Display this help"<<std::endl;
    std::cout<<'\t'<<"-e    Encryption mode"<<std::endl;
    std::cout<<'\t'<<"-d    Decryption mode"<<std::endl;
    std::cout<<std::endl;
    return;
}
int main(int argc, char** argv){
    if (argc==1){
        print_help(argv[0]);
        return 0;
    }
    std::vector<std::string> str;
    for (int i = 1; i < argc; ++i) {
        str.push_back(argv[i]);
    }
    if (str[0]=="-h" || str[0]=="-help" || str[0]=="help"){
        print_help(argv[0]);
        return 0;
    }
    if (str[0]!="-h" && str[0]!="-e" && str[0]!="-d"){
        std::cout<<"Unrecognized argument, please run:"<<std::endl;
        std::cout<<std::endl<<'\t'<<argv[0]<<" -h"<<std::endl<<std::endl;
        return 0;
    }
    if (str.size()<=2){
        std::cout<<"Arguments incomplete, please run:"<<std::endl;
        std::cout<<std::endl<<'\t'<<argv[0]<<" -h"<<std::endl<<std::endl;
        return 0;
    }
    if (str[1]==str[2]){
        std::cout<<"input/ouput file has the same name"<<std::endl;
        return 0;
    }
    TJF_ARX_cipher stream_cipher;
    if (str[0]=="-e"){
        stream_cipher.cipher(str[1],str[2],true);
        return 0;
    }
    stream_cipher.cipher(str[1],str[2],false);
    return 0;
}
