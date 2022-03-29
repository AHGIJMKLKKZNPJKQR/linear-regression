CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3

SRCDIR = src
OBJDIR = obj

objects := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

all: main

main: $(objects)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(objects): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -r $(OBJDIR)/*
	rm main