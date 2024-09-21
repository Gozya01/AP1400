#ifndef Q1_H
#define Q1_H

#endif //Q1_H

#include <cmath>
#include <functional>
namespace q1{

    double gradient_descent(double start,double stp,std::function<double(double)> f){
        const double ex=1e-6;
        do{
            double k=(f(start+ex)-f(start))/ex;
            if(abs(k)<ex)break;
            start-=stp*k;
        }while(1);
        return start;
    }
    template <typename T, typename F>
    T gradient_descent(T init, T step) {
        return gradient_descent(init, step, F());
    }

}