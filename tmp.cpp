#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "tmp.h"
#include "astar.h"
#include "stale.h"
using namespace std;

bool czy(int co)
{
    char choice;
    switch( co )
    {
    case 0:
        cout << "Czy zaznaczyc na mapie wszystkie punkty sprawdzane przez algorytm? [Y/N]" << endl;
        break;
    case 1:
        cout << "Czy wyswietlic droge w postaci tabeli? [Y/N]" << endl;
        break;
    case 2:
        cout << "Czy zapisac mape w pliku? [Y/N]" << endl;
        break;
    case 3:
        cout << "Czy zapisac tabele w pliku? [Y/N]" << endl;
        break;
    }

    do
    {
        cin >> choice;
        if(choice != 'y' && choice != 'Y' && choice != 'n' & choice != 'N')
        {
            cout << "Nieznane polecenie." << endl;
            cin.sync();
        }

    } while(choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');
    if(choice == 'y' || choice == 'Y')
        return true;
    else
        return false;
}

void create_2d(char map[][N])
{
    int random1;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
        {
            if(i == 0 || i == N-1 || j == 0 || j == N-1)
                map[i][j] = '@';
            else
            {
                random1 = rand()%4;
                if(random1 == 0)
                    map[i][j] = '@';
                else
                    map[i][j] = '.';
            }
        }
}
void write_2d(char map[][N])
{
    for(int i = 0; i < N; i++)
    {

        for(int j = 0; j < N; j++)
            cout << map[i][j];
        cout << endl;
    }
}
void sign(char map[][N], int x, int y, char co)
{
    map[x][y] = co;
}


int policz(node * tab)
{
    int ile = 0;
    node * akt = tab;
    while(akt!=NULL)
    {
        ile++;
        akt = akt->getr();
    }
    return ile;
}


void wypisz_t(node * tab, int licznik)
{

    if(tab != NULL)
    {
        wypisz_t(tab->getr(), licznik-1);
        cout << "Punkt nr " << licznik << " o wspolrzednych X: " << tab->getx() << " Y: " << tab->gety() << " odleglym o celu o  " << tab->geth() << " i koszcie " << tab->getg() << endl;

    }

}

void pisanie_tabeli(node * tab)
{
    bool tabela;
    int licznik = policz(tab);
    tabela = czy(1);
    if(tab == NULL)
    {
        cout << "Nie udalo sie znalezc drogi lub punkt startowy w tym samym miejscu co punkt koncowy." << endl;
    }
    if(tabela == true)
    {
        wypisz_t(tab, licznik);
    }
}

void save_to_file(char map[][N])
{
    string nazwa_pliku;
    ofstream plik;
    cout << "Podaj nazwe pliku: " << endl;
    do
    {

    getline(cin, nazwa_pliku);
    plik.open(nazwa_pliku.c_str());
    }while (!plik.good());
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            plik << map[i][j];
        }
        plik << endl;
    }
    plik.close();
}



void czy_zapisac_tabele(node * tab)
{
    int licznik = policz(tab);
    if(czy(3))
    {
        string nazwa_pliku;
        ofstream plik;
        cout << "Podaj nazwe pliku: " << endl;
        do
        {

        getline(cin, nazwa_pliku);
        plik.open(nazwa_pliku.c_str());
        }while (!plik.good());
        while(tab != NULL)
        {
            plik << "Punkt nr " << licznik << " o wspolrzednych X: " << tab->getx() << " Y: " << tab->gety() << " odleglym o celu o  " << tab->geth() << " i koszcie " << tab->getg() << endl;
            tab = tab->getr();
            licznik--;
        }

        plik.close();
    }
}

void drop_list(Telement *& head)
{
    Telement * tmp;
    while(head != NULL)
    {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}

void funkcje_zapisu(node * Q, char map[][N])
{

    pisanie_tabeli(Q);
    if(czy(2))
        save_to_file(map);
    czy_zapisac_tabele(Q);
}
