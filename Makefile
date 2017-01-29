CXX=g++
CXXFLAGS=-c -O2 -march=native -pipe -MMD -MP
LDFLAGS=

BUILD_DIR=bin
TARGET=${BUILD_DIR}/huff

SRC_FILES=$(wildcard *.cpp) $(wildcard **/*.cpp)
O_FILES=${SRC_FILES:%.cpp=${BUILD_DIR}/%.cpp.o}
D_FILES=${O_FILES:%.o=%.d}

all: ${TARGET}

clean:
	rm -rf ${BUILD_DIR}

${TARGET}: ${O_FILES}
	${CXX} ${LDFLAGS} $^ -o $@

${BUILD_DIR}/%.cpp.o: %.cpp # | $(@D)
	@mkdir -p $(@D)
	${CXX} ${CXXFLAGS} $< -o $@

-include ${D_FILES}

.PHONY: clean, all
