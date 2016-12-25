// Copyright 2016 Annotator Team
#include <AnnotatorLib/ImageFTP.h>
#include <AnnotatorLib/Video.h>
#include <gmock/gmock.h>
#include <string>

#include <Poco/Net/NetException.h>

class imageftp_test : public testing::Test {
 public:
};

TEST_F(imageftp_test, listfiles) {
    try{
    AnnotatorLib::ImageFTP imageFtp("ftp://test:test@localhost/images/");
    std::cout << "images on ftp server: " << imageFtp.size() << std::endl;
    imageFtp.next();
    }catch(Poco::Net::FTPException &e)
    {
        std::cout << e.message() << std::endl;
    }

}
