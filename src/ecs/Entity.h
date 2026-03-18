//
// Created by kate on 2026-01-21.
//

#ifndef COMP8051_ENTITY_H
#define COMP8051_ENTITY_H
#include <array>
#include <bitset>
#include <cstddef>

#include "ComponentType.h"

// constexpr means that this computation happens at compile time rather than run time to improve the performance
// 32 components fits perfectly in a 32-bit integer
// we limit the components to 32 bc we very rarely will have more than 32, unless its a bigger game
constexpr std::size_t MAX_COMPONENTS = 32;

// bitset is an array that has values of either 0 or 1
// bitset[5] = 1 -> entity has component 5
// allows you to check if an entity has a certain component
// one bit for each possible component
// bit operations are fast, and work well for checking each frame
using ComponentBitSet = std::bitset<MAX_COMPONENTS>;

// a fixed size array where each index is a component, value is the pointer to the component itself
// the index corresponds to the ComponentTypeID
// we use a fixed number of components so there is no dynamic allocation for the array
using ComponentArray = std::array<void*, MAX_COMPONENTS>;

class Entity {
  // if active is false, delete entity
  bool active = true;

  ComponentArray componentArray{};
  ComponentBitSet componentBitSet{};

public:
  bool isActive() {
    return active;
  }
  void destroy() {
    active = false;
  }

  // templates need to be implemented in header, not the cpp file
  // templates let you write generic functions, classes and variables that can operate with different data types without having to rewrite the same code for each
  // entity.hasComponent<Position>() -> returns true or false
  template<typename T>
  bool hasComponent() {
    return componentBitSet[getComponentTypeID<T>()];
  }

  // template that can receive multiple arguments
  // entity.addComponent<Position>(4, 5)
  // entity.addComponent<Health>(100)
  template<typename T, typename... mArgs>
  T& addComponent(mArgs&&...args) {
    // lvalue: an object that has an identifiable, persistent memory location
    // rvalue: a temporary value that does not persist beyond the expression that it uses
    // usually, when you pass arguments into a function, they all get changed to lvalues (which is inefficient)

    // implements perfect forwarding - passes its arguments to another function while preserving the og arguments' value categories
    // doesn't convert passed in parameters to lvalues
    // this is more efficient with moves and temporaries
    // old style c++ initialization
    T* component(new T{std::forward<mArgs>(args)...});
    // add the new component to the array
    componentArray[getComponentTypeID<T>()] = component;

    // update the bitset to true
    componentBitSet[getComponentTypeID<T>()] = true;

    // return dereferenced version of component
    return *component;
  }

  // not returning T because don't wanna make a copy
  // not returning T* because harder to work with
  template<typename T>
  T& getComponent() {
    // auto keyword detects the type of variable based on the value you assign to it
    auto ptr(componentArray[getComponentTypeID<T>()]);

    // static cast forces the compiler to consider all possible conversion methods from one type to another
    // e.g. void pointer would be cast to a position
    // return the dereferenced version of the pointer
    return *static_cast<T*>(ptr);
  }

  template<typename T>
  void deactivateComponent() {
    componentBitSet[getComponentTypeID<T>()] = false;
  }
};

#endif //COMP8051_ENTITY_H

























