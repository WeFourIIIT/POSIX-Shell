shell: main.o ujjwal.o priyank.o prashant.o rishabh.o
	g++ -w main.o ujjwal.o priyank.o prashant.o rishabh.o -o shell

main.o: main.cpp
	g++ -w -c main.cpp

ujjwal.o: ujjwal.cpp ujjwal.h
	g++ -w -c ujjwal.cpp

priyank.o: priyank.cpp priyank.h
	g++ -w -c priyank.cpp

prashant.o: prashant.cpp prashant.h
	g++ -w -c prashant.cpp

rishabh.o: rishabh.cpp rishabh.h
	g++ -w -c rishabh.cpp

clean:
	rm -rf *.o shell