.DEFAULT_GOAL := compile

compile:
	g++ -o ./bin/main -I ./include ./src/*.cpp -w -lSDL2 -lSDL2_image -lSDL2_ttf
run:
	./bin/main