# 'CC' yra kompiliatoriaus kintamasis. Šiuo atveju nurodyta naudoti 'g++' kompiliatorių.
CC = g++

# 'CFLAGS' yra kintamasis, kuriame saugomos kompiliavimo vėliavos. Šiuo atveju nurodyta optimizacija '-O3' ir C++17 standartas.
CFLAGS = -O3 -std=c++17

# Pagrindinė taisyklė 'all', kuri nurodo, kaip sukurti vykdomąjį failą 'run' iš objektinių failų.
all: main.o file_functions.o mylib.o
	# Ši komanda sujungia visus objektinius failus į vieną vykdomąjį failą pavadinimu 'run'.
	$(CC) $(CFLAGS) main.o file_functions.o mylib.o -o run

# Taisyklės, kaip sukompiliuoti šaltinio failus į objektinius failus.
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

file_functions.o: file_functions.cpp file_functions.h
	$(CC) $(CFLAGS) -c file_functions.cpp
	
mylib.o: mylib.cpp mylib.h
	$(CC) $(CFLAGS) -c mylib.cpp

# Taisyklė 'clean', kuri yra naudojama šalinti visus sukompiliuotus objektinius failus ir vykdomąjį failą.
clean:
	# Šalinami visi objektiniai failai ir vykdomasis failas 'run'.
	rm *.o run
