# C++ SFML Game Template

## Linux SFML's dependencies

``` bash
sudo apt update
sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libfreetype-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev
```
---

## Configure and build
``` bash
cmake -S . -B build
cmake --build build --config Release
```
## Run

``` bash
./build/bin/Ougi
```

## Solution for safe directory error

``` bash
git config --global --add safe.directory /complete/path/to/Ougi/build/_deps/sfml-src
```
