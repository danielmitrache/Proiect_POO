## Proiect POO

Joc 2D scris in C++ folosind SFML 3. 

Pentru a rula pe propriul sistem:
```bash
git clone <repo-link>
cd <repo>
make
./game
```

Pentru ca Makefile-ul să funcționeze, trebuie să existe următoarea ierarhie pe disc: `C:/SFML/SFML-3.0.0`.

Alternativ, dacă SFML este instalat într-o altă locație, actualizați variabilele `CXXFLAGS` și `LDFLAGS` din Makefile pentru a reflecta calea corectă. De exemplu:

```makefile
CXXFLAGS = -I"C:/path/to/SFML/include" ...
LDFLAGS = -L"C:/path/to/SFML/lib" ...
```

Daca prima comanda `make` a esuat, folositi comanda `make clean` inainte de a incerca din nou.

Dacă utilizați Windows și `make` nu funcționează, încercați să folosiți comanda `mingw32-make`:

```bash
mingw32-make clean
mingw32-make
./game
```

