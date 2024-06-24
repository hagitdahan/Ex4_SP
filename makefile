CXX = clang++
CXXFLAGS = -std=c++2a -Wall -g
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
#VALGRIND_FLAGS=--leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --error-exitcode=99
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SRCS = Demo.cpp 
HDRS = tree.hpp node.hpp Complex.hpp
OBJS = $(SRCS:.cpp=.o) 

TESTSOURCES = TestCounter.cpp Test.cpp
TESTOBJS = $(TESTSOURCES:.cpp=.o)

TARGET = tree
TESTTARGET = test

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(SFMLFLAGS) 

$(TESTTARGET): $(TESTOBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TESTTARGET) $(TESTOBJS) $(filter-out Demo.o, $(OBJS))

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind_test: $(TESTTARGET) 
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./$(TESTTARGET) 2>&1 | { egrep "lost| at " || true; }
	
valgrind_tree: $(TARGET) 
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./$(TARGET) 

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET) $(TESTOBJS) $(TESTTARGET)

$(OBJS): $(HDRS)
