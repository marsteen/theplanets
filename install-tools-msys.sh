#!/bin/sh
pacman -S g++ make
pacman -S mingw-w64-x86_64-cmake
echo 'PATH="${PATH}:/mingw64/bin"' >> ~/.bash_profile
alias cmake='cmake -G "Unix Makefiles"'