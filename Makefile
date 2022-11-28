shell: main.o ujjwal.o priyank.o prashant.o rishabh.o
	g++ -std=c++14 -w main.o ujjwal.o priyank.o prashant.o rishabh.o -o shell

main.o: main.cpp
	g++ -std=c++14 -w -c main.cpp

ujjwal.o: ujjwal.cpp ujjwal.h
	g++ -std=c++14 -w -c ujjwal.cpp

priyank.o: priyank.cpp priyank.h
	g++ -std=c++14 -w -c priyank.cpp

prashant.o: prashant.cpp prashant.h
	g++ -std=c++14 -w -c prashant.cpp

rishabh.o: rishabh.cpp rishabh.h
	g++ -std=c++14 -w -c rishabh.cpp

clean:
	rm -rf *.o shell