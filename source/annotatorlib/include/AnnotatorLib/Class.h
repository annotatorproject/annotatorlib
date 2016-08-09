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

    /**
     * @brief Class
     * @param id The internally used for classes used unique id.
     */
    Class(unsigned long id);

    /**
     * @brief Class
     * @param id The internally used for classes used unique id.
     * @param name A for humans readable name for the class.
     */
    Class(unsigned long id, std::string name);

    /**
     * @brief Class
     * @param name A for humans readable name for the class.
     *
     * The id will be generated automatically.
     */
    Class(std::string name);

	/**
	 * 
	 * @return id 
	 */
    static unsigned long genId();

    unsigned long getId();

    void setName(std::string name);
    std::string getName();

    bool equals(Class *other);

protected:
	/**
	 * 
	 */
    unsigned long id;

    std::string name;

};

} // of namespace AnnotatorLib

#endif
