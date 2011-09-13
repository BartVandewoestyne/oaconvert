CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=airspace.cpp restricted.cpp latlon.cpp latitude.cpp longitude.cpp coordinate.cpp \
        point.cpp header.cpp stringutils.cpp parser.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=oa2pm

all: liboa2pm.a $(EXECUTABLE)

liboa2pm.a: $(OBJECTS)
	rm -f $@
	ar cq $@ $(OBJECTS)

$(EXECUTABLE): oa2pm.o liboa2pm.a
	$(CC) $^ -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o

realclean: clean
	rm -f $(EXECUTABLE) liboa2pm.a *.mp
