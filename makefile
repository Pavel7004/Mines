# фаил для сборки проекта посредством компилятора gcc и улититы GNU Make

# все файлы объектного кода проекта
objects = main.o field.o convert.o

# задача сборки проекта
install: $(objects)
	g++ -o minesGame $(objects)
	rm $(objects)

# фаил объектного кода main.cpp
main.o: main.cpp
	g++ -o main.o -c main.cpp

# фаил объектного кода field.cpp
field.o: field.h field.cpp
	g++ -o field.o -c field.cpp

# фаил объектного кода convert.cpp
convert.o: convert.h convert.cpp
	g++ -o convert.o -c convert.cpp
