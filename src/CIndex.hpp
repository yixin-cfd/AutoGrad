#pragma once
#include <cstddef>
#include <type_traits>
#include "common.hpp"

namespace AD
{
    class CIndex
    {
    public:
        static index_t next; // È«¾ÖË÷Òý
        static void reset() noexcept { next = 0; }
    };

};