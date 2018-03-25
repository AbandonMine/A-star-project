#ifndef TMP_H
#define TMP_H
#include "stale.h"
#include "astar.h"
using namespace std;

void create_2d(char map[][N]);
void write_2d(char map[][N]);
void sign(char map[][N], int x, int y, char co);

bool czy(int co);

void pisanie_tabeli(node * tab);
void wypisz_t(node * tab, int licznik);

void save_to_file(char map[][N]);
void czy_zapisac_tabele(node * tab);
void funkcje_zapisu(node * Q, char map[][N]);

void drop_list(Telement *& head);

#endif // TMP_H
