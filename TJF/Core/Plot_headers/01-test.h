#ifndef __01TEST__
#define __01TEST__
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iostream>
class test01{
    private:
        const double my_pi = 3.14159265358979323846;
        std::vector <double> dat;
        std::vector <double> dat_sum;
        std::vector <double> qc_vector;
        std::vector <double> pc_vector;
        std::vector <double> mc;
        std::vector <double> kc;
        std::vector <double> xi;
        double kc_final_value; //valor final
        double N_;
        double c_top=100; //numero de pruebas
        double dt_; //tiempo de muestreo 
        int size_min=1000;
    public:
        void init(std::vector<double> input){
            std::vector<double>().swap(dat);
            dat=input;
            dt_=1.0;
        }
        void init(std::vector<double> input, double dt){
            std::vector<double>().swap(dat);
            dat=input;
            dt_=dt;
        }
        void make_test(){
            if (dat.size()<size_min){
                std::cout<<"Error, data must have at least 1000 observations"<<std::endl;
                kc_final_value=sqrt(-1.0);
                return;
            }
            make_sum();
            srand(time(NULL));
            std::vector<double>().swap(mc);
            std::vector<double>().swap(kc);
            N_=cast_d(dat.size())/10.0;
            make_xi();
            for (size_t i=0; i<c_top; ++i){ 
                make_new_coordinates();
                for (size_t j=0; j<N_; ++j){
                    make_mc(j);
                }
                kc.push_back(make_kc());
                std::vector<double>().swap(mc);
            }
            quicksort(&kc[0],kc.size());
            kc_final_value=kc[c_top/2];
            std::vector<double>().swap(kc);
            return ;
        }
        double get_value(){
            return kc_final_value;
        }
        void print_pcqc(std::vector<double> input){
            std::vector<double>().swap(dat);
            srand(time(NULL));
            dat=input;
            make_sum();
            make_new_coordinates();
            for (size_t i=0; i<pc_vector.size(); ++i){
                std::cout<<pc_vector[i]<<'\t'<<qc_vector[i]<<std::endl;
            }
            return ;
        }
        void print_pcqc(){
            srand(time(NULL));
            make_sum();
            make_new_coordinates();
            for (size_t i=0; i<pc_vector.size(); ++i){
                std::cout<<pc_vector[i]<<'\t'<<qc_vector[i]<<std::endl;
            }
            return ;
        }
        void clear(){
            std::vector <double>().swap(dat);
            std::vector <double>().swap( dat_sum);
            std::vector <double>().swap( qc_vector);
            std::vector <double>().swap( pc_vector);
            std::vector <double>().swap( mc);
            std::vector <double>().swap( kc);
            std::vector <double>().swap( xi);
            dt_=1.0;
            N_=0.0;
        }
    private:
        double cast_d(unsigned int input){
            return static_cast<double>(input);
        }
        void make_sum(){
            double temp=0.0;
            std::vector<double>().swap(dat_sum);
            for (size_t i=0; i<dat.size(); ++i){
                temp+=dat[i];
                dat_sum.push_back(temp);
            }
            return;
        }
        void make_new_coordinates(){
            std::vector<double>().swap(pc_vector);
            std::vector<double>().swap(qc_vector);
            double temp_pc=0.0;
            double temp_qc=0.0;
            double c_value= (cast_d(rand())/RAND_MAX )*my_pi*0.98+0.01;
            double theta;
            for (size_t i=0; i< dat.size(); ++i){
                theta= cast_d(i+1)*c_value + dat_sum[i];
                temp_pc+=dat[i]*cos(theta);
                temp_qc+=dat[i]*sin(theta);
                pc_vector.push_back(temp_pc);
                qc_vector.push_back(temp_qc);
            }
            return;
        }
        void make_mc(unsigned int tope){
            double temp=0.0;
            double temp_qc;
            double temp_pc;
            for (size_t i=0; i< (dat.size()-tope); ++i){
                temp_pc= pc_vector[i]-pc_vector[i+tope];
                temp_qc= qc_vector[i]-qc_vector[i+tope];
                temp+=(temp_pc*temp_pc + temp_qc*temp_qc );
            }
            temp/=cast_d(dat.size()-tope);
            mc.push_back(temp*dt_*dt_);
            return;
        }
        void make_xi(){
            std::vector <double>().swap(xi);
            for (size_t i=0; i<N_ ; ++i){
                xi.push_back( cast_d( i+1));
            }
            return ;
        }
        double mean_vector(std::vector<double> input){
            double sum=0.0;
            for (size_t i=0; i< input.size(); ++i){
                sum+=input[i];
            }
            return sum/cast_d(input.size());
        }
        double cov_vector(std::vector <double > left, double left_mean, std::vector<double> right, double right_mean){
            double cov=0.0;
            for (size_t i=0; i< left.size(); ++i){
                cov+=((left[i]-left_mean)*(right[i]-right_mean) );
            }
            return cov/cast_d(left.size());
        }
        double var_vector(std::vector <double> input, double mean  ){
            return cov_vector(input, mean, input, mean );
        }
        double make_kc(){
            double kc_val;
            double mc_mean= mean_vector(mc);
            double xi_mean= mean_vector(xi);
            kc_val=cov_vector(mc, mc_mean, xi, xi_mean);
            kc_val/=sqrt( var_vector(mc,mc_mean)*var_vector(xi,xi_mean));
            return kc_val;
        }
        //quicksort
        //code from StackOverflow
        void quicksort(double a[], int n) {
            if (n <= 1) return;
            double p = a[n/2];
            double b[n], c[n];
            int i, j = 0, k = 0;
            for (i=0; i < n; i++) {
                if (i == n/2) 
                    continue;
                if ( a[i] <= p) 
                    b[j++] = a[i];
                else            
                    c[k++] = a[i];
            }
            quicksort(b,j);
            quicksort(c,k);
            for (i=0; i<j; i++) 
                a[i] =b[i];
            a[j] = p;
            for (i= 0; i<k; i++) 
                a[j+1+i] =c[i]; 
            return ;
        } 

};
#endif
