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
ex13.o: ex13.c CSCIx229.h
fatal.o: fatal.c CSCIx229.h
loadtexbmp.o: loadtexbmp.c CSCIx229.h
print.o: print.c CSCIx229.h
project.o: project.c CSCIx229.h
errcheck.o: errcheck.c CSCIx229.h
object.o: object.c CSCIx229.h

sphere.o: sphere.c sphere.h CSCIx229.h
cube.o: cube.c cube.h CSCIx229.h
triangularPrism.o: triangularPrism.c triangularPrism.h CSCIx229.h
tear.o: tear.c tear.h CSCIx229.h
torus.o: torus.c torus.h CSCIx229.h
cylinder.o: cylinder.c cylinder.h CSCIx229.h
bicycle.o: bicycle.h bicycle.c cylinder.o torus.o
diamond.o: diamond.h diamond.c CSCIx229.h
tetrahedron.o: tetrahedron.h tetrahedron.c CSCIx229.h
cone.o: cone.h cone.c CSCIx229.h

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
	gcc -O3 -o $@ $^   $(LIBS)

#  Clean
clean:
	$(CLEAN)

# Clean and make
cleanmake: clean main

