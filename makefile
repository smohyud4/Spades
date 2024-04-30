all: compile link

compile:
	 g++ -c main.cpp -I"C:\Users\Sulaiman Mohyuddin\Documents\libraries\SFML-2.5.1\include" 

link:
	g++ main.o -o main -L"C:\Users\Sulaiman Mohyuddin\Documents\libraries\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
clean:
	rm -f main *.o
