#include "CTape.hpp"

namespace AD
{
    std::vector<std::function<void(std::vector<Real> &)>> CTape::stack = {};
    bool CTape::record_flag = false;
}