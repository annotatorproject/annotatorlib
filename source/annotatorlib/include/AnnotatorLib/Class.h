// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_CLASS_H
#define ANNOTATOR_ANNOTATORLIB_CLASS_H

#include <iostream>
#include <map>
#include <memory>
#include <string>

#include <AnnotatorLib/annotatorlib_api.h>

namespace AnnotatorLib {

/************************************************************/

/**
 * @brief The Class class
 * Represents a class that objects can affiliate to.
 */
class ANNOTATORLIB_API Class {
 public:
  const unsigned long id;
  const std::string name;

  /**
   * @brief Class constructor
   *
   * The id and the name will be generated automatically.
   */
  Class();

  /**
   * @brief Class constructor
   * @param name A for humans readable name for the class.
   *
   * The id will be generated automatically.
   */
  Class(std::string name);

  /**
   * @brief Class
   * @param id
   * @param name
   */
  Class(unsigned long id, std::string name);

  ~Class() {}

  /**
   *
   * @return id
   */
  static unsigned long genId();

  unsigned long getId() const;
  std::string getName() const;

  bool equals(Class *other);

  friend std::ostream &operator<<(std::ostream &stream,
                                  const AnnotatorLib::Class &c) {
    stream << "Class: " << c.getId() << "," << c.getName() << " ";
    return stream;
  }

  friend std::ostream &operator<<(
      std::ostream &stream, const std::shared_ptr<AnnotatorLib::Class> &c) {
    if (c) stream << *c;
    return stream;
  }

 private:
  static std::string genName();
};

typedef std::map<std::string, std::shared_ptr<Class>> ClassMap;

}  // of namespace AnnotatorLib

#endif
