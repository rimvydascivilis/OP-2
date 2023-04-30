CXX := g++
CXXFLAGS := -std=c++2a
RELEASE_FLAGS = -O3

SRCDIR = src
BUILDDIR = build

EXEC = $(BUILDDIR)/program
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
INCLUDES = -Iinclude

.PHONY: all release clean run

all: $(EXEC)

ifeq ($(wildcard $(BUILDDIR)),)
$(shell mkdir -p $(BUILDDIR))
endif

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

run: $(EXEC)
	./$(EXEC)

release: CXXFLAGS += $(RELEASE_FLAGS)
release: all

clean:
	rm -f $(BUILDDIR)/*.o $(EXEC)
	rmdir $(BUILDDIR)