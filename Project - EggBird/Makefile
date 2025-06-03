EGGBIRD.bin: Enemy.o main.o
	g++ Enemy.o main.o -o EGGBIRD.bin

Enemy.o: Enemy.hpp Enemy.cpp
	g++ -c Enemy.cpp

main.o: GameStart.hpp Enemy.hpp Get.hpp Point.hpp Title.hpp Clear.hpp main.cpp
	g++ -c main.cpp

clean: 
	rm -f EGGBIRD.bin *.o