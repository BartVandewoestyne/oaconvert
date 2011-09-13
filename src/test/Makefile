CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES= HeaderTest.cpp ParserTest.cpp LatLonTest.cpp MainTester.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=MainTester

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -lcppunit -loa2pm -L../ -o $@

.cpp.o:
	$(CC) $(CFLAGS) -I../ $< -o $@

clean:
	rm -f *.o

realclean: clean
	rm -f $(EXECUTABLE) *.mp
