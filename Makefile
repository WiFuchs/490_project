#CXX=clang++
CXX=g++

CXXFLAGS= -O3 -std=c++17

BINARIES=dataProj testStates

all: ${BINARIES}

tests: ${BINARIES}
	./testStates

dataProj: dataAQ.o demogState.o demogData.o parse.o main.o Ethnicity.o psData.o psCombo.o  DataDraw.o
	${CXX} $^ -o $@

testStates: testStates.o dataAQ.o demogState.o demogData.o parse.o tddFuncs.o Ethnicity.o psData.o psCombo.o  DataDraw.o

	${CXX} $^ -o $@

clean:
	/bin/rm -f ${BINARIES} *.o
