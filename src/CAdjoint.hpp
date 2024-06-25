#pragma once
#include <cmath>
#include <cassert>
#include <limits>
#include <iostream>
#include <cstddef>
#include <functional>
#include <type_traits>
#include "common.hpp"
#include "CIndex.hpp"

/// @brief 自动微分命名空间
/// @author JLX
/// @date 2024-6-25
/// @ref https://github.com/bob-carpenter/ad-handbook.git
namespace AD
{

    /// @brief 用于伴随的节点变量类型
    class CAdjoint
    {
    private:
        Real val_;    // 变量值
        index_t idx_; // 变量全局索引

    public:
        CAdjoint(){};
        CAdjoint(Real val, index_t idx = 0) { Set(val, idx); };
        void Set(Real val, index_t idx = 0);
        inline Real val() const noexcept { return val_; }
        inline Real idx() const noexcept { return idx_; }

        friend std::ostream &operator<<(std::ostream &o, const CAdjoint &y)
        {
            o << "(" << y.val() << ", " << y.idx() << ")";
            return o;
        }
    };

} // namespace: AD
