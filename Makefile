CXXC = /usr/bin/clang++
CXXFLAGS = -Wall -Werror

#Commands wont show in the console
.SILENT:

all: linker

wclean: linker
	echo "Cleaning up"
	rm -f linker *.o

linker: main.o matrix.o number.o
	echo "Linking"
	$(CXXC) $(CXXFLAGS) -o main main.o matrix.o number.o

main.o: src/main.cpp
	echo "Builing main.o"
	$(CXXC) $(CXXFLAGS) -c src/main.cpp
	
matrix.o: src/matrix.cpp
	echo "Builing matrix.o"
	$(CXXC) $(CXXFLAGS) -c src/matrix.cpp

number.o: src/number.cpp
	echo "Builing number.o"
	$(CXXC) $(CXXFLAGS) -c src/number.cpp

clean:
	echo "Cleaning up"
	rm -f linker *.o
	rm -f main