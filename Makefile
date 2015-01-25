all: sigslot_test
.PHONY: clean

widget.o: widget.h

sigslot_test: main.o widget.o
	$(CXX) $(LFLAGS) -o $@ $^

clean:
	rm -f *.o
	rm -f sigslot_test
