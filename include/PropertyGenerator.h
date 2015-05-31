#pragma once

#include "Properties.h"

#include <vector>
#include <functional>

template<typename T>
class PropertyGenerator : public std::vector<T> {
public:
  PropertyGenerator() {}

  template<typename U>
  PropertyGenerator(U begin, U end, std::function<T (U)> conv) {
    for (auto it = begin; it != end; ++it) {
      this->push_back(conv(it));
    }
  }

  template<typename U, typename I>
  PropertyGenerator(U iterable, std::function<T (I)> conv) {
    for (auto& it : iterable) {
      this->push_back(conv(it));
    }
  }

  template<typename U>
  PropertyGenerator(U iterable) {
    for (auto& it : iterable) {
      this->push_back(it);
    }
  }
};

