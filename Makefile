shell: main.o ujjwal.o priyank.o prashant.o rishabh.o
	g++ main.o ujjwal.o priyank.o prashant.o rishabh.o -o shell

main.o: main.cpp
	g++ -c main.cpp

ujjwal.o: ujjwal.cpp ujjwal.h
	g++ -c ujjwal.cpp

priyank.o: priyank.cpp priyank.h
	g++ -c priyank.cpp

prashant.o: prashant.cpp prashant.h
	g++ -c prashant.cpp

rishabh.o: rishabh.cpp rishabh.h
	g++ -c rishabh.cpp

clean:
	rm -rf *.o shell