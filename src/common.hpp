#pragma once
#include <cstddef>
#include <type_traits>
namespace AD
{
    using index_t = size_t; // ȫ����������
    using Real = double;    // ���ڰ������������, �����͵���

    template <typename T>
    using enable_if_arithmetic_t = std::enable_if_t<std::is_arithmetic_v<T>>; // �ж�����T�Ƿ�����������

};