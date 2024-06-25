#pragma once
#include <vector>
#include <functional>
#include "common.hpp"
#include "CTape.hpp"

namespace AD{
    inline CAdjoint operator-(const CAdjoint& x){
        CAdjoint y(-x.val());
        auto f=[=](std::vector<Real>& grad){
            grad[x.idx()] -= grad[y.idx()];
        };
        CTape::stack.emplace_back(f);
        return y;
    }
}