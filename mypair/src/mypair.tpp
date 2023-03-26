#include "mypair.h"

template <class T>
T mypair<T>::getmax()
{
    T retval;
    retval = a > b ? a : b;
    return retval;
}

// int main()
// {
//     mypair<int> myobject(100, 75);
//     cout << myobject.getmax();
//     return 0;
// }