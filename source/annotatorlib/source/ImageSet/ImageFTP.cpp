// Copyright 2016 Annotator Team

#define Annotator_AnnotatorLib_ImageFTP_BODY

/************************************************************
 ImageFTP class body
 ************************************************************/

// include associated header file
#include <boost/algorithm/string.hpp>
#include <memory>
#include <opencv2/opencv.hpp>
#include <set>
#include <stdexcept>

#include <Poco/StreamCopier.h>
#include <Poco/URI.h>

#include "AnnotatorLib/ImageSet/ImageFTP.h"

// Derived includes directives

namespace AnnotatorLib {

const std::set<std::string> imagetypes = {(".bmp"), (".pbm"),  (".pgm"),
                                          (".ppm"), (".jpg"),  (".jpeg"),
                                          (".png"), (".tiff"), (".tif")};

ImageFTP::ImageFTP(std::string path) {
  this->path = path;
  loadFolder();
}

ImageFTP::~ImageFTP() {
  if (ftpSession && ftpSession->isOpen()) ftpSession->close();
}

ImageSetType ImageFTP::getType() { return ImageSetType::IMAGEFTP; }

Image ImageFTP::getImage(unsigned long position) {
  Image img = downloadImage((images.begin() + position)->string());
  return img;
}

std::string ImageFTP::getImagePath(unsigned long position) {
  return (images.begin() + position)->string();
}

bool ImageFTP::gotoPosition(unsigned long position) {
  if (images.size() < position) return false;
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

bool ImageFTP::equals(ImageSet* other) {
  if (this == other) return true;
  if (other->getType() != ImageSetType::IMAGEFTP) return false;
  if (this->getPath() != other->getPath()) return false;
  return true;
}

struct sort_functor {
  bool operator()(const std::string& a, const std::string& b) { return a < b; }
};

void ImageFTP::loadFolder() {
  Poco::URI uri(path);
  std::vector<std::string> userinfo;
  boost::split(userinfo, uri.getUserInfo(), boost::is_any_of(":"));

  host = uri.getHost();
  username = userinfo[0];
  if (userinfo.size() > 1) password = userinfo[1];
  workingDir = uri.getPath();

  ftpSession = std::make_shared<Poco::Net::FTPClientSession>();
  ftpSession->open(host, port, username, password);
  ftpSession->setWorkingDirectory(workingDir);
  std::istream& istr = ftpSession->beginList();
  std::ostringstream dataStr;
  Poco::StreamCopier::copyStream(istr, dataStr);
  ftpSession->endList();
  std::string s(dataStr.str());

  std::vector<std::string> files;
  boost::split(files, s, boost::is_any_of("\r\n"));

  // only use image files
  for (auto const& file : files) {
    std::string extension = boost::filesystem::extension(file);
    if (imagetypes.find(extension) != imagetypes.end()) images.push_back(file);
  }
  std::sort(images.begin(), images.end());
  imgIter = images.begin();
}

Image ImageFTP::downloadImage(std::string file) {
  cv::Mat mat;
  try {
    if (!ftpSession->isOpen()) {
      ftpSession->open(host, port, username, password);
      ftpSession->setWorkingDirectory(workingDir);
    }
    std::istream& istr = ftpSession->beginDownload(file);
    std::ostringstream dataStr;
    Poco::StreamCopier::copyStream(istr, dataStr);
    ftpSession->endDownload();
    std::string s(dataStr.str());

    // source: https://gist.github.com/Benjit87/4188323
    std::vector<char> data = std::vector<char>(s.begin(), s.end());
    cv::Mat data_mat = cv::Mat(data);
    mat = cv::imdecode(data_mat, 1);
  } catch (...) {
  }

  return mat;
}

// static attributes (if any)

}  // of namespace AnnotatorLib

/************************************************************
 End of ImageFTP class body
 ************************************************************/
