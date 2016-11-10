all: securesystem

securesystem: Subject.o Object.o SecureSystem.o ReferenceMonitor.o
	g++ -o securesystem Subject.o Object.o SecureSystem.o ReferenceMonitor.o
		
Subject.o: Subject.cpp
	g++ -c -std=c++0x -Wall -c -o Subject.o Subject.cpp

Object.o: Object.cpp
	g++ -c -std=c++0x -Wall  -c -o Object.o Object.cpp

ReferenceMonitor.o: ReferenceMonitor.cpp
	g++ -c -std=c++0x -Wall  -c -o ReferenceMonitor.o ReferenceMonitor.cpp

SecureSystem.o: SecureSystem.cpp
	g++ -c -std=c++0x -Wall  -c -o SecureSystem.o SecureSystem.cpp

clean:
		rm -rf *.o hash