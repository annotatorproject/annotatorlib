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

    /**
     *
     * @return id
     */
    static unsigned long genId();

    unsigned long getId() const;
    std::string getName() const;

    bool equals(Class *other);

private:
    static std::string genName();
};

} // of namespace AnnotatorLib

#endif
