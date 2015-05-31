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

/**
 * PropertyVariable
 */
PropertyVariable::PropertyVariable()
    : PropertyValue(PrologVariable()) {
}

PropertyValue PropertyVariable::get() const {
  // All non-variable properties should be strings with valid UUIDs.
  return PropertyValue(term().asString());
}

/**
 * PropertyVector
 */
static std::vector<PrologTerm> asPrologTerms(std::vector<PropertyValue> values) {
  std::vector<PrologTerm> terms;
  for (auto value : values) {
    terms.push_back(value.term());
  }
  return terms;
}

PropertyVector::PropertyVector(std::initializer_list<PropertyValue> values)
    : terms_(asPrologTerms(values)) {
}

PropertyVector::PropertyVector(std::vector<PropertyValue> values)
    : terms_(asPrologTerms(values)) {
}

PropertyVector::PropertyVector(PrologTermVector terms)
    : terms_(terms) {
}

PrologTermVector PropertyVector::term() const {
  return terms_;
}

size_t PropertyVector::size() const {
  return terms_.size();
}

/**
 * PropertyFunctor
 */
PropertyFunctor::PropertyFunctor(std::string property, PropertyVector vector)
    : PropertyValue(PrologFunctor(property, vector.term())) {
}

/**
 * PropertyQuery
 */
PropertyQuery::PropertyQuery(PropertyFunctor functor)
    : query_(functor.term().asFunctor()) {
}

void PropertyQuery::apply(std::function<void ()> callback) {
  query_.apply([&](PrologTermVector) {
    callback();
  });
}

