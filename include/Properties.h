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

