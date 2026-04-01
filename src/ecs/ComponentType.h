/*
 *  ComponentType.h
 *  Defines static IDs for each component type.
 */

#ifndef MAZIAC_COMPONENTTYPE_H
#define MAZIAC_COMPONENTTYPE_H
#include <cstddef>

// creating a type alias for std:size_t
// size_t is designed to represent sizes and indices because its unsigned (positive) and it's very large (long long)
using ComponentTypeID = std::size_t;

// free function: any function that is not a member of a class or struct
// when you have a free function defined in a header, each .cpp that includes this header would get its own definition,
// causing a linker error. using inline merges them into one definition

// global counter generator
// returns a unique number every time we call it
// making id static = id will keep its value through multiple calls of this function
inline ComponentTypeID getComponentTypeID() {
    static ComponentTypeID id = 0;
    return id++;
}

// overloads the function above because they have different signatures
// template allows us to use generic types and is inline by default
// allows us to have different versions of the function:
//   getComponentTypeID<Position>() -> always returns 0
//   getComponentTypeID<Health>() -> would always return 1
// a static local variable is created for every component type - every time I call with the same typename, it returns the same ID
template <typename T>
ComponentTypeID getComponentTypeID() {
    static ComponentTypeID typeID = getComponentTypeID();
    return typeID;
}

#endif //MAZIAC_COMPONENTTYPE_H