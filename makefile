Game : basicSetup.cpp loadShaders.cpp drawObjects.cpp reshapeWindow.cpp camera.cpp game.cpp glad.c tiles.cpp headers.cpp
	g++ -o main basicSetup.cpp loadShaders.cpp drawObjects.cpp reshapeWindow.cpp camera.cpp	game.cpp glad.c tiles.cpp headers.cpp -std=c++11 -lGL -lglfw -ldl -lmpg123 -lao 
