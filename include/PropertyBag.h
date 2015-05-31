#pragma once

#include "PropertyMap.h"

#include <vector>
#include <functional>

class PropertyBag : public std::vector<PropertyVector> {
public:
  template<typename T>
  PropertyBag(
      PropertyMap<T> map,
      PropertyGenerator<T> first,
      PropertyGenerator<T> second)
      : PropertyBag(map, first, map, second) {
  }

  template<typename T, typename U>
  PropertyBag(PropertyMap<T> fmap, PropertyGenerator<T> first, PropertyMap<U> smap, PropertyGenerator<U> second) {
    auto fit = first.begin(), fend = first.end();
    auto sit = second.begin(), send = second.end();
    for (; fit != fend && sit != send; ++fit, ++sit) {
      push_back(PropertyVector({fmap.get(*fit), smap.get(*sit)}));
    }
  }
};

