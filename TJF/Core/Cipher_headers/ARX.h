#ifndef __ARX__
#define __ARX__

class ARX{
    private:
        #define ROTL(a,b) (((a) << (b)) | ((a) >> (32 - (b))))
        #define QR(a, b, c, d) (			\
            a += b,  d ^= a,  d = ROTL(d,16),	\
            c += d,  b ^= c,  b = ROTL(b,12),	\
            a += b,  d ^= a,  d = ROTL(d, 8),	\
            c += d,  b ^= c,  b = ROTL(b, 7))
        unsigned int x[8];
        int i;
    public:
        void ARX8(unsigned int input[8]){
            for (i = 0; i < 8; ++i)	
                x[i] = input[i];
            for (i = 0; i < 8; ++i){ 
                QR(x[0], x[1], x[2], x[3]); 
                QR(x[4], x[5], x[6], x[7]);
                QR(x[5], x[0], x[7], x[2]); 
                QR(x[1], x[4], x[3], x[6]); 
            }
            for (i = 0; i < 8; ++i)
                input[i] += x[i];
            return;
        }
        void ARXN(unsigned int input[8], int N){
            for (i = 0; i < 8; ++i)	
                x[i] = input[i];
            for (i = 0; i < N; ++i){ 
                QR(x[0], x[1], x[2], x[3]); 
                QR(x[4], x[5], x[6], x[7]);
                QR(x[5], x[0], x[7], x[2]); 
                QR(x[1], x[4], x[3], x[6]); 
            }
            for (i = 0; i < 8; ++i)
                input[i] += x[i];
            return;
        }

};
#endif