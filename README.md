# Annotator Library

Library for labeling and annotating images.

=================

[![Stories in Ready][waffle-image]][waffle]
[![Build Status][travis-image]][travis]
[![Build Status Windows][appveyor-image]][appveyor]
[![Coverage_Status][coveralls-image]][coveralls]
[![Coverage Status Codecov][codecov-image]][codecov]
[![Coverity Scan Build Status][coverity-image]][coverity]
[![Documentation][codedocs-image]][codedocs]
[![Gitter][gitter-image]][gitter]

[travis-image]: https://travis-ci.org/annotatorproject/annotatorlib.png?branch=master
[travis]: http://travis-ci.org/annotatorproject/annotatorlib

[appveyor-image]: https://img.shields.io/appveyor/ci/chriamue/annotatorlib.svg
[appveyor]: https://ci.appveyor.com/project/chriamue/annotatorlib

[coveralls-image]: https://img.shields.io/coveralls/annotatorproject/annotatorlib.svg?label=Coverage
[coveralls]: https://coveralls.io/github/annotatorproject/annotatorlib

[codecov-image]: https://img.shields.io/codecov/c/github/annotatorproject/annotatorlib.svg
[codecov]: https://codecov.io/gh/annotatorproject/annotatorlib

[codedocs-image]: https://codedocs.xyz/annotatorproject/annotatorlib.svg
[codedocs]: https://codedocs.xyz/annotatorproject/annotatorlib/

[coverity-image]: https://img.shields.io/coverity/scan/12802.svg
[coverity]: https://scan.coverity.com/projects/annotatorproject-annotatorlib

[gitter-image]: https://badges.gitter.im/Join%20Chat.svg
[gitter]: https://gitter.im/annotatorproject/annotatorlib

[waffle-image]: https://badge.waffle.io/annotatorproject/annotatorlib.svg?label=ready&title=Ready
[waffle]: http://waffle.io/annotatorproject/annotatorlib

## Quick start

First install CMake, Qt5 and a c++11 compiler (gcc 5).

```bash
sudo apt-get install libboost-system-dev libboost-filesystem-dev libpoco-dev libmysqlclient-dev libmongo-client-dev
```

Build LibPoco

```bash
git clone https://github.com/pocoproject/poco.git
cd poco
sed -i 's#mysqlclient_r#mysqlclient mysqlclient_r#g' cmake/FindMySQL.cmake
cd build
cmake ..
make -j2
```

Then build.

```bash
git clone https://github.com/annotatorproject/annotatorlib
git submodule update --init --recursive
cd annotatorlib
mkdir build
cd build
cmake -DPoco_DIR= ../../poco/build/Poco ..
make
```

Add PascalVoc storage support.

```bash
cd annotatorlib/source/storages
git clone https://github.com/annotatorproject/annotatorstorage_pascalvocxml
cd ../../build
cmake ..
make
```

## Conan Build on Windows

First install Visual Studio, CMake, Git and Conan.

Open Git Bash:

```bash
git clone https://github.com/annotatorproject/annotatorlib
git submodule update --init --recursive
cd annotatorlib
mkdir build
cd build
cmake .. -G "Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Release -DOPTION_CONAN_PACKAGES=1
cmake --build . --config Release
```

## Build coverage

```bash
git clone https://github.com/annotatorproject/annotatorlib
git submodule update --init --recursive
cd annotatorlib
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Coverage ..
make annotatorlib_coverage
```
