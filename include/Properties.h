#pragma once

#include <PrologInterface.h>

#include <iostream>
#include <map>
#include <vector>

class PropertyValue {
public:
  PropertyValue();
  PropertyValue(PrologTerm term);

  PrologTerm term() const;

  std::string uuid() const;

protected:
  class UUID {
  public:
    UUID();
    UUID(std::string uuid);

    std::string str() const;

  private:
    std::string uuid_;
  };

  PropertyValue(UUID uuid, PrologTerm term);

private:
  UUID uuid_;
  PrologTerm term_;
};

class PropertyVariable : public PropertyValue {
public:
  PropertyVariable();

  // Get the PropertyValue this variable is bound to in a query.
  PropertyValue get() const;
};

class PropertyVector {
public:
  PropertyVector(std::initializer_list<PropertyValue> values);
  PropertyVector(std::vector<PropertyValue> values);
  PropertyVector(PrologTermVector terms);

  PrologTermVector term() const;

  size_t size() const;

private:
  PrologTermVector terms_;
};

class PropertyFunctor : public PropertyValue {
public:
  PropertyFunctor(std::string property, PropertyVector vector);
};

