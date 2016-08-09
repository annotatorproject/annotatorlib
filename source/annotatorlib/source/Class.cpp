#define Annotator_AnnotatorLib_Class_BODY

// include associated header file
#include "AnnotatorLib/Class.h"
#include <exception>
#include <sstream>
#include <stdexcept>

// Derived includes directives

namespace AnnotatorLib {

// static attributes
static long lastId = 110000;

/**
 * @brief Attribute::Attribute
 * @param id
 * @param type
 * @param name
 */
Class::Class(unsigned long id)
{
    this->id = id;
}

Class::Class(unsigned long id, std::string name) {
  this->id = id;
  this->name = name;
}

unsigned long Class::genId() {
  lastId += 7;
  return lastId;
}

unsigned long Class::getId() { return id; }

void Class::setName(std::string name) { this->name = name; }

std::string Class::getName() { return name; }

bool Class::equals(Class *other) {
  if (this == other)
    return true;
  if (this->name != other->name)
    return false;
  return true;
}

} // of namespace AnnotatorLib
