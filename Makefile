Cxx:=g++
CPPFLAGS:=-g -O0

kinako-chan: kinako-chan.cpp
	$(Cxx) $(CPPFLAGS) kinako-chan.cpp -o kinako-chan

install:
	$(Cxx) -O2  kinako-chan.cpp -o kinako-chan

clean:
	rm -f *.o kinako-chan

demo: kinako-chan
	./kinako-chan example.bf

test: kinako-chan
	./kinako-chan -h

.PHONY: demo test clean install
