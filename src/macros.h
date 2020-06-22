//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_MACROS_H
#define SOCIETY_MACROS_H

#include <memory>

#define SP(X) std::shared_ptr<X>
#define POINTERIZE(CLASS) typedef std::shared_ptr<CLASS> Ptr

#include <string>

template <typename T>
struct ReflectedType {
    std::string type;
    T *val;
};
#define REFLECT(TYPE, NAME) TYPE _##NAME; ReflectedType<TYPE> NAME{#TYPE, &_##NAME};
#define GET(TYPE, NAME, ACCESS) ACCESS: TYPE get_##NAME() { return _##NAME; }
#define SET(TYPE, NAME, ACCESS) ACCESS: void set_##NAME(TYPE val) { _##NAME = val; }
#define PVAR(TYPE, NAME, GET_ACCESS, SET_ACCESS) private: TYPE _##NAME; GET(TYPE, NAME, GET_ACCESS) SET(TYPE, NAME, SET_ACCESS)


#endif //SOCIETY_MACROS_H
