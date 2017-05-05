CXX=clang++
LDFLAGS=-g
CXXFLAGS=-g -c -std=c++11
OBJS=main.o graph.o
RM=rm -f
TARGET=project

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(TARGET)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

graph.o: graph.cpp
	$(CXX) $(CXXFLAGS) graph.cpp

clean:
	$(RM) $(OBJS)
