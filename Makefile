main: *.c *.h
	gcc -W -Wall -Wextra -pedantic -mwindows -o main *.c *.h -Isrc/include -Lsrc/lib -lSDL2 -lSDL2main -Isrc/include-image -Lsrc/lib-image -lSDL2_image -Isrc/include-mixer -Lsrc/lib-mixer -lSDL2_mixer
game: *.c *.h
	gcc -W -Wall -Wextra -pedantic -mwindows -o "Five Nights at Freddy's" *.c *.h -Isrc/include -Lsrc/lib -lSDL2 -lSDL2main -Isrc/include-image -Lsrc/lib-image -lSDL2_image -Isrc/include-mixer -Lsrc/lib-mixer -lSDL2_mixer
clean:
	rm *.exe *.gch *.stackdump