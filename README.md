# Annotator Library

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
