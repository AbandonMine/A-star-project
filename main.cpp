#include <iostream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <math.h>
#include "tmp.h"
#include "tmp.cpp"
#include "astar.h"
#include "astar.cpp"
#include "stale.h"
using namespace std;

int main()
{
    srand(time(0));
    char map[N][N]  =
    {
        '@', '@', '@', '@', '@', '@', '@', '@', '@', '@',
        '@', '.', '@', '.', '.', '.', '.', '@', '.', '@',
        '@', '.', '.', '.', '.', '.', '.', '@', '.', '@',
        '@', '.', '.', '.', '.', '.', '.', '@', '.', '@',
        '@', '.', '.', '.', '.', '.', '.', '@', '.', '@',
        '@', '.', '.', '.', '.', '.', '.', '@', '.', '@',
        '@', '.', '.', '.', '.', '.', '.', '@', '.', '@',
        '@', '.', '@', '@', '@', '@', '@', '@', '.', '@',
        '@', '.', '.', '.', '.', '.', '.', '.', '.', '@',
        '@', '@', '@', '@', '@', '@', '@', '@', '@', '@',
    }
        ;

    int xstart, ystart, xcelu, ycelu;
    clock_t czas_trwania_alogrytmu;
    node * tab = NULL;

    //te funkcje zostana wyrzucone po wprowadzeniu wczytywania mapy i GUI
    //create_2d(map);
    write_2d(map);
    do
    {
    cout << "Podaj parametry punktu startu: (0-" << N-1 << ")" << endl << "x: ";
    cin >> xstart;
    cout << "y: ";
    cin >> ystart;
    } while( map[ystart][xstart] == '@');
    sign(map, ystart, xstart, 'S');
    system( "cls" );
    write_2d(map);
    do
    {
    cout << "Podaj parametry punktu finalnego: (0-" << N-1 << ")" << endl << "x: ";
    cin >> xcelu;
    cout << "y: ";
    cin >> ycelu;
    } while( map[ycelu][xcelu] == '@');
    sign(map, ycelu, xcelu, 'M');
    system( "cls" );
    write_2d(map);
    //koniec

    czas_trwania_alogrytmu = clock();
    tab = algorytm_a_gwiazdka(xstart, ystart, xcelu, ycelu, map);
    czas_trwania_alogrytmu = clock() - czas_trwania_alogrytmu;
    write_2d(map);
    cout << "Algorytm pracowal przez: " << (float(czas_trwania_alogrytmu))/CLOCKS_PER_SEC << " s."  << endl;
    pisanie_tabeli(tab);
    if(czy(2))
        save_to_file(map);
    czy_zapisac_tabele(tab);
    getchar();
    return 0;
}
