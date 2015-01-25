all: sigslot_test
.PHONY: clean

SRCS=main.cpp widget.cpp eventloop.cpp eventobject.cpp server.cpp simpleclient.cpp
OBJS=$(SRCS:%.cpp=%.o)

CXXFLAGS += -g

%.o : %.cpp
	$(COMPILE.cpp) -MD -o $@ $<
	@cp $*.d $*.P; \
			sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
			-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
			rm -f $*.d
-include $(SRCS:%.cpp=%.P)

sigslot_test: $(OBJS)
	$(CXX) $(LFLAGS) -o $@ -Wl,--start-group $^ -Wl,--end-group

clean:
	rm -f *.P
	rm -f *.P
	rm -f *.o
	rm -f sigslot_test
