main:
	g++ main.cpp chessboard.cpp chesspiece.cpp -o chess -lSDL2 -lSDL2_image -lSDL2_ttf

run:
	g++ main.cpp chessboard.cpp chesspiece.cpp -o chess -lSDL2 -lSDL2_image -lSDL2_ttf
	./chess

clean:
	rm -f *.o chess