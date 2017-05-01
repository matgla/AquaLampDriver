#pragma once

#include <array>

#include "types.hpp"

template <std::size_t BUF_SIZE>
class Buffer
{
  public:
    Buffer()
        : writerIndex_(0),
          readerIndex_(0),
          size_(0)
    {
    }

    template <typename Type>
    u16 write(Type ch)
    {
        if (writerIndex_ >= BUF_SIZE)
        {
            writerIndex_ = 0;
        }
        incrementSize();
        buffer_[writerIndex_++] = ch;
        return writerIndex_;
    }

    template <typename Type>
    u16 write(Type ch, int offset)
    {
        if (writerIndex_ >= BUF_SIZE)
        {
            writerIndex_ = 0;
        }
        incrementSize();
        buffer_[writerIndex_ + offset] = ch;
        return ++writerIndex_;
    }

    template <typename Type>
    void write(Type *str)
    {
        for (int i = 0; i < strlen(str); ++i)
        {
            write(str[i]);
        }
    }

    u8 getByte()
    {
        if (size_)
        {
            if (readerIndex_ >= BUF_SIZE)
            {
                readerIndex_ = 0;
            }
            size_--;
            return buffer_[readerIndex_++];
        }
        return 0;
    }

    bool getValue(u16 offset, u8 &value)
    {
        if (offset >= size_)
        {
            return false;
        }

        if (size_)
        {
            int tempIndex = readerIndex_;
            if (tempIndex >= BUF_SIZE)
            {
                tempIndex = 0;
            }
            value = buffer_[tempIndex + offset];
            return true;
        }
        return false;
    }

    bool removeFromBuffer(u16 pos)
    {
        if (size_)
        {
            int nrOfBytesAfterPos = size() - pos;
            for (int i = 0; i < nrOfBytesAfterPos; ++i)
            {
                int currentPos = readerIndex_;
                if (readerIndex_ + pos + i >= BUF_SIZE)
                {
                    currentPos = 0;
                }
                u8 value;

                if (!getValue(i + pos + 1, value))
                {
                    buffer_[currentPos + pos + i] = value;
                    break;
                }
                buffer_[currentPos + pos + i] = value;
            }
            --size_;

            if (writerIndex_ == 0)
            {
                writerIndex_ = BUF_SIZE;
            }
            else
            {
                --writerIndex_;
            }
        }
        return false;
    }

    u8 *getData()
    {
        return buffer_;
    }

    u16 size()
    {
        return size_;
    }

    void flush()
    {
        writerIndex_ = 0;
        readerIndex_ = 0;
        size_ = 0;
    }

  private:
    void incrementSize()
    {
        if (size_ < BUF_SIZE)
        {
            ++size_;
        }
        else
        {
            ++readerIndex_;
        }
    }
    volatile u8 buffer_[BUF_SIZE];
    volatile u16 writerIndex_;
    volatile u16 readerIndex_;
    volatile u16 size_;
};