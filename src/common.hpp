#pragma once
#include <cstddef>
#include <type_traits>
namespace AD
{
    using index_t = size_t; // 全局索引类型
    using Real = double;    // 用于伴随的数据类型, 变量和导数

    template <typename T>
    using enable_if_arithmetic_t = std::enable_if_t<std::is_arithmetic_v<T>>; // 判断类型T是否是算数类型

};