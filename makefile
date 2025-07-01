# Example 12
EXE=pr
vpath %.c car
vpath %.h car

# Main target
all: $(EXE)

#  Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32 -lm
CLEAN=rm -f *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall -Icar
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Dependencies
car.o: car.c CSCI5229.h objects.h car/CarParts.h car/Monocoque.c car/Utils.h car/Wing.c car/Halo.c
Utils.o: car/Utils.c CSCI5229.h
Wing.o: car/Wing.c car/Utils.h CSCI5229.h car/CarParts.h
Monocoque.o: car/Monocoque.c car/Utils.h CSCI5229.h car/CarParts.h
Halo.o: car/Halo.c car/Utils.h CSCI5229.h car/CarParts.h

pr.o: pr.c CSCI5229.h objects.h car/CarParts.h
objects.o: objects.c CSCI5229.h objects.h

print.o: print.c CSCI5229.h
errcheck.o: errcheck.c CSCI5229.h
loadtexbmp.o: loadtexbmp.c CSCI5229.h
fatal.o: fatal.c CSCI5229.h

# Create archive
CSCI5229.a:print.o loadtexbmp.o errcheck.o fatal.o Utils.o Wing.o Monocoque.o Halo.o
	ar -rcs $@ $^

# Compile rules
.c.o:
	gcc -c $(CFLG)  $<
.cpp.o:
	g++ -c $(CFLG)  $<

#  Link
pr:pr.o  objects.o car.o CSCI5229.a
	gcc $(CFLG) -o $@ $^  $(LIBS)

#  Clean
clean:
	$(CLEAN)
