#ifndef __MUTTINF__
#define __MUTTINF__
#include <vector>
#include <cmath>
class MuttInf{
    private:
        std::vector<double> dat;
        std::vector<double> mutual_inf;
        unsigned int num_mutual=200;
        double lim_inf;
        double lim_sup;
        double dt_;
        double arrist;
        double di_;
        double t_ignore=1;
        unsigned int n_=200;
        unsigned int N_;
        unsigned int **matrix;
        double *array_temp;
    public:
        MuttInf(){
            std::vector<double>().swap(dat);
            std::vector<double>().swap(mutual_inf);
            return;
        }
        MuttInf(std::vector<double > input, double dt){
            std::vector<double>().swap(dat);
            dt_=dt;
            unsigned int bottom=t_ignore/dt_;
            for (size_t i=bottom; i< input.size(); i++){
                dat.push_back(input[i]);
            }
            std::vector<double>().swap(mutual_inf);
            num_mutual=5.0/dt;
            return;
        }
        void set(std::vector<double > input, double dt){
            std::vector<double>().swap(dat);
            dt_=dt;
            unsigned int bottom=t_ignore/dt_;
            for (size_t i=bottom; i< input.size(); i++){
                dat.push_back(input[i]);
            }
            std::vector<double>().swap(mutual_inf);
            num_mutual=5.0/dt;
            return;
        }
        void init(double lim_i, double lim_s){
            lim_inf=lim_i;
            lim_sup=lim_s;
            arrist=fabs( lim_sup - lim_inf );
            di_=arrist/n_;
            make_grid();
            return;
        }
        void init(){
            double min=dat[0];
            double max=dat[0];
            for (int i=1; i<dat.size(); ++i){
                if (dat[i]>max)
                    max=dat[i];
                else{
                    if (dat[i]<min)
                        min=dat[i];
                }
            }
            arrist=fabs( max - min );
            lim_inf=min;
            di_=arrist/n_;
            make_grid();
            return;
        }
        void make(){
            make_test();
            return;
        }
        std::vector<double> get_dat(){
            free_grid();
            free_array();
            return mutual_inf;
        }
        int get_pos(){
            return get();
        }
        int get_tau(){
            return tau();
        }
        void clear(){
            free_grid();
            free_array();
        }
    private:
        void make_test(){
            make_array();
            clear_matrix();
            for (size_t i=0; i< num_mutual; i++){
                fill_matrix(i);
                mutual_inf.push_back(make_mutual_inf(i));
                clear_matrix();
            }
            return;
        }
        int tau(){
            make_array();
            clear_matrix();
            int top=dat.size()/2;
            double derivative;
            fill_matrix(0);
            mutual_inf.push_back(make_mutual_inf(0));
            clear_matrix();
            for (size_t i=1; i< top ; i++){
                fill_matrix(i);
                mutual_inf.push_back(make_mutual_inf(i));
                clear_matrix();
                derivative = (mutual_inf[i]-mutual_inf[i-1])/dt_;
                if (derivative>0){
                    return (i);
                }
            }
            return top;
        }
        void make_array(){
            array_temp= new double [n_];
            for (size_t i=0; i<n_ ; i++){
                array_temp[i]=lim_inf+di_*i;
            }
            return;
        }
        void free_array(){
            delete array_temp;
            return;
        }
        void free_grid(){
            for (size_t i=0; i<n_; i++)
                delete matrix[i];
            delete matrix;
            return;
        }
        void make_grid(){
            matrix= new unsigned int *[n_];
            for (size_t i=0; i<n_; i++)
                matrix[i]= new unsigned int [n_];
            clear_matrix();
            return;
        }
        void clear_matrix(){
            for (size_t i=0; i< n_; i++)
                for (size_t j=0; j<n_; j++)
                    matrix[i][j]=0;
            return;
        }
        void fill_matrix(unsigned int tau){
            double x;
            double y;
            size_t x_pos;
            size_t y_pos;
            size_t pivot;
            size_t bottom=0;
            size_t top=n_;
            for (size_t i=0; i< dat.size()-tau; i++){
                x=dat[i];
                y=dat[i+tau];
                bottom=0;
                top=n_;
                while (bottom+1!=top){
                    pivot=(top+bottom)/2;
                    if (x<=array_temp[pivot])
                        top=pivot;
                    else
                        bottom=pivot;
                }
                x_pos=pivot;
                bottom=0;
                top=n_;
                while (bottom+1!=top){
                    pivot=(top+bottom)/2;
                    if (y<=array_temp[pivot])
                        top=pivot;
                    else
                        bottom=pivot;
                }
                y_pos=pivot;
                matrix[x_pos][y_pos]++;
            }
            return;
        }
        double make_mutual_inf(size_t tau){
            double result=0.0;
            double entropy_px=0.0;
            double entropy_py=0.0;
            double entropy_pxpy=0.0;
            double pxpy;
            double max=(double)(dat.size()-tau);
            std::vector<double> px;
            for (size_t i=0; i<n_; i++){
                px.push_back(0.0);
            }
            for (size_t i=0; i<n_; ++i){
                double py=0.0;
                for (size_t j=0; j<n_; ++j){
                    px[j]+=(double)matrix[i][j];
                    py+=(double)matrix[i][j];
                    if (matrix[i][j]==0) continue;
                    pxpy=(double)matrix[i][j]/max;
                    entropy_pxpy+=(pxpy*log2(pxpy));
                }
                if (py==0.0) continue;
                py/=max;
                entropy_py+=(py*log2(py));
            }
            for (size_t i=0; i<n_; i++){
                double ppx=px[i]/max;
                if (ppx==0.0) continue;
                entropy_px+=(ppx*log2(ppx));
            }
            std::vector<double>().swap(px);
            return -entropy_px-entropy_py+entropy_pxpy;
        }
        int get(){
            double derivative;
            for (size_t i=0; i<mutual_inf.size(); ++i){
                derivative = (mutual_inf[i+1]-mutual_inf[i])/dt_;
                if (derivative>0){
                    return (i+1);
                }
            }
            return mutual_inf.size();
        }
};

#endif