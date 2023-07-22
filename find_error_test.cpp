#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#define SIZE 2048
#define SIZEX 10
#define SIZEY 12
#define ERROR 0.05
#define ERRORSIZE 209715

double findnearerr (char*, int, int);
void printcheck (char* , int );

int main ()
{
    char arr[SIZEY][SIZEX] = {{0,1,0,0,0,0,0,0,0,0},{1,0,1,1,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},
                             {1,0,0,0,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,1}};
    double a;
    a = findnearerr(&arr[0][0],12,1);
    printcheck(&arr[0][0],10);
    printf("a:%f",a);
    return 0;
}

void printcheck (char* arr, int ord)
{
    printf("s:%c",arr[ord]);
    return;
}

double findnearerr (char* matrix, int ord, int count)
{
    int x=ord/SIZEX;
    int y=ord%SIZEY;
    int xa=x-count;
    int ya=y-count;
    int pos=0;
    double dis[2]={0};
    dis[0]= (2*count+1)*sqrt(2);
    for (int i1=1;i1<=count*2;i1++)
    {
        ya = ya+1;
        if (ya>=SIZEY||ya<0||xa>=SIZEX||xa<0)
        {
            continue;
        }
        pos=SIZEX*xa+ya;    
        
        if (matrix[pos]==1)
        {
            dis[1]=sqrt((x-xa)*(x-xa)+(y-ya)*(y-ya));
            if (dis[1]<dis[0])
            {
                dis[0]=dis[1];
            }
        }
        else if (matrix[pos]==0)
        {
            continue;
        }
    }
    for (int i2=1;i2<=count*2;i2++)
    {
        xa=xa+1;
        if (ya>=SIZEY||ya<0||xa>=SIZEX||xa<0)
        {
            continue;
        }
        pos=SIZEX*xa+ya;    
        if (matrix[pos]==1)
        {
            dis[1]=sqrt((x-xa)*(x-xa)+(y-ya)*(y-ya));
            if (dis[1]<dis[0])
            {
                dis[0]=dis[1];
            }
        }
        else if (matrix[pos]==0)
        {
            continue;
        }
    }
    for (int i3=1;i3<=count*2;i3++)
    {
        ya=ya-1;
        if (ya>=SIZEY||ya<0||xa>=SIZEX||xa<0)
        {
            continue;
        }
        pos=SIZEX*xa+ya;    
        if (matrix[pos]==1)
        {
            dis[1]=sqrt((x-xa)*(x-xa)+(y-ya)*(y-ya));
            if (dis[1]<dis[0])
            {
                dis[0]=dis[1];
            }
        }
        else if (matrix[pos]==0)
        {
            continue;
        }
    }
    for (int i4=1;i4<=count*2;i4++)
    {
        xa=xa-1;
        if (ya>=SIZEY||ya<0||xa>=SIZEX||xa<0)
        {
            continue;
        }
        pos=SIZEX*xa+ya;    
        if (matrix[pos]==1)
        {
            dis[1]=sqrt((x-xa)*(x-xa)+(y-ya)*(y-ya));
            if (dis[1]<dis[0])
            {
                dis[0]=dis[1];
            }
        }
        else if (matrix[pos]==0)
        {
            continue;
        }
    }
    if (dis[1]==0)
    {
        return findnearerr (matrix,ord,count+1);
    }
    return dis[0];
}
