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

  void query(PropertyFunctor functor, std::function<void ()> callback) {
    PropertyQuery(functor).apply(callback);
  }
};

