//用char的完整程式
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#define SIZEX 1300   
#define SIZEY 1300
#define ERROR 0.05
#define ERRORSIZE 128000


void errorloss (char*,int,int);
void arraprint (char*,int,int);
void shuffle (char*,size_t);
int finderror (char*,int);
double findnearerr (char*, int, int);
void fillerr (char*,int);

int main (void)
{ 
    int x,y=0;
    char matrix [SIZEX][SIZEY]={0};
    fillerr(&matrix[0][0],ERRORSIZE);
    
    // arraprint(&matrix[0][0],SIZEX,SIZEY);
    // printf("-------------------------------------------------\n");
    
    for (int i=0;i<1000;i++)
    {
        int errorspot=0;
        double nearest_dis=0;
        double avrnearest_dis=0;
        double neighborratio=0;
        double nearbyerr=0;
        shuffle(&matrix[0][0],SIZEX*SIZEY);

    // //arraprint(&matrix[0][0],SIZE);   
        int num=0;
        while (errorspot<SIZEX*SIZEY)
        {
            errorspot=finderror(&matrix[0][0],errorspot);
            num+=1;
            if (errorspot==-1)
            {
            //printf("error spot:%d error finding stop\n",errorspot);
                break;
            }
            nearest_dis = findnearerr (&matrix[0][0],errorspot,1);
        //printf("nearest distense:%f \n",nearest_dis);
            if (nearest_dis==1)
                {nearbyerr=nearbyerr+1;}
        //printf("相鄰點數＝ %d\n",nearbyerr);
            avrnearest_dis=nearest_dis+avrnearest_dis;
            errorspot+=1;      
    }
    
    avrnearest_dis= avrnearest_dis/ERRORSIZE;
    neighborratio=nearbyerr/ERRORSIZE;
    FILE *fp = NULL ;
    fp = fopen("./result_data/1600loss05persent.csv","a");

    
    printf("ratio=%f\naverage=%f\n",neighborratio,avrnearest_dis);
    fprintf(fp,"%9f\t%9f\n",neighborratio,avrnearest_dis);

    }
    
    
    return 0;
}
void fillerr (char* mat,int num){
    for (int i=0;i<num;i++){
        mat[i]=1;
    }
    return;
}

void errorloss(char *arra,int val,int amp)
{
    int a = val/amp;
    int b = val%amp;
    for(int i=0;i<a;i++)//整數部分填值
    {
        for (int j=0;j<amp;j++)
        {
            arra[i*amp+j]=1;
        }
        
    }
    for(int t=0;t<b;t++)//餘數部分填值
    {
        arra[(a+1)*amp+t]=1;
    }
    
    return;
}

void arraprint(char *arra,int ampX,int ampY)//把整個陣列印出來
{
    
    for (int i=0;i<ampX;i++)
    {
        for (int j=0;j<ampY;j++)
        {
            printf("%d ",arra[i*ampX+j]);
        }
        printf("\n");
    }
    return;
}

void shuffle(char *array, size_t n) //打亂矩陣
{
    sleep(1);
    srand(time(NULL));
    if (n > 1) {
        for (size_t i = 0; i < n - 1; i++) {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
    
    return;
}

int finderror (char* matrix, int ord)//尋找錯誤
{
    // printf("finderror");
    int err;
    int i;
    for (i=ord;i<SIZEX*SIZEY;i++)
    {
        if (matrix[i]==1)
        {
            err = i;
            return err;
        }
    }
    return -1;
}

double findnearerr (char* matrix, int ord, int count)
{
    int x=ord/SIZEX;
    int y=ord%SIZEX;
    int xa=x-count;
    int ya=y-count;
    int pos=0;
    double dis[2]={0};
    dis[0]= (2*count+1)*sqrt(2);
    for (int i1=1;i1<=count*2;i1++)
    {
        ya = ya+1;
        if (ya>=SIZEX||ya<0||xa>=SIZEY||xa<0)
        {
            continue;
        }
        pos=SIZEY*xa+ya;    
        
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
        if (ya>=SIZEX||ya<0||xa>=SIZEY||xa<0)
        {
            continue;
        }
        pos=SIZEY*xa+ya;    
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
        if (ya>=SIZEX||ya<0||xa>=SIZEY||xa<0)
        {
            continue;
        }
        pos=SIZEY*xa+ya;    
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
        if (ya>=SIZEX||ya<0||xa>=SIZEY||xa<0)
        {
            continue;
        }
        pos=SIZEY*xa+ya;    
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
