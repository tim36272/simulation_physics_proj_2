NC=-I/usr/local/include
LIB=-L/usr/local/lib -L/usr/X11R6/lib
LIBS=-lGL -lGLU -lglut

	
proj2: main.o simSession.o camera.o quaternion.o rigid_body.o
	g++ $(LIB) $(INC) -o proj2 main.o simSession.o rigid_body.o camera.o quaternion.o $(LIBS) -g -Wall
	
main.o: main.cpp ../simulation/simSession.h ../simulation/geometry.h ../utilities/visualization/camera.h
	g++ -c main.cpp -g -Wall
	
simSession.o: ../simulation/simSession.cpp ../simulation/simSession.h camera.o
	g++ -c "../simulation/simSession.cpp" -g -Wall

camera.o: ../utilities/visualization/camera.cpp ../utilities/visualization/camera.h
	g++ -c "../utilities/visualization/camera.cpp" -g -Wall

quaternion.o: ../utilities/math/quaternion.cpp ../utilities/math/quaternion.h
	g++ -c "../utilities/math/quaternion.cpp" -g -Wall

rigid_body.o: ../simulation/rigid_body.cpp ../simulation/rigid_body.h
	g++ -c "../simulation/rigid_body.cpp" -g -Wall

#vec.o: ../utilities/math/vec.hpp
#	g++ -c "../utilities/math/vec.hpp" -o vec.o -g -Wall

clean:
	rm *.o
