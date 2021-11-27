.DEFAULT_GOAL := compile

compile:
	g++ -o ./bin/main -I ./include ./src/*.cpp -w -lSDL2
run:
	./bin/main