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
        std::vector<Real> dydx; // �洢y(����)��x(���)�ĵ���
        static void reset_()
        {
            CIndex::reset();
            stack.clear();
            record_flag = false;
        } //
        static bool record_flag;        // �Ƿ�ʼ�洢����
    public:
        static std::vector<std::function<void(std::vector<Real> &)>> stack; // �洢����
        static bool IsRecord(void){return record_flag;} // �Ƿ�ʼ�洢�������ⲿ����
    public:
        void reset()
        {
            reset_();
            dydx.clear();
        }

        void record(bool flag){record_flag = flag;}

        void evalute(const CAdjoint &y)
        {
            assert(y.idx() < std::numeric_limits<index_t>::max());
            dydx.resize(CIndex::next + 1); // �洢����
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
            for (auto chain_f = stack.crbegin(); chain_f != stack.crend(); ++chain_f) // ��ʽ���򣬷������
            {
                (*chain_f)(dydx); // �𲽸��µ���
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