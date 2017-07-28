swig -c++ -tcl wormSegmenter.i
g++ -fPIC -c wormSegmenter_wrap.cxx
g++ -fPIC -c wormSegmenter.cpp
g++ -shared wormSegmenter_wrap.o wormSegmenter.o -o wormsegmenter.so `pkg-config --cflags --libs opencv`
tclsh make-package.tcl > pkgIndex.tcl


