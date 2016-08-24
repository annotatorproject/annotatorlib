#ifndef ANNOTATOR_ANNOTATORLIB_CLASS_H
#define ANNOTATOR_ANNOTATORLIB_CLASS_H

#include <AnnotatorLib/annotatorlib_api.h>
#include <string>

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

    Class();

    /**
     * @brief Class
     * @param name A for humans readable name for the class.
     *
     * The id will be generated automatically.
     */
    Class(std::string name);

    Class(unsigned long id, std::string name);

    /**
     *
     * @return id
     */
    static unsigned long genId();

    unsigned long getId() const;
    std::string getName() const;

    bool equals(Class *other);

};

} // of namespace AnnotatorLib

#endif
