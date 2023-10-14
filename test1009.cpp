//用char的完整程式
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#define SIZEX 400   
#define SIZEY 400
#define ERROR 0.15
#define ERRORSIZE 24000

#define STAGE 18

int lfsr(int,char*);
void coordinate(int,int*);
void arraprint (char*,int,int);

int main (void)
{ 
    char matrix [SIZEX][SIZEY]={0};
    int m_seq = pow(2,STAGE);
    char setting [32] = {18,7,0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,0,0,0,0};
    int intial =1 ;
    int temp = intial;
    int round = ((SIZEX*SIZEY)/1000)-1;
    //-------settings----------------------------------------------------//

    for (int i1=0;i1<500;i1++){
        if ((i1%10)==0){
            printf("i1=%d\n",i1);
        }
        intial = temp;
        int skip=0;//count the numbers that have been skip
        int seq=0;//index on the sequence that is include in the range of the matrix
        int errplace[ERRORSIZE]={0};
        for (int q=0;q<SIZEX*SIZEY;q++){
            intial=lfsr(intial,&setting[0]);
            if (intial==temp){
                printf("wrong seq\n");
                break;
            }
            // printf("lfsr:%d\n",intial);
            if (intial>SIZEX*SIZEY){
                skip+=1;
                // printf("skip\n");
                continue;
            }
            else{
                errplace[seq]=intial;
                seq+=1;
                if (seq==ERRORSIZE){
                    // printf("end point ");
                    break;
                }
            }
        }
        // printf("skip:%d seq:%d\n",skip,seq);
        int target,count = 0;
        double distance[2] = {0}; 
        int tarcoor[2] = {0};
        int concoor[2] = {0};
        double nearbyerr=0;
        double avrnearest_dis=0;
        double neighborratio=0;
        for (int q1=0;q1<ERRORSIZE;q1++){
        // for (int q1=0;q1<1;q1++){  
            // printf("dis[0]=%f dis[1]=%f\n",distance[0],distance[1]);
            distance[0] = 0;
            distance[1] = 0;  
            target = errplace [q1];
            coordinate(target,&tarcoor[0]);
            // printf("q1:%d %d tx=%d ty=%d\n",q1,target,tarcoor[0],tarcoor[1]);
            for (int q2=0;q2<ERRORSIZE;q2++){
                if (q1==q2){
                    continue;
                }
                count = errplace [q2];
                coordinate(count,&concoor[0]);
                // printf("%d cx=%d cy=%d\n",count,concoor[0],concoor[1]);
                int xx = pow((concoor[0]-tarcoor[0]),2);
                int yy = pow((concoor[1]-tarcoor[1]),2);
                double aa = sqrt(xx+yy);
                // printf("xx:%d yy:%d aa:%f\n",xx,yy,aa);
                distance[1] = aa;
                // printf("dis=%f\n",distance[1]);
                if (distance[0]==0||distance[1]<distance[0]){
                    distance[0]=distance[1];
                    // printf("dis[0]=%f dis[1]=%f\n",distance[0],distance[1]);
                    if (distance[1]==1){
                        nearbyerr+=1;
                        continue;
                    }
                }
                
            }
            avrnearest_dis=avrnearest_dis+distance[0];
            // printf("total_dis:%f distance[0]:%f\n",avrnearest_dis,distance[0]);
            // printf("totaldis:%f\n",avrnearest_dis);
        }
        avrnearest_dis= avrnearest_dis/ERRORSIZE;
        neighborratio= nearbyerr/ERRORSIZE;
        printf("ratio=%f  average=%f\n",neighborratio,avrnearest_dis);
    
        FILE *fp = NULL ;
        fp = fopen("./m-seqresultdata/400loss15persent.csv","a");
        fprintf(fp,"%9f\t%9f\n",neighborratio,avrnearest_dis);
        temp += round;
    }
    
    
    return 0;
}
void coordinate (int target,int* coor){
    coor[0]=target%SIZEX;
    coor[1]=target/SIZEX;
    return;
}
int lfsr (int intial, char* setting)
{
    int step=STAGE;
    int i=1;
    int i1,i2,it=0;
    // printf("start\n");
    // printf("%d\n",intial);
    for (int j=0;j<32;j++){
        // printf("j=%2d\n",j);
        if(j==0){
            i=1;
            if((i&intial)==i){
                i1=1;
            }
            else{
                i1=0;
            }
            continue;
            }
        else if(setting[j]==0){
            break;
        }
        else{
            // printf("i11=%2d\n",i);
            it=setting[j-1]-setting[j];
            // printf("i22=%2d\n",i);
            i=i<<it;
            // printf("i33=%2d\n",i);
            if ((i&intial)==i){
                i2=1;
            }
            else{
                i2=0;
            }
            // printf("i2=%2d\n",i2);
        }
        i1=i1^i2;
        // printf("ia=%2d\n",i1);
    }
     
    
    // i=i1^i2;
    i1<<=(step-1);
    intial>>=1;
    intial+=i1;
    // intial&=1048575;
    // printf("%d\n",intial);
    return intial;
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


