# Makefile - R Arce
all: client

client: client.o ParsedFile.o Engine.o
	c++ client.o ParsedFile.o Engine.o -o client

client.o: client.cpp ParsedFile.h Engine.h
	c++ -c client.cpp

ParsedFile.o: ParsedFile.cpp ParsedFile.h 
	c++ -c ParsedFile.cpp

Engine.o: Engine.cpp Engine.h
	c++ -c Engine.cpp

clean: 
	rm -rf *.o

pack:
	tar cvzf engine.tgz client.cpp ParsedFile.h ParsedFile.cpp Makefile
