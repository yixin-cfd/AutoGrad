#pragma once
#include <vector>
#include <functional>
#include "common.hpp"
#include "CTape.hpp"

namespace AD{
    template<typename T, typename=enable_if_arithmetic_t<T>>
    inline CAdjoint pow(const CAdjoint& x, T p){
        CAdjoint y(std::pow(x.val(), p));
        auto f =[=](std::vector<Real> & grad){
            grad[x.idx()] += grad[y.idx()] * p*std::pow(x.val(), p-1.0);
        };
        CTape::stack.emplace_back(f);
        return y;
    }
}