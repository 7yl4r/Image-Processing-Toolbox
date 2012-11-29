# source files.
SRC =  image/image.cpp utility/utility.cpp roi/roi.cpp add/add.cpp threshold/threshold.cpp scale/scale.cpp smooth/smooth.cpp equalize/equalize.cpp colorSpace/colorSpace.cpp edgeDetect/edgeDetect.cpp circleDetect/circleDetect.cpp fourier/fourier.cpp 

OBJ = $(SRC:.cpp=.o)

OUT = ../lib/libiptools.a

# include directories
INCLUDES = -I. -I/usr/local/include -Iimage/ -Iutility/ -I/usr/include/c++/4.2.1 /usr/local/lib/libfftw3.a

# linked libraries (uncertain if this is right) (It doesn't seem to do anything...)
LIBS = -lrfftw -lfftw -lm

# C++ compiler flags (-g -O2 -Wall)
CCFLAGS = -g

# compiler
CCC = g++

# compile flags
LDFLAGS = -g 

.SUFFIXES: .cpp

.cpp.o:
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@ $(LIBS)

$(OUT): $(OBJ)
	ar rcs $(OUT) $(OBJ)

clean:
	rm -f $(OBJ) $(OUT) Makefile.bak# DO NOT DELETE
