#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#define SIZE 2048
#define ERROR 0.05
#define ERRORSIZE 209715

int main ()
{
    printf("hello world");
}

double findnearerr (char* matrix, int ord, int count)
{
    int x=ord/SIZE;
    int y=ord%SIZE;
    int xa=x-count;
    int ya=y-count;
    int pos=0;
    double dis[2]={0};
    dis[0]= (2*count+1)*sqrt(2);
    for (int i1=1;i1<=count*2;i1++)
    {
        ya = ya+1;
        if (ya>=SIZE||ya<0||xa>=SIZE||xa<0)
        {
            continue;
        }
        pos=SIZE*xa+ya;    
        
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
        if (ya>=SIZE||ya<0||xa>=SIZE||xa<0)
        {
            continue;
        }
        pos=SIZE*xa+ya;    
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
        if (ya>=SIZE||ya<0||xa>=SIZE||xa<0)
        {
            continue;
        }
        pos=SIZE*xa+ya;    
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
        if (ya>=SIZE||ya<0||xa>=SIZE||xa<0)
        {
            continue;
        }
        pos=SIZE*xa+ya;    
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
