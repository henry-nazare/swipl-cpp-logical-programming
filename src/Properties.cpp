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
  return PropertyValue(term().asString().str(), term().asString());
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
 * PropertyList
 */
PropertyList::PropertyList(std::vector<PropertyValue> vector)
    : PropertyValue(PrologList(asPrologTerms(vector))) {
}

/**
 * PropertyConjunction
 */
PropertyConjunction::PropertyConjunction(PropertyList args)
    : PropertyValue(PrologConjunction(args.term().asList())) {
}

/**
 * PropertySolution
 */
PropertySolution::PropertySolution(PrologSolution solution)
    : solution_(solution) {
}

PropertyValue PropertySolution::get(PropertyValue var) const {
  PrologTerm res = solution_.get(var.term());
  return PropertyValue(res.asString().str(), res);
}

/**
 * PropertyQuery
 */
PropertyQuery::PropertyQuery(PropertyFunctor functor)
    : query_(functor.term().asFunctor()) {
}

std::vector<PropertySolution> PropertyQuery::solutions() const {
  std::vector<PropertySolution> solutions;
  for (auto &solution : query_.solutions()) {
    solutions.push_back(PropertySolution(solution));
  }
  return solutions;
}

bool std::less<PropertyValue>
    ::operator()(const PropertyValue& lhs, const PropertyValue& rhs) const {
  return std::less<std::string>()(lhs.uuid(), rhs.uuid());
}

