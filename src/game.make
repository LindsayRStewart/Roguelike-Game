# game.make

all: DungeonCrawlGame clean

DungeonCrawlGame: gameEngine.o layer.o armor.o character.o item.o monster.o player.o base_room.o hall.o rec_room.o tree.o weapon.o healthPotion.o
	g++ gameEngine.o layer.o armor.o character.o item.o monster.o player.o base_room.o hall.o rec_room.o tree.o weapon.o healthPotion.o -lncurses -o DungeonCrawlGame
	
gameEngine.o: gameEngine.cpp player.h layer.h
	g++ -c gameEngine.cpp

layer.o: layer.cpp layer.h rec_room.h base_room.h tree.h player.h monster.h healthPotion.h
	g++ -c layer.cpp

armor.o: armor.cpp armor.h
	g++ -c armor.cpp

character.o: character.cpp character.h
	g++ -c character.cpp

item.o: item.cpp item.h
	g++ -c item.cpp

monster.o: monster.cpp monster.h
	g++ -c monster.cpp

player.o: player.cpp player.h
	g++ -c player.cpp

base_room.o: base_room.cpp base_room.h layer.h
	g++ -c base_room.cpp

rec_room.o: rec_room.cpp rec_room.h layer.h
	g++ -c rec_room.cpp
	
hall.o: hall.cpp hall.h layer.h
	g++ -c hall.cpp 

tree.o: tree.cpp tree.h
	g++ -c tree.cpp

weapon.o: weapon.cpp weapon.h
	g++ -c weapon.cpp
	
healthPotion.o: healthPotion.cpp healthPotion.h
	g++ -c healthPotion.cpp
	
clean:
	rm -rf *.o *.h~ *.cpp~ *.make~
