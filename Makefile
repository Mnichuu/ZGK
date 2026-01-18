# Makefile
CXX := g++
SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)
TARGET := projekt3D

PKG_CFLAGS := $(shell pkg-config --cflags openscenegraph 2>/dev/null)
PKG_LIBS := $(shell pkg-config --libs openscenegraph 2>/dev/null)

CXXFLAGS := -std=c++14 -O2 -Wall $(PKG_CFLAGS)
LDFLAGS := $(PKG_LIBS)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)
