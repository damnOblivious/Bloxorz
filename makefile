Game : basicSetup.cpp loadShaders.cpp drawObjects.cpp reshapeWindow.cpp camera.cpp game.cpp glad.c 3DObject.cpp tiles.cpp brick1.cpp brick2.cpp switchbrick.cpp goaltile.cpp fragile.cpp grid.cpp blocks.cpp headers.cpp Text.cpp
	g++ -o main basicSetup.cpp loadShaders.cpp drawObjects.cpp reshapeWindow.cpp camera.cpp	game.cpp glad.c 3DObject.cpp tiles.cpp brick1.cpp brick2.cpp switchbrick.cpp goaltile.cpp fragile.cpp grid.cpp blocks.cpp headers.cpp Text.cpp -I./include/ -L./lib/ -std=c++11 -lSOIL -lGL -lglfw -ldl -lmpg123 -lassimp -lao
