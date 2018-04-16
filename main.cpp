
#include "opencvlib.h"

#include <iostream>

#include "astar_do_open.h"

using namespace std;
using namespace cv;

Mat menu;
bool clicked = false;
const int radius_pen = 5;

int xstart = 0, ystart = 0, xcelu = 0, ycelu = 0;
void set_board(Mat & matrix)
{
    for(int i = 0; i < matrix.rows; i++)
        for(int j = 0; j < matrix.cols; j++)
        {
            if(i == 0 || j == 0 || i == matrix.rows-1 || j == matrix.cols-1)
            {
                matrix.at<Vec3b>(i, j)[0] = 0;
                matrix.at<Vec3b>(i, j)[1] = 0;
                matrix.at<Vec3b>(i, j)[2] = 0;
            }
            else
            {
                matrix.at<Vec3b>(i, j)[0] = 255;
                matrix.at<Vec3b>(i, j)[1] = 255;
                matrix.at<Vec3b>(i, j)[2] = 255;
            }

        }
}


void onMouse(int event, int x, int y, int flags, void * param)
{
    switch(event)
    {
        case CV_EVENT_LBUTTONDOWN:

            circle(menu, Point(x,y), radius_pen, Scalar(0,0,0), -1);
            clicked = true;

            break;

        case EVENT_MBUTTONDOWN:


            circle(menu, Point(x, y), radius_pen, Scalar(0, 0, 255), -1);
            xstart = x;
            ystart = y;
            break;

        case CV_EVENT_LBUTTONUP:

            circle(menu, Point(x,y), radius_pen, Scalar(0,0,0), -1);
            clicked = false;
            break;

        case CV_EVENT_MOUSEMOVE:
            if(clicked)
            {
                circle(menu, Point(x,y), radius_pen, Scalar(0,0,0), -1);
                break;
            }
            break;

        case CV_EVENT_RBUTTONDOWN:

            circle(menu, Point(x, y), radius_pen, Scalar(255, 0, 0), -1);
            xcelu = x;
            ycelu = y;
            break;

        default: break;

    }
}

int main()
{
    menu.create(480, 640, CV_8UC3);
    set_board(menu);
    namedWindow("Main");
    imshow("Main", menu);
    setMouseCallback("Main", onMouse);
    while (waitKey(20) != 27)
    {
        imshow("Main", menu);

        if(waitKey(20) == 'a')
        {
           /* if(menu.at<Vec3b>(xstart, ystart)[0] == 0 &&
               menu.at<Vec3b>(xstart, ystart)[1] == 0 &&
               menu.at<Vec3b>(xstart, ystart)[2] == 255 &&
               menu.at<Vec3b>(xcelu, ycelu)[0] == 255 &&
               menu.at<Vec3b>(xcelu, ycelu)[1] == 0 &&
               menu.at<Vec3b>(xcelu, ycelu)[2] == 0) */
                    algorytm_a_gwiazdka(xstart, ystart, xcelu, ycelu, menu);
           // else
                //cout << "ERROR PLACEHOLDER" << endl;
        }
        if(waitKey(20) == 'r')
        {
            set_board(menu);
        }

    }

    //waitKey(0);
    return 0;
}

