#pragma once

#include <iostream>
using namespace std;

template <class T>
class mypair
{
    T a, b;

public:
    mypair(T first, T second)
    {
        a = first;
        b = second;
    }
    T getmax();
};

#include "mypair.tpp"