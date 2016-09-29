#define Annotator_AnnotatorLib_Class_BODY

// include associated header file
#include "AnnotatorLib/Class.h"
#include <exception>
#include <sstream>
#include <stdexcept>

// Derived includes directives

namespace AnnotatorLib {

// static attributes
static unsigned long lastId = 110000;
static unsigned long lastNamePostfix = 0;

Class::Class() : id(genId()), name(genName()) {}

Class::Class(std::string name) : id(genId()), name(name) {}

Class::Class(unsigned long id, std::string name) : id(id), name(name) {
  if (lastId < id) lastId = id;
}

unsigned long Class::genId() { return lastId += 7; }

std::string Class::genName() {
  return "unnamed_class_" + std::to_string(lastNamePostfix++);
}

unsigned long Class::getId() const { return id; }

std::string Class::getName() const { return name; }

bool Class::equals(Class *other) {
  if (this == other) return true;
  if (this->name != other->name) return false;
  return true;
}

}  // End of namespace AnnotatorLib
