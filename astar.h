#ifndef ASTAR_H
#define ASTAR_H
#include "stale.h"
class node
{
private:
    int x_akt;
    int y_akt;
    float h;
    float g;
    float f;
    node * rodzic;
public:
    node(int X_p, int Y_p,  float H_p, float G_p, float F_p, node * r_p);

    int getx();
    int gety();
    float geth();
    float getg();
    float getf();
    node* getr();
    void ustaw_x(int x);
    void ustaw_y(int y);
    void policz_h(int xcelu, int ycelu);
    void policz_g(int x_Q, int y_Q);
    void policz_f();
    bool czy_cel(int xcelu, int ycelu);
    void zmien_rodzica(node * na_jaki);

};

struct Telement
{
    node * pole;
    Telement * next;
};

void wybierz_Q(Telement * otwarta_glowa, node *& Q);
void dodaj_do_zamknietej(Telement *& glowa, node * co);
void dodaj_do_otwartej(Telement *& glowa, int x, int y, int xcelu, int ycelu, node * Q, char map[][N], bool czy);
bool czy_jest_w_liscie(Telement * glowa, int x, int y);
bool czy_zakazane(char map[][N], int x, int y);
void zamien_rodzica(Telement * glowa, int x, int y, node* gdzie);
void pokoloruj_droge(node *Q, char map[][N]);
void usun_z_otwartej(Telement *& glowa, node * co);
node * algorytm_a_gwiazdka(int xstart, int ystart, int xcelu, int ycelu, char map[][N]);
#endif // ASTAR_H
