#include "Properties.h"

/**
 * PropertyValue
 */
static int next_uuid() {
  static unsigned int current_uuid = 0;
  return current_uuid++;
}

PropertyValue::UUID::UUID()
    : UUID(std::to_string(next_uuid())) {
}

PropertyValue::UUID::UUID(std::string uuid)
    : uuid_(uuid) {
}

std::string PropertyValue::UUID::str() const {
  return uuid_;
}

PropertyValue::PropertyValue()
    : uuid_(), term_(PrologString(uuid())) {
}

PropertyValue::PropertyValue(PrologTerm term)
    : term_(term) {
}

PropertyValue::PropertyValue(UUID uuid, PrologTerm term)
    : uuid_(uuid), term_(term) {
}

PrologTerm PropertyValue::term() const {
  return term_;
}

std::string PropertyValue::uuid() const {
  return uuid_.str();
}

