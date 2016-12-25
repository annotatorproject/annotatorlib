// Copyright 2016 Annotator Team

#define Annotator_AnnotatorLib_ImageFTP_BODY

/************************************************************
 ImageFTP class body
 ************************************************************/

// include associated header file
#include <opencv2/opencv.hpp>
#include <set>
#include <stdexcept>
#include <boost/algorithm/string.hpp>

#include <Poco/Net/FTPClientSession.h>
#include <Poco/StreamCopier.h>
#include <Poco/URI.h>

#include "AnnotatorLib/ImageFTP.h"

// Derived includes directives

namespace AnnotatorLib {

const std::set<std::string> imagetypes = {(".bmp"), (".pbm"),  (".pgm"),
                                          (".ppm"), (".jpg"),  (".jpeg"),
                                          (".png"), (".tiff"), (".tif")};

ImageFTP::ImageFTP(std::string path) {
  this->path = path;
  loadFolder();
}

ImageSetType ImageFTP::getType() { return ImageSetType::IMAGEFTP; }

Image ImageFTP::getImage(unsigned long position) {
  Image img = downloadImage((images.begin() + position)->string());
  return img;
}

bool ImageFTP::gotoPosition(unsigned long position) {
  if (images.size() < position)
    return false;
  this->position = position;
  imgIter = images.begin() + position;
  return true;
}

long ImageFTP::getPosition() { return position; }

bool ImageFTP::hasNext() { return imgIter != images.end(); }

Image ImageFTP::next() {
  Image img = downloadImage(imgIter->string());
  imgIter++;
  position++;
  return img;
}

unsigned int ImageFTP::size() { return images.size(); }

unsigned int ImageFTP::getFPS() { return 24; }

std::string ImageFTP::getPath() { return path; }

bool ImageFTP::equals(ImageSet *other) {
  if (this == other)
    return true;
  if (other->getType() != ImageSetType::IMAGEFTP)
    return false;
  if (this->getPath() != other->getPath())
    return false;
  return true;
}

struct sort_functor {
  bool operator()(const std::string &a, const std::string &b) { return a < b; }
};

void ImageFTP::loadFolder() {

  Poco::URI uri(path);
  std::vector<std::string> userinfo;
  boost::split(userinfo, uri.getUserInfo(), boost::is_any_of(":"));

  Poco::Net::FTPClientSession session(uri.getHost(), 21, userinfo[0], userinfo[1]);
  session.setWorkingDirectory(uri.getPath());
  std::istream& istr = session.beginList();
  std::ostringstream dataStr;
  Poco::StreamCopier::copyStream(istr, dataStr);
  session.endList();
  std::string s(dataStr.str());
  session.close();

  std::vector<std::string> files;
  boost::split(files, s, boost::is_any_of("\r\n"));

  // only use image files
  for(auto const& file: files) {
      std::string extension = boost::filesystem::extension(file);
      if(imagetypes.find(extension) != imagetypes.end())
          images.push_back(file);
  }
  std::sort(images.begin(), images.end());
  imgIter = images.begin();

}

Image ImageFTP::downloadImage(std::string file)
{
    cv::Mat mat;
    try{
    Poco::URI uri(path);
    std::vector<std::string> userinfo;
    boost::split(userinfo, uri.getUserInfo(), boost::is_any_of(":"));

    Poco::Net::FTPClientSession session(uri.getHost(), 21, userinfo[0], userinfo[1]);
    session.setWorkingDirectory(uri.getPath());
    std::istream& istr = session.beginDownload(file);
    std::ostringstream dataStr;
    Poco::StreamCopier::copyStream(istr, dataStr);
    session.endDownload();
    std::string s(dataStr.str());
    session.close();

    // source: https://gist.github.com/Benjit87/4188323
    std::vector<char> data = std::vector<char>( s.begin(), s.end() );
    cv::Mat data_mat = cv::Mat(data);
    mat = cv::imdecode(data_mat, 1);
    }catch(...){

    }

    return mat;

}

// static attributes (if any)

} // of namespace AnnotatorLib

/************************************************************
 End of ImageFTP class body
 ************************************************************/
