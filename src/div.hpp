#pragma once
#include <vector>
#include <functional>
#include "common.hpp"
#include "CTape.hpp"

namespace AD
{
    inline CAdjoint operator/(const CAdjoint &x1, const CAdjoint &x2)
    {
        CAdjoint y(x1.val() / x2.val());
        auto f = [=](std::vector<Real> &grad)
        {
            grad[x1.idx()] += grad[y.idx()] / x2.val();
            grad[x2.idx()] -= x1.val() * grad[y.idx()] / (x2.val() * x2.val());
        };
        if (CTape::IsRecord())
            CTape::stack.emplace_back(f);
        return y;
    }

    template <typename T, typename = enable_if_arithmetic_t<T>>
    inline CAdjoint operator/(const CAdjoint &x1, T x2)
    {
        CAdjoint y(x1.val() / x2);
        auto f = [=](std::vector<Real> &grad)
        {
            grad[x1.idx()] += grad[y.idx()] / x2;
        };
        if (CTape::IsRecord())
            CTape::stack.emplace_back(f);
        return y;
    }

    template <typename T, typename = enable_if_arithmetic_t<T>>
    inline CAdjoint operator/(T x1, const CAdjoint &x2)
    {
        CAdjoint y(x1 / x2.val());
        auto f = [=](std::vector<Real> &grad)
        {
            grad[x2.idx()] -= x1 * grad[y.idx()] / (x2.val() * x2.val());
        };
        if (CTape::IsRecord())
            CTape::stack.emplace_back(f);
        return y;
    }

}
