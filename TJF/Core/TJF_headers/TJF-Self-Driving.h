#ifndef __TJF__
#define __TJF__
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include <random>

class TJF_SD{
    private:
        double an_, an_next;
        double bn_, bn_next;
        double cn_, cn_next;
        double dn_, dn_next, dn_next_next;
        double alpha_;
        unsigned int s_, s_next;
        double dt_;
        double t;
        double f_temp;
        Poly pn_;
        Poly pn_next;
    public:
        TJF_SD(){
            an_=0.0;
            bn_=0.0;
            dn_=0.0;
            cn_=0.0;
            s_=0;
        }
        void init_dt(double dt){
            dt_=dt;
            return;
        }
        void init_randomly(){
            an_=        random_number(0.0,1.0);
            bn_=        random_number(1.0,2.0);
            dn_=        random_number(0.01,0.998);
            alpha_=     random_number(2.0,4);
            s_=3;
        }
        void init_val(double an, double bn, double dn, double alpha){
            an_=    an;
            bn_=    bn;
            dn_=    dn;
            s_ =    3;
            alpha_ =alpha;
        }
        void init_function(){
            make_init();
        }
        double get_value(){
            return make_r();
        }
        void print_values(){
            std::cout<<"an"<<'\t'<<an_ <<std::endl;
            std::cout<<"bn"<<'\t'<<bn_ <<std::endl;
            std::cout<<"dn"<<'\t'<<dn_ <<std::endl;
            return;
        }
        void clear(){
            an_=    0.0;
            bn_=    0.0;
            dn_=    0.0;
            t=0.0;
        }
    private:
        double random_number(double min, double max){
            thread_local static std::mt19937 mt{std::random_device{}()};
            thread_local static std::uniform_real_distribution<double> dist;
            using pick = std::uniform_real_distribution<double>::param_type;
            return dist(mt, pick(min, max));
        }
        void make_init(){
            dn_next= dn_+1.0;
            cn_=dn_+(dn_next - dn_)/cast_d(2);
            dn_next_next= dn_next+mod_float(an_+bn_*pn_.get_P(dn_next-cn_));
            cn_next = dn_next + (dn_next_next-dn_next)/cast_d(2);
            pn_.set(alpha_, s_);
            pn_next.set(alpha_,s_);
            t=dn_;
            return ;
        }
        double mod_float(double input){
            return fabs(fmod(input,1.0));
        }
        double make_r(){
            do{
                if (t<dn_next){
                    f_temp=an_+bn_*pn_.get_P(t-cn_);
                    t+=dt_;
                    return f_temp;
                }
                s_next = get_s(mod_float(an_+bn_*pn_.get_P(t-cn_))); 
                pn_next.set_n(s_next);
                bn_next=bn_*pn_.get_DP(dn_next-cn_)/pn_next.get_DP(dn_next-cn_next);
                
                if (std::isnan(bn_next) || std::isinf(bn_next))
                    bn_next=bn_; 
                  
                an_next= an_+ bn_*pn_.get_P(dn_next-cn_)-bn_next*pn_next.get_P(dn_next-cn_next);
                an_=an_next;
                bn_=bn_next;
                pn_.set_n(s_next);
                dn_=dn_next;
                dn_next=dn_next_next;
                cn_=cn_next;
                dn_next_next= dn_next+1.0*fabs(fmod(an_+bn_*pn_.get_P(t-cn_),1.0));
                cn_next = dn_next + (dn_next_next-dn_next)/cast_d(2);
                s_=s_next;
            }while(true);
        }
        inline int get_s(double input){
            return ((int)(input*42949672))%4 + 2;
        }
        inline double cast_d(unsigned int input){
            return static_cast<double>(input);
        }
};
#endif