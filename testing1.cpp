//用window跑shift+ctrl+B編譯
//跑./testing1.exe
//如果要在window的VS code跑還需要下載MinGW
//且加入環境變數"C:\MinGW\bin"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
//x^7 + x^3 + 1
//初始值:0b1110010=114
#define SIZEX 10
#define SIZEY 12
#define SIZE 120
#define ERROR 0.05
#define ERRORSIZE 6
#define INITIAL 0b1110010


void arraprint (char*);
int stagedefine (void);
int lfsr (int,int,int*);
void fillerr (char*,int);
int main (void){
    int settingmatrix[32]={7,3,0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0,0,0,0,0};
    char matrix [SIZEY][SIZEX]={0};
    int stage = stagedefine();
    int a = lfsr(INITIAL,stage,&settingmatrix[0]);
    for (int i=0;i<ERRORSIZE;i++)
    {   
        if (a>=(SIZEX*SIZEY)){
            printf("i=%d %d pass\n",i,a);
            a = lfsr(a,stage,&settingmatrix[0]);
            i=i-1;
            continue;
        }
        else {
            fillerr(&matrix[0][0],a);
            printf("i=%d %d\n",i,a);
            a = lfsr(a,stage,&settingmatrix[0]);
        }
        
    }
    arraprint(&matrix[0][0]);
    
    return 0;
}

void fillerr (char* mat,int s){
    mat[s]=1;
    return;
}

int lfsr (int intial, int s, int* set){
    //設定x^7 + x^3 + 1
    int mat[32]={0};

    int i,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10=0;
    i=1;//7
    if ((i&intial)==1)
    {
        mat[0]=1;   
    }
    else{mat[0]=0;}

    int c=0;
    int c1=s;
    int setstop=0;
    int j=1;

    for (int t=0;t<32;t++){
        c=set[t];
        if (c==0)
        {
            break;
        }
        setstop+=1;
        c1=c1-c;
        i<<=c1;
        if ((i&intial)==(pow(2,(s-c))))
        {
            mat[j]=1;
        }
        else{mat[j]=0;} 
        j+=1;
    }
    // i<<=4;//3 
    // //printf("i<<1=%d\n",i);
    // if ((i&intial)==16)
    // {
    //     i2=1;
    // }
    // else{i2=0;}        
    
    // i=i1^i2;
    for (int ii=1;ii<setstop;ii++){
        mat[0]=mat[ii]^mat[0];
    }
    i<<=(s-1);
    intial>>=1;
    // intial+=i;
    intial+=mat[0];
    int tem = pow(2,s)-1;
    intial&=tem;
    // printf("intial:%d\n",intial);
    return intial;
}

int stagedefine (void){
    int x = SIZEX;
    int y = SIZEY;
    int s = 2;
    while (1){
        if (x*y<=pow(2,s)&&x*y>pow(2,s-1)){
            return s;
        }
        s=s+1;
    }
}

void arraprint (char* mat){
    int x = SIZEX;
    int y = SIZEY;
    for (int i=0;i<x*y;i++){
        printf("%d ",mat[i]);
        if (i<x-1){
            continue;
        }
        if((i+1)%(x)==0){
            printf("\n");
        }
    }
    return;
}