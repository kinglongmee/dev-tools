#!/bin/bash

# copy from https://gist.github.com/bopjiang/11146574
# generate cscope index files in current directory
# the generated cscope index files also include go standard packages

if [ "$GOROOT" = "" ] ; then
echo "GOROOT is not set"
GOROOT=`go env |grep "GOROOT" |cut -d "=" -f2`
GOROOT=${GOROOT#\"}
GOROOT=${GOROOT%\"}
fi
echo $GOROOT

go_pkg_src=$GOROOT/pkg

find $go_pkg_src -name "*.go" -print > cscope.files
find . -name "*.go" -print >> cscope.files

if cscope -b -k; then
        echo "Done"
else
        echo "Failed"
        exit 1
fi
