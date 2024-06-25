#pragma once
#include <vector>
#include <functional>
#include "common.hpp"
#include "CTape.hpp"

namespace AD
{
    inline CAdjoint sqrt(const CAdjoint &x)
    {
        CAdjoint y(std::sqrt(x.val()));
        auto f = [=](std::vector<Real> &grad)
        {
            grad[x.idx()] += 0.5 *grad[y.idx()]/ y.val();
        };
        CTape::stack.emplace_back(f);
        return y;
    }
}