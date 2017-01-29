// Copyright 2016 Annotator Team

#ifndef PKG_ANNOTATOR_ANNOTATORLIB
#define PKG_ANNOTATOR_ANNOTATORLIB

/************************************************************
 Pkg_AnnotatorLib package header
 ************************************************************/

#include <AnnotatorLib/annotatorlib_api.h>

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

std::string ANNOTATORLIB_API AttributeTypeToString(AttributeType type);

AttributeType ANNOTATORLIB_API AttributeTypeFromString(std::string str);

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
  MYSQL,
  /**
   *
   */
  SQLITE,
  /**
   *
   */
  JSON,
  /**
   *
   */
  MONGODB,
};

/**
 *
 */
enum class ImageSetType {

  UNKNOWN,
  CAMERA,
  VIDEO,
  IMAGEFOLDER,
  IMAGEFTP,
};

/**
 * @brief The AnnotationType enum
 */
enum class AnnotationType { ELLIPSE, RECTANGLE };

std::string ANNOTATORLIB_API StorageTypeToString(StorageType type);

StorageType ANNOTATORLIB_API StorageTypeFromString(std::string str);

/**
  Converts a String to an ImageSetType

 * @brief typeFromString
 * @param str
 * @return
 */
ImageSetType ANNOTATORLIB_API ImageSetTypeFromString(std::string str);

/**
  Converts ImageSetType to a String

 * @brief typeToString
 * @param type
 * @return
 */
std::string ANNOTATORLIB_API ImageSetTypeToString(ImageSetType type);

/**
 * @brief AnnotationTypeFromString
 * @param str
 * @return
 */
AnnotationType ANNOTATORLIB_API AnnotationTypeFromString(std::string str);

std::string ANNOTATORLIB_API AnnotationTypeToString(AnnotationType type);

}  // of namespace AnnotatorLib

/************************************************************
 End of Pkg_AnnotatorLib package header
 ************************************************************/

#endif
