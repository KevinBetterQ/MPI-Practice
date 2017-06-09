#include <stdio.h>
#include <mpi.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#define PI  3.1415926535898
double Integral(double a,double b,double (*fun)(double))
{   int i,l;    
    double n=0.001,s=0;    
    l=(b-a)/n;    
    double top,base;    
    for(i=0;i<l;i++){        
    top=(*fun)(a+n*i);        
    base=(*fun)(a+n*(i+1));        
    s=(top+base)*n/2+s;    }    
    printf("cos(x)在(%lf,%lf)上的积分为%lf\n",a,b,s);
    return s;
}
int main(int argc,char** argv){
    MPI_Comm comm = MPI_COMM_WORLD;
    int size,rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(comm,&size);
    MPI_Comm_rank(comm,&rank);
    int i;
    double sum=0;
    double sum=0;
    double sum=0;
    double a=0;                                                                                                        
    double b=2*PI;        
    double n=(b-a)/size;
    double *sbuf=(double *)malloc(sizeof(double)* size);
    double *rbuf=(double *)malloc(sizeof(double)* size);
    double *start=(double *)malloc(sizeof(double)*1);
    double *part=(double *)malloc(sizeof(double)*1);
    if(rank==0){
       for(i=0;i<size;i++)
        sbuf[i]=a+n*i;
    }
    MPI_Scatter(sbuf,1,MPI_DOUBLE,start,1,MPI_DOUBLE,0,comm);
    (*part)=Integral((*start),(*start)+n,cos);
    MPI_Gather(part,1,MPI_DOUBLE,rbuf,1,MPI_DOUBLE,0,comm);
    if(rank==0){
    for(i=0;i<(size+1);i++)
    {
      sum+=rbuf[i];
    }
    printf("cos(x)在(%lf,%lf)的定积分为%lf\n",a,b,sum);
    }
    MPI_Finalize();
    return 0;
}