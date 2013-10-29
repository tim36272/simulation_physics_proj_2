vmath: vmathMain.o vmath.o
	g++ -o vmath vmathMain.o vmath.o -g -Wall
	
vmathMain.o: vmathMain.cpp vmath.h
	g++ -c vmathMain.cpp -g -Wall

vmath.o: vmath.cpp vmath.h
	g++ -c vmath.cpp -g -Wall
	
clean:
	rm *.o
