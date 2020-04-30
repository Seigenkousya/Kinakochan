Cxx:=g++
CPPFLAGS:=-g -O0

Brainwash: Brainwash.cpp
	$(Cxx) $(CPPFLAGS) Brainwash.cpp -o Brainwash

clean:
	rm -f *.o Brainwash

test: Brainwash
	./Brainwash example.bf

.PHONY: test clean
