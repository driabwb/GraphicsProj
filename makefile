# Example 13
EXE=main

# Main target
all: $(EXE)

#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall
LIBS=-lglut32cu -lglu32 -lopengl32
CLEAN=del *.exe *.o *.a *~
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall -g
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a *~ *.gch
endif

# Dependencies
fatal.o: fatal.c CSCIx229.h
loadtexbmp.o: loadtexbmp.c CSCIx229.h
print.o: print.c CSCIx229.h
project.o: project.c CSCIx229.h
errcheck.o: errcheck.c CSCIx229.h
object.o: object.c CSCIx229.h

sphere.o: sphere.cpp sphere.h CSCIx229.h
cube.o: cube.cpp cube.h CSCIx229.h
triangularPrism.o: triangularPrism.cpp triangularPrism.h CSCIx229.h
tear.o: tear.cpp tear.h CSCIx229.h
torus.o: torus.cpp torus.h CSCIx229.h
cylinder.o: cylinder.cpp cylinder.h CSCIx229.h
bicycle.o: bicycle.h bicycle.cpp cylinder.o torus.o
diamond.o: diamond.h diamond.cpp CSCIx229.h
tetrahedron.o: tetrahedron.h tetrahedron.cpp CSCIx229.h
cone.o: cone.h cone.cpp CSCIx229.h

world.o: world.c world.h CSCIx229.h cube.o sphere.o triangularPrism.o tear.o torus.o cylinder.o bicycle.o diamond.o tetrahedron.o \
	cone.o

#  Create archive
CSCIx229.a:fatal.o loadtexbmp.o print.o project.o errcheck.o object.o
	ar -rcs $@ $^

objects.a:cube.o sphere.o triangularPrism.o tear.o torus.o cylinder.o bicycle.o diamond.o tetrahedron.o \
	cone.o world.o
	ar -rcs $@ $^

# Compile rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

#  Link
main:main.o CSCIx229.a objects.a
	g++ -O3 -o $@ $^   $(LIBS)

#  Clean
clean:
	$(CLEAN)

# Clean and make
cleanmake: clean main

