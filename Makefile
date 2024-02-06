all: client server

poker.so: src/poker/*.cpp
	@g++ -fPIC -shared src/poker/*.cpp -o poker.o -Wall -g
	

client: poker.so src/client/*.cpp
	@g++ poker.o src/client/*.cpp -o client -Wall -g


server: poker.so src/server/*.cpp
	@g++ poker.o src/server/*.cpp -o server -Wall -g


clean:




# bin/card.o: src/poker/Card.cpp src/poker/Card.hpp
# 	@g++ -c src/poker/Card.cpp -Wall -o bin/card.o

# bin/Deck.o: src/Card.cpp src/Card.hpp
# 	@g++ -c src/Card.cpp -Wall -o bin/card.o
