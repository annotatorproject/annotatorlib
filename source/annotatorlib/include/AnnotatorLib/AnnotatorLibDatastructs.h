

#ifndef PKG_ANNOTATOR_ANNOTATORLIB
#define PKG_ANNOTATOR_ANNOTATORLIB

/************************************************************
 Pkg_AnnotatorLib package header
 ************************************************************/

#include <string>

/* Package dependency header include                        */

namespace AnnotatorLib {

// Types defined within the package
/**
 *
 */
enum class AttributeType {
  /**
   *
   */
  STRING,
  /**
   *
   */
  BOOLEAN,
  /**
   *
   */
  INTEGER,
  /**
   *
   */
  FLOAT,
  /**
    *
    */
  UNKNOWN,
};

std::string AttributeTypeToString(AttributeType type);

AttributeType AttributeTypeFromString(std::string str);

/**
 *
 */
enum class StorageType {

  UNKNOWN,
  /**
   *
   */
  XML,
  /**
   *
   */
  SQL,
  /**
   *
   */
  SQLITE,
  /**
   *
   */
  JSON,
};

std::string StorageTypeToString(StorageType type);

StorageType StorageTypeFromString(std::string str);

/**
 *
 */
enum class ImageSetType {

  UNKNOWN,
  CAMERA,
  VIDEO,
  IMAGEFOLDER,
};

/**
  Converts a String to an ImageSetType

 * @brief typeFromString
 * @param str
 * @return
 */
ImageSetType ImageSetTypeFromString(std::string str);

/**
  Converts ImageSetType to a String

 * @brief typeToString
 * @param type
 * @return
 */
std::string ImageSetTypeToString(ImageSetType type);

/**
 * @brief The AnnotationType enum
 */
enum class AnnotationType { ELLIPSE, RECTANGLE };

/**
 * @brief AnnotationTypeFromString
 * @param str
 * @return
 */
AnnotationType AnnotationTypeFromString(std::string str);

std::string AnnotationTypeToString(AnnotationType type);

}  // of namespace AnnotatorLib

/************************************************************
 End of Pkg_AnnotatorLib package header
 ************************************************************/

#endif
