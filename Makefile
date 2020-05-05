Cxx	 := g++
CXXFLAGS := -g -O0

INCLUDE  := -I./include
TARGET   := ./kinako-chan
SRCDIR   := ./src
OBJDIR   := ./src/obj
SOURCES  := $(wildcard ./src/*.cpp)
OBJECTS  := $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))

$(TARGET): $(OBJECTS) $(LIBS)
	$(CXX) $(CXXFLAGS)-o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@[ -d $(OBJDIR) ]
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

install: $(OBJECTS) $(LIBS)
	$(CXX) -O2 -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJECTS) $(TARGET)

demo: kinako-chan
	./kinako-chan -s=1000 example.knk

test: kinako-chan
	./kinako-chan -s=50 example.knk

.PHONY: demo test clean install
