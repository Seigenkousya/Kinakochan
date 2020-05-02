Cxx:=g++
CPPFLAGS:=-g -O0

Kinakochan: Kinakochan.cpp
	$(Cxx) $(CPPFLAGS) Kinakochan.cpp -o Kinakochan

install:
	$(Cxx) -O2  Kinakochan.cpp -o Kinakochan

clean:
	rm -f *.o Kinakochan

test: Kinakochan
	./Kinakochan example.bf

.PHONY: test clean install
