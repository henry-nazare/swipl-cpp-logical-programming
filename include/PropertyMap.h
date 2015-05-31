#pragma once

#include "Properties.h"
#include "PropertyGenerator.h"

template<typename T>
class PropertyMap {
public:

  template<typename U>
  class LookupResult {
  public:
    LookupResult(U result, U end)
      : result(result), end(end) {
    }

    bool isPresent() const {
      return result != end;
    }

    U get() const {
      assert(isPresent() && "get() called on invalid result");
      return result;
    }

  private:
    U result, end;
  };

  void put(PropertyValue property, T item) {
    type_property_map_.insert(std::make_pair(item, property));
    property_type_map_.insert(std::make_pair(property, item));
  }

  PropertyValue get(T item) const {
    return lookup(item).get()->second;
  }

  T get(PropertyValue property) const {
    property_type_map_.find(property),
    return lookup(property).get()->second;
  }

  LookupResult<typename std::map<PropertyValue, T>::const_iterator>
      lookup(PropertyValue property) const {
    return LookupResult<typename std::map<PropertyValue, T>::const_iterator>(
        property_type_map_.find(property),
        property_type_map_.end());
  }

  LookupResult<typename std::map<T, PropertyValue>::const_iterator>
      lookup(T item) const {
    return LookupResult<typename std::map<T, PropertyValue>::const_iterator>(
        type_property_map_.find(item),
        type_property_map_.end());
  }

  static PropertyMap<T> fromGenerator(PropertyGenerator<T> generator) {
    PropertyMap<T> map;
    for (auto& item : generator) {
      map.put(PropertyValue(), item);
    }
    return map;
  }

private:
  std::map<T, PropertyValue> type_property_map_;
  std::map<PropertyValue, T> property_type_map_;
};
