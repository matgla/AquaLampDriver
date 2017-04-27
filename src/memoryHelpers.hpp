#pragma once

struct Deleter
{
    template <typename T>
    void operator()(T *obj)
    {
        free(obj);
    }
};