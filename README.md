# Annotator Library [ ![Build Status] [travis-image] ] [travis] [ ![Documentation] [codedocs-image] ] [codedocs] [ ![Gitter] [gitter-image] ] [gitter]


[travis-image]: https://travis-ci.org/lasmue/annotatorlib.png?branch=master
[travis]: http://travis-ci.org/lasmue/annotatorlib

[codedocs-image]: https://codedocs.xyz/lasmue/annotatorlib.svg
[codedocs]: https://codedocs.xyz/lasmue/annotatorlib/

[gitter-image]: https://badges.gitter.im/Join%20Chat.svg
[gitter]: https://gitter.im/lasmue/annotatorlib

### Quick start

First install CMake, Qt5 and a c++11 compiler (gcc 5).

```
sudo apt-get install libboost-system-dev libboost-filesystem-dev
sudo apt-get install qtbase5-dev
```

Then build.

```sh
git clone https://github.com/lasmue/annotatorlib
git submodule update --init --recursive
cd annotatorlib
mkdir build
cd build
cmake ..
make
```
