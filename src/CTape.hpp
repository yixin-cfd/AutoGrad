#pragma once
#include <cassert>
#include <limits>
#include <vector>
#include <cstddef>
#include <functional>
#include <unordered_map>
#include "common.hpp"
#include "CIndex.hpp"
#include "CAdjoint.hpp"

namespace AD
{
    class CAdjoint;
    class CTape
    {
    private:
        std::vector<Real> dydx; // �洢y(����)��x(���)�ĵ���
        static void reset_()
        {
            CIndex::reset();
            stack.clear();
        } //
    public:
        static std::vector<std::function<void(std::vector<Real> &)>> stack; // �洢����
    public:
        void reset()
        {
            reset_();
            dydx.clear();
        }

        void evalute(const CAdjoint &y)
        {
            assert(y.idx() < std::numeric_limits<index_t>::max());
            dydx.resize(y.idx() + 1, 0.0);  // �洢����
            dydx[y.idx()] = 1;
            for (auto chain_f = stack.crbegin(); chain_f != stack.crend(); ++chain_f) // ��ʽ���򣬷������
            {
                (*chain_f)(dydx); // �𲽸��µ���
            }
            
        }

        Real getGradient(const CAdjoint &x)
        {
            return dydx[x.idx()];
        }
    };

}