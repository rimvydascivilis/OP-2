CXX := g++
CXXFLAGS := -std=c++2a
RELEASE_FLAGS = -O3

SRCDIR = src
TESTDIR = test
BUILDDIR = build

EXEC = $(BUILDDIR)/program
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
TESTS = $(wildcard $(TESTDIR)/*.cpp)
TESTSOURCES = $(filter-out $(SRCDIR)/main%, $(wildcard $(SRCDIR)/*))
INCLUDES = -Iinclude
INCLUDESTEST = -lgtest -lpthread

.PHONY: all release clean run test

all: $(EXEC)

ifeq ($(wildcard $(BUILDDIR)),)
$(shell mkdir -p $(BUILDDIR))
endif

test: $(TESTS) $(TESTSOURCES)
	$(CXX) -o $(BUILDDIR)/test $(TESTS) $(TESTSOURCES) $(INCLUDESTEST) $(INCLUDES)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

run: $(EXEC)
	./$(EXEC)

release: CXXFLAGS += $(RELEASE_FLAGS)
release: all

clean:
	rm -rf $(BUILDDIR)