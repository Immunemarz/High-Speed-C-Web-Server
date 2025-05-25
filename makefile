CC = g++
CPPFLAGS = -g -I.
LDFLAGS = -Wl,--no-as-needed
all: server RegularExpression
server: server.o serializer.o books.h
serializer.o: serializer.cpp serializer.h
RegularExpression: RegularExpression.o
RegularExpression.o: RegularExpression.cpp

clean:
	rm server
	rm *.o