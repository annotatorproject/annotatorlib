// Copyright 2016-2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_IMAGEFOLDER_H
#define ANNOTATOR_ANNOTATORLIB_IMAGEFOLDER_H

/************************************************************
 ImageFolder class header
 ************************************************************/

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/ImageSet/ImageSet.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <string>
#include <vector>

#include <boost/filesystem.hpp>

namespace AnnotatorLib {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API ImageFolder : public ImageSet {
 public:
  ImageFolder(std::string path);

  /**
   *
   * @return type
   */
  virtual ImageSetType getType() override;

  /**
   * @brief getImage
   * @param position
   * @return
   */
  virtual Image getImage(unsigned long position) override;

  virtual std::string getImagePath(unsigned long position) override;

  virtual bool gotoPosition(unsigned long position) override;

  virtual long getPosition() override;

  /**
   *
   * @return next
   */
  virtual bool hasNext() override;

  /**
   *
   * @return image
   */
  virtual Image next() override;

  /**
   *
   * @return size
   */
  virtual unsigned int size() override;

  virtual unsigned int getFPS() override;

  virtual std::string getPath() override;

  virtual bool equals(ImageSet *other) override;

 protected:
  void loadFolder();

  std::string path;

  long position = 0;
  std::vector<boost::filesystem::path> images;
  std::vector<boost::filesystem::path>::const_iterator imgIter;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace AnnotatorLib

/************************************************************
 End of ImageFolder class header
 ************************************************************/

#endif
