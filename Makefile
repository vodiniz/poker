all: client server

poker.so: src/poker/*.cpp
	@g++ -fPIC -shared src/poker/*.cpp -o poker.so -Wall
	

client: poker.so src/client/*.cpp
	@g++ poker.so src/client/*.cpp -o client -Wall


server: poker.so src/server/*.cpp
	@g++ poker.so src/server/*.cpp -o server -Wall



# src.so:
# 	@g++ -fPIC -shared -o src.so ../src/*.cpp -Wall -g


# funcional_tests: src.so derived_flows.o
# 	@g++ ../test/funcional/*.cpp src.so derived_flows.o -o funcional_tests -Wall


# unit_tests: src.so derived_flows.o
# 	@g++ ../test/unit/*.cpp src.so derived_flows.o -o unit_tests -Wall