#pragma once

#include <array>


namespace containers
{

// TODO: add error codes
template <typename Type, std::size_t BufferSize>
class StaticVector
{
public:
    StaticVector() : firstFreePosition_(0)
    {
    }

    void push_back(const Type& data)
    {
        if (firstFreePosition_ >= BufferSize)
        {
            return;
        }

        data_[firstFreePosition_] = data;
        ++firstFreePosition_;
    }

    std::size_t size() const
    {
        return firstFreePosition_;
    }

    Type pop_back()
    {
        if (0 == firstFreePosition_)
        {
            return {};
        }
        --firstFreePosition_;
        return data_[firstFreePosition_];
    }

    Type get_last()
    {
        if (0 == size())
        {
            return {};
        }

        return data_[firstFreePosition_ - 1];
    }

private:
    std::size_t firstFreePosition_;
    std::array<Type, BufferSize> data_;
};

} // namespace containters
