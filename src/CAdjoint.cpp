#include "CAdjoint.hpp"

void AD::CAdjoint::Set(Real val, index_t idx)
{
    this->val_ = val;
    if (idx == 0) // 默认全局索引
    {
        assert(idx < std::numeric_limits<index_t>::max()); // 判断节点是否超出限制
        this->idx_ = ++CIndex::next;
    }
    else // 自行配置
    {
        this->idx_ = idx;
    }
}
