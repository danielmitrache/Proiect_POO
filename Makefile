all: compile link

compile:
	g++ -c src/Game.cpp -I"C:/SFML/SFML-3.0.0/include" -DSFML_STATIC
	g++ -c src/main.cpp -I"C:/SFML/SFML-3.0.0/include" -DSFML_STATIC

link:
	g++ Game.o main.o -o game -L"C:/SFML/SFML-3.0.0/lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows
	del /F main.o Game.o

clean:
	del /F main.o Game.o game.exe main.exe
