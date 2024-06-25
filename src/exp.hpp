#pragma once
#include <vector>
#include <functional>
#include "common.hpp"
#include "CTape.hpp"

namespace AD{
    inline CAdjoint exp(const CAdjoint& x){
        CAdjoint y(std::exp(x.val()));
        auto f=[=](std::vector<Real> &grad){
            grad[x.idx()] += y.val()*grad[y.idx()];
        };
        CTape::stack.emplace_back(f);
        return y;
    }
}