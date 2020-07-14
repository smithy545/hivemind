//
// Created by Philip on 6/1/2020.
//

#ifndef SOCIETY_MACROS_H
#define SOCIETY_MACROS_H

#include <boost/preprocessor.hpp>
#include <memory>
#include <string>
#include <utility>
#include <vector>


#define POINTERIZE(CLASS) typedef std::shared_ptr<CLASS> Ptr
#define SP(X) std::shared_ptr<X>
#define EMPTY
#define MOVE(X) std::move(X)
#define NOOP(...)
#define ID(X) X

// Private var base
#define _DECLARE(TYPE, NAME, ACCESS) ACCESS: TYPE _##NAME
#define _VAR(TYPE, NAME, GETTER, GET_ACCESS, SETTER, SET_ACCESS) GETTER(NAME, TYPE, GET_ACCESS) SETTER(NAME, TYPE, SET_ACCESS) _DECLARE(TYPE, NAME, private)

// Base getter/setter
#define GETFUNC(NAME, TYPE, ACCESS, PRE, PREFIX, POST) ACCESS: PRE TYPE PREFIX##_##NAME() POST { return _##NAME; }
#define SETFUNC(NAME, TYPE, ACCESS, PRE, PREFIX, VALUE_MOD) ACCESS: PRE void PREFIX##_##NAME(TYPE val) { _##NAME = VALUE_MOD(val); }

// Useful Getter/Setter permutations
#define GET(NAME, TYPE, ACCESS) GETFUNC(NAME, TYPE, ACCESS, inline, get, EMPTY)
#define GET_BOOL(NAME, _, ACCESS) GETFUNC(NAME, bool, ACCESS, inline, is,  EMPTY)
#define GET_CONST(NAME, TYPE, ACCESS) GETFUNC(NAME, TYPE, ACCESS, inline, get, const)
#define SET(NAME, TYPE, ACCESS) SETFUNC(NAME, TYPE, ACCESS, inline, set, ID)
#define MOVE_AND_SET(NAME, TYPE, ACCESS) SETFUNC(NAME, TYPE, ACCESS, inline, set, MOVE)
#define GET_REF(NAME, TYPE, ACCESS) GETFUNC(NAME, TYPE, ACCESS, inline, &get, EMPTY)
#define SET_REF(NAME, TYPE, ACCESS) SETFUNC(NAME, TYPE##&, ACCESS, inline, set, ID)

// CONSTVAR: const var
#define _CONSTVAR(TYPE, NAME, ACCESS) _VAR(TYPE, NAME, GET_CONST, ACCESS, NOOP, EMPTY)

// Useful permutations of var base
#define _VAR_GET(TYPE, NAME, ACCESS) _VAR(TYPE, NAME, GET, ACCESS, NOOP, EMPTY)
#define _VAR_SET(TYPE, NAME, ACCESS) _VAR(TYPE, NAME, NOOP, EMPTY, SET, ACCESS)
#define _VAR_GETSET(TYPE, NAME, GET_ACCESS, SET_ACCESS) _VAR(TYPE, NAME, GET, GET_ACCESS, SET, SET_ACCESS)

// BVAR: boolean var gets use "isX" instead of "getX"
#define _BVAR_GETSET(NAME, GET_ACCESS, SET_ACCESS) _VAR(bool, NAME, GET_BOOL, GET_ACCESS, SET, SET_ACCESS)
#define _BVAR_GET(NAME, ACCESS) _VAR(bool, NAME, GET_BOOL, ACCESS, NOOP, EMPTY)

// MVAR: var that gets moved on set
#define _MVAR_SET(TYPE, NAME, ACCESS) _VAR(TYPE, NAME, NOOP, EMPTY, MOVE_AND_SET, ACCESS)
#define _MVAR_GETSET(TYPE, NAME, GET_ACCESS, SET_ACCESS) _VAR(TYPE, NAME, GET, GET_ACCESS, MOVE_AND_SET, SET_ACCESS)

// REFVAR: var that is moved with refs
#define _REFVAR_GET(TYPE, NAME, ACCESS) _VAR(TYPE, NAME, GET_REF, ACCESS, NOOP, EMPTY)
#define _REFVAR_SET(TYPE, NAME, ACCESS) _VAR(TYPE, NAME, NOOP, EMPTY, SET_REF, ACCESS)
#define _REFVAR_GETSET(TYPE, NAME, GET_ACCESS, SET_ACCESS) _VAR(TYPE, NAME, GET_REF, GET_ACCESS, SET_REF, SET_ACCESS)


#endif //SOCIETY_MACROS_H
