all: client server

poker.so: src/poker/*.cpp
	@g++ -fPIC -shared src/poker/*.cpp -o poker.o -Wall
	

client: poker.so src/client/*.cpp
	@g++ poker.o src/client/*.cpp -o client -Wall


server: poker.so src/server/*.cpp
	@g++ poker.o src/server/*.cpp -o server -Wall



clean:




# bin/card.o: src/poker/Card.cpp src/poker/Card.hpp
# 	@g++ -c src/poker/Card.cpp -Wall -o bin/card.o

# bin/Deck.o: src/Card.cpp src/Card.hpp
# 	@g++ -c src/Card.cpp -Wall -o bin/card.o

# src.so:
# 	@g++ -fPIC -shared -o src.so ../src/*.cpp -Wall -g


# funcional_tests: src.so derived_flows.o
# 	@g++ ../test/funcional/*.cpp src.so derived_flows.o -o funcional_tests -Wall


# unit_tests: src.so derived_flows.o
# 	@g++ ../test/unit/*.cpp src.so derived_flows.o -o unit_tests -Wall