Cxx	 := g++
CXXFLAGS := -g -O0

INCLUDE  := -I./include
TARGET   := ./kinako-chan
SRCDIR   := ./src
OBJDIR   := ./src/obj
SOURCES  := $(wildcard ./src/*.cpp)
OBJECTS  := $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@[ -d $(OBJDIR) ]
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

install: $(OBJECTS)
	$(CXX) -O2 -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJECTS) $(TARGET)

demo: kinako-chan
	./kinako-chan -s=100 example.knk

test: kinako-chan
	./kinako-chan -s=50 example.knk

test1: kinako-chan
	./kinako-chan -h

test2: kinako-chan
	./kinako-chan -n example.knk

test3: kinako-chan
	./kinako-chan -s=5 example.knk

.PHONY: demo test test1 test2 test3 clean install
