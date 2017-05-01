CXX=clang++
LDFLAGS=-g
CXXFLAGS=-g -c -Wc++11-extensions
OBJS=main.o
RM=rm -f
TARGET=project

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(TARGET)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

clean:
	$(RM) $(OBJS)
