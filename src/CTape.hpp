#pragma once
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>
#include <cstddef>
#include <functional>
#include <unordered_map>
#include <algorithm>
#include "common.hpp"
#include "CIndex.hpp"
#include "CAdjoint.hpp"

namespace AD
{
    class CAdjoint;
    class CTape
    {
    private:
        std::vector<Real> dydx; // 存储y(单个)对x(多个)的导数
        static void reset_()
        {
            CIndex::reset();
            stack.clear();
        } //
    public:
        static std::vector<std::function<void(std::vector<Real> &)>> stack; // 存储函数
    public:
        void reset()
        {
            reset_();
            dydx.clear();
        }

        void evalute(const CAdjoint &y)
        {
            assert(y.idx() < std::numeric_limits<index_t>::max());
            dydx.resize(CIndex::next + 1); // 存储导数
            fill(dydx.begin(), dydx.end(), 0.0);
            dydx[y.idx()] = 1;
#if 0
            std::cout << "(";
            for (int i = 0; i < dydx.size(); i++)
            {
                std::cout << dydx[i] << ", ";
            }
            std::cout << ")" << std::endl;
#endif
            for (auto chain_f = stack.crbegin(); chain_f != stack.crend(); ++chain_f) // 链式法则，反向进行
            {
                (*chain_f)(dydx); // 逐步更新导数
            }
#if 0
            std::cout << "(";
            for (int i = 0; i < dydx.size(); i++)
            {
                std::cout << dydx[i] << ", ";
            }
            std::cout << ")" << std::endl;
#endif
        }

        Real getGradient(const CAdjoint &x)
        {
            return dydx[x.idx()];
        }
    };

}