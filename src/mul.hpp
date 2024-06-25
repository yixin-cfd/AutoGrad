#pragma once
#include <vector>
#include <functional>
#include "common.hpp"
#include "CTape.hpp"

namespace AD{
    inline CAdjoint operator*(const CAdjoint&x1, const CAdjoint&x2){
        CAdjoint y(x1.val()*x2.val());
        auto f =[=](std::vector<Real>& grad){
            grad[x1.idx()] += x2.val()*grad[y.idx()];   // 本层函数对变量的导数 * 下游传递来的导数
            grad[x2.idx()] += x1.val()*grad[y.idx()];      
        };
        CTape::stack.emplace_back(f);
        return y;
    }

    template<typename T, typename=enable_if_arithmetic_t<T>>
    inline CAdjoint operator*(const CAdjoint&x1, T x2){
        CAdjoint y(x1.val()*x2);
        CTape::stack.emplace_back([=](std::vector<Real> &grad){
            grad[x1.idx()] += x2*grad[y.idx()];
        });
        return y;
    }

    template<typename T, typename=enable_if_arithmetic_t<T>>
    inline CAdjoint operator*(T x1, const CAdjoint&x2){
        CAdjoint y(x1*x2.val());
        CTape::stack.emplace_back([=](std::vector<Real> &grad){
            grad[x2.idx()] += x1*grad[y.idx()];
        });
        return y;
    }
}