#ifndef __TJF__
#define __TJF__
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include <random>

class TJF{
    private:
        double an_, an_next;
        double bn_, bn_next;
        double cn_, cn_next;
        double dn_, dn_next, dn_next_next;
        double alpha_;
        double beta_;
        double gamma_;
        double lambda_;
        unsigned int s_, s_next;
        double dt_;
        double An_max=50.0;
        double Bn_max=25.0;
        double ln_, rn_;
        double t;
        double f_temp;
        double w;
        Poly pn_;
        Poly pn_next;
    public:
        TJF(){
            an_=0.0;
            bn_=0.0;
            dn_=0.0;
            cn_=0.0;
        }
        void init_dt(double dt){
            dt_=dt;
            return;
        }
        void init_randomly(){
            alpha_=     random_number(1.5,2.5);
            beta_=      random_number(0.01,0.998);
            gamma_=     random_number(3.0,5.0);
            lambda_=    random_number(0.01,0.998);
            an_=        random_number(0.0,10.0);
            bn_=        random_number(2.0,6.0);
            dn_=        random_number(0.01,0.998);
            ln_=        random_number(0.01,0.998);
            rn_=dn_;
        }
        void init_val(double alfa, double beta, double gamma, double lambda, double an, double bn, double dn, double ln){
            alpha_= alfa;
            beta_=  beta;
            gamma_= gamma;
            lambda_=lambda;
            an_=    an;
            bn_=    bn;
            dn_=    dn;
            ln_=    ln;
            rn_=    dn;
        }
        void init_function(){
            make_init();
        }
        double get_trajectory_point(){
            return make_r();
        }
        unsigned int get_rand_from_system(){
            w=make_r();
            w=fabs(w);
            w=w-(int)w;
            return w*4294967296;
        }
        unsigned int get_rand_from_system2(){
            w=bn_*pn_.get_DP(t-cn_);
            w=fabs(w);
            w=w-(int)w;
            return w*4294967296;
        }
        void clear(){
            alpha_= 0.0;
            beta_=  0.0;
            gamma_= 0.0;
            lambda_=0.0;
            an_=    0.0;
            bn_=    0.0;
            dn_=    0.0;
            ln_=    0.0;
            rn_=    0.0;
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
            dn_next= dn_+Activation_Function() ;
            dn_next_next= dn_next+Activation_Function();
            cn_=dn_+(dn_next - dn_)/cast_d(2);
            cn_next = dn_next + (dn_next_next-dn_next)/cast_d(2);
            s_=get_s();
            pn_.set(alpha_, s_);
            pn_next.set(alpha_,s_);
            t=dn_;
            return ;
        }
        double Activation_Function(){
            ln_=ln_*beta_*(1.0-ln_)*4096.0;
            ln_=fmod(ln_ , 1.0);
            return ln_;
        }
        double make_r(){
            do{
                if (t<dn_next){
                    f_temp=an_+bn_*pn_.get_P(t-cn_);
                    t+=dt_;
                    return f_temp;
                }
                s_next = get_s(); 
                pn_next.set_n(s_next);
                bn_next=bn_*pn_.get_DP(dn_next-cn_)/pn_next.get_DP(dn_next-cn_next);
                
                if (std::isnan(bn_next) || std::isinf(bn_next))
                    bn_next=bn_*gamma_; 
                  
                an_next= an_+ bn_*pn_.get_P(dn_next-cn_)-bn_next*pn_next.get_P(dn_next-cn_next);
                an_=an_next;
                bn_=bn_next;

                //rules 14 15
                
                an_=fmod(an_,An_max);
                if (bn_>0)
                    bn_=fmod(bn_,Bn_max)+gamma_;
                else
                    bn_=fmod(bn_,Bn_max)-gamma_;
                
                //end rules

                pn_.set_n(s_next);
                dn_=dn_next;
                dn_next=dn_next_next;
                cn_=cn_next;
                dn_next_next= dn_next+Activation_Function();
                cn_next = dn_next + (dn_next_next-dn_next)/cast_d(2);
                s_=s_next;
            }while(true);
        }
        inline double get_log_lambda(){
            rn_=rn_*lambda_*(1.0-rn_)*4096.0;
            rn_=fmod(rn_ , 1.0);
            return rn_;
        }
        inline int get_s(){
            return ((int)(get_log_lambda()*42949672))%4 + 2;
        }
        inline double cast_d(unsigned int input){
            return static_cast<double>(input);
        }
};
#endif