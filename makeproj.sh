mkdir $1

cp -r ../Stanford_CS106B_linux/* ./$1

echo "PROGRAM = $1
OBJECTS = $1.o

CPPOPTIONS = -IStanfordCPPLib -fvisibility-inlines-hidden
LDOPTIONS = -L.
LIB = -lStanfordCPPLib

all: \$(PROGRAM)

$1: \$(OBJECTS)
	g++ -o \$(PROGRAM) \$(LDOPTIONS) \$(OBJECTS) \$(LIB)

$1.o: $1.cpp Makefile libStanfordCPPLib.a
	g++ -c \$(CPPOPTIONS) $1.cpp

libStanfordCPPLib.a:
	@rm -f libStanfordCPPLib.a
	(cd StanfordCPPLib; make all)
	ln -s StanfordCPPLib/libStanfordCPPLib.a .


tidy:
	rm -f ,* .,* *~ core a.out *.err

clean scratch: tidy
	rm -f *.o *.a \$(PROGRAM)
" >> ./$1/Makefile

#/home/dato/assignments/ass1
#/home/dato/assignments/Stanford_CS106B_linux/StanfordCPPLib/libStanfordCPPLib.a

ln -s $(pwd)/$1/StanfordCPPLib/libStanfordCPPLib.a $(pwd)/$1/libStanfordCPPLib.a
