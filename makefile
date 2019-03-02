CPPFLAGS += -std=c++14 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include
# what dos this do ^^





all : bin/c_compiler

# Bison
src/simpleparser.tab.cpp src/simpleparser.tab.hpp: src/simpleparser.y
	bison -v -d src/simpleparser.y -o src/simpleparser.tab.cpp

# Flex
src/simplelexer.yy.cpp: src/simplelexer.flex src/simpleparser.tab.hpp
	flex -o src/simplelexer.yy.cpp src/simplelexer.flex


bin/c_compiler: src/simplelexer.yy.cpp src/simpleparser.tab.cpp src/simpleparser.tab.hpp

		mkdir -p bin
		g++ $(CPPFLAGS) src/ast/compile.cpp src/ast/translate.cpp -o bin/c_compiler $^



clean:

	rm src/*.tab.cpp
	rm src/*.yy.cpp
	rm src/*.tab.hpp
	rm src/*.output
	rm bin/*
	rm test_deliverable/results/*
	rm c_translator_tests/results/*
