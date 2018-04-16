#include <iostream>

#include "opencvlib.h"

#include <cmath>
#include <cstdlib>

#include "astar_do_open.h"

using namespace std;
using namespace cv;
node :: node (int X_p, int Y_p,  float H_p, float G_p, float F_p, node * r_p)
{
    x_akt = X_p; y_akt = Y_p; h = H_p; g = G_p; f = F_p; rodzic = r_p;
}

int node :: getx() {return x_akt;}
int node :: gety() {return y_akt;}
float node :: geth() {return h;}
float node :: getg() {return g;}
float node :: getf() {return f;}
node* node :: getr() {return rodzic;}

void node :: ustaw_x(int x)
{
    this->x_akt = x;
}

void node :: ustaw_y(int y)
{
    this->y_akt = y;
}


void node :: policz_h(int xcelu, int ycelu)
{
    float xp = xcelu - x_akt;
    float yp = ycelu - y_akt;
    this->h = sqrt( xp * xp + yp * yp);
}

void node :: policz_g(int x_Q, int y_Q)
{
    if(x_akt == x_Q || y_akt == y_Q)
        this->g += 1;
    else
        this->g += 1.4;
}

void node :: policz_f()
{
    this->f = h + g;
}

bool node :: czy_cel(int xcelu, int ycelu)
{
    if(x_akt == xcelu && y_akt == ycelu)
        return true;
    else
        return false;
}

void node :: zmien_rodzica(node * na_jaki)
{
    this->rodzic = na_jaki;
}

void wybierz_Q(Telement * otwarta_glowa, node *& Q)
{
    Telement * akt = otwarta_glowa;
    node * minf = otwarta_glowa->pole;
    while(akt != NULL)
    {
        if(akt->pole->getf() < minf->getf())
            minf = akt->pole;
        akt = akt->next;
    }
    Q = minf;
}

void dodaj_do_zamknietej(Telement *& glowa, node * co)
{
        Telement * tmp;
        Telement * nowy;
        nowy = new Telement;
        nowy->pole = co;
        nowy->next = NULL;
        if(glowa == NULL)
        {
            glowa = nowy;
        }
        else
        {
            tmp = glowa;
            while(tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            tmp->next = nowy;

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

void dodaj_do_otwartej(Telement *& glowa, int x, int y, int xcelu, int ycelu, node * Q, Mat menu, bool czy)
{
        Telement * tmp;
        Telement * nowy;
        nowy = new Telement;
        nowy->pole = new node(x, y, 0, Q->getg(), 0, Q);
        if(czy == true)
        {
            menu.at<Vec3b>(y, x)[0] = 0;
            menu.at<Vec3b>(y, x)[1] = 255;
            menu.at<Vec3b>(y, x)[2] = 0;
        }
        nowy->pole->policz_h(xcelu, ycelu);
        nowy->pole->policz_g(Q->getx(), Q->gety());
        nowy->pole->policz_f();
        nowy->next = NULL;
        if(glowa == NULL)
            glowa = nowy;
        else
        {
            tmp = glowa;
            while(tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            tmp->next = nowy;

        }

}

bool czy_jest_w_liscie(Telement * glowa, int x, int y)
{
    Telement * akt = glowa;
    while(akt != NULL)
    {
        if(akt->pole->getx() == x && akt->pole->gety() == y)
            return true;
        akt = akt->next;
    }
    return false;
}


bool czy_zakazane(Mat menu, int x, int y)
{
                if(menu.at<Vec3b>(y,x)[0] == 0 && menu.at<Vec3b>(y,x)[1] == 0 && menu.at<Vec3b>(y,x)[2] == 0)
                     return true;
                else
                     return false;
}

void zamien_rodzica(Telement * glowa, int x, int y, node* gdzie)
{
    Telement * akt = glowa;
    while(akt != NULL)
    {
        if(akt->pole->getx() == x && akt->pole->gety() == y)
            break;
        akt = akt->next;
    }
    akt->pole->zmien_rodzica(gdzie);
}

void usun_z_otwartej(Telement *& glowa, node * co)
{
    Telement * akt, * tmp, * pop;
    akt = glowa;
    pop = NULL;
    while(akt != NULL)
    {
        if(akt->pole == co)
        {
            tmp = akt;
            if(akt == glowa)
                glowa = glowa->next;
            else
                pop->next = akt->next;
            akt = akt->next;
            delete tmp;
        }
        else
        {
            pop = akt;
            akt = akt->next;
        }
    }
}



void  pokoloruj_droge(node *Q, Mat menu)
{
    node * akt = Q;
    while(akt != NULL)
    {
        circle(menu, Point(akt->getx(), akt->gety()), 1, Scalar(255, 0, 0), -1);
        akt = akt->getr();
    }
}


void algorytm_a_gwiazdka(int xstart, int ystart, int xcelu, int ycelu, Mat menu)
{
    cout << "start" << endl;

    Telement * otwarta_glowa = NULL;
    Telement * zamknieta_glowa = NULL;

    node * Q;
    node * tmp;

    int dir_y [8] = {0, -1, -1, -1, 0, 1, 1, 1};
    int dir_x [8] = {1, 1, 0, -1, -1, -1, 0, 1};

    int x_s;
    int y_s;

    float nowy_g;
    float stary_g1;
    float stary_g2;
    float stary_g;

    bool zaznaczanie = true;

    otwarta_glowa = new Telement;
    otwarta_glowa->pole = new node(xstart, ystart, 0, 0, 0, NULL);
    if(otwarta_glowa->pole->czy_cel(xcelu, ycelu))
    {
        cout << "Punkt startowy i końcowy zanjduja sie w tym samym miejscu!" << endl;
        return;
    }
    otwarta_glowa->pole->policz_h(xcelu, ycelu);
    otwarta_glowa->pole->policz_f();
    otwarta_glowa->next = NULL;
    while(otwarta_glowa != NULL)
    {
        wybierz_Q(otwarta_glowa, Q);
        dodaj_do_zamknietej(zamknieta_glowa, Q);
        usun_z_otwartej(otwarta_glowa, Q);

        if(Q->czy_cel(xcelu, ycelu))
        {
            pokoloruj_droge(Q, menu);
            drop_list(otwarta_glowa);
            drop_list(zamknieta_glowa);
            return;
        }

        for(int i = 0; i < 8; i++)
        {
            x_s = Q->getx() + dir_x[i];
            y_s = Q->gety() + dir_y[i];

            if(!czy_jest_w_liscie(zamknieta_glowa, x_s, y_s) && !czy_zakazane(menu, x_s, y_s))
            {

                if(!czy_jest_w_liscie(otwarta_glowa, x_s, y_s))
                {
                       dodaj_do_otwartej(otwarta_glowa, x_s, y_s, xcelu, ycelu, Q, menu, zaznaczanie);
                }
                else
                {
                    tmp = (Q->getr());
                    nowy_g = sqrt( (x_s - tmp->getx() ) * ( x_s - tmp->getx() ) + ( y_s - tmp->gety() ) * ( y_s - tmp->gety()) );
                    stary_g1 = sqrt( (Q->getx() - tmp->getx()) * (Q->getx() - tmp->getx()) + (Q->gety() - tmp->gety()) * (Q->gety() - tmp->gety()));
                    stary_g2 = sqrt( (x_s - Q->getx()) * (x_s - Q->getx()) + (y_s - Q->gety()) * (y_s - Q->gety()));
                    stary_g = stary_g1 + stary_g2;
                    if(nowy_g > stary_g)
                    {
                        zamien_rodzica(zamknieta_glowa, x_s, y_s, tmp);
                    }

                }
            }

        }


    }
   cout << "Nie znaleziono polaczenia!" << endl;
   drop_list(otwarta_glowa);
   drop_list(zamknieta_glowa);
   return;
}
