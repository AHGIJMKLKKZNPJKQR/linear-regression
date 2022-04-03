CXX = g++
CXXFLAGS = -std=c++17	-Wall	-Wextra	-O3

SRCDIR = src
OBJDIR = obj

objects := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))
depends := $(objects:.o=.d)

all: main

main: $(objects)
	$(CXX) $(CXXFLAGS) -pthread -o $@ $^

-include $(depends)

$(objects): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp Makefile
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -r $(OBJDIR)/*
	rm main