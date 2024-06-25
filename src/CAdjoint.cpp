#include "CAdjoint.hpp"

void AD::CAdjoint::Set(Real val, index_t idx)
{
    this->val_ = val;
    if (idx == 0) // Ĭ��ȫ������
    {
        assert(idx < std::numeric_limits<index_t>::max()); // �жϽڵ��Ƿ񳬳�����
        this->idx_ = ++CIndex::next;
    }
    else // ��������
    {
        this->idx_ = idx;
    }
}
