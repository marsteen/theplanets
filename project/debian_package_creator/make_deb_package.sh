#!/bin/sh
DIRDEB=theplanets_2_0
#
mkdir -p ./$DIRDEB/usr/local/bin
cp ../build/bin/Linux/theplanets ./$DIRDEB/opt/theplanets
dpkg-deb --build $DIRDEB
