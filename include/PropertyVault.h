#pragma once

#include "Properties.h"
#include "PropertyBag.h"

class PropertyVault {
public:
  void add(std::function<PropertyFunctor (PropertyVector)> functor, PropertyBag bag) {
    for (auto &vector : bag) {
      add(functor(vector));
    }
  }

  void add(PropertyFunctor functor) {
    PrologCall::fact(functor.term());
  }

  PropertyQuery query(PropertyFunctor functor) {
    return PropertyQuery(functor);
  }
};

