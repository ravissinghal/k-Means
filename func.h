#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LEN 1024
#define MAX_ROW 500
#define K 3

char str[] = "Output1";

struct DataC{

   // Adding new values
   
   char Date[10];
   int S_id;
   char S_name[50];
   //Done Adding
   float Flow;
   float Temp;
   float DO;
   float Sat;
   float pH;
   float Cond;
   int Class;
};


void normalize(struct DataC *data, struct DataC *dataN, int n);
void min(struct DataC *data, int n, float* miF, float* miT, float* miD, float* miS, float* miP, float* miC);
void max(struct DataC *data, int n, float* maF, float* maT, float* maD, float* maS, float* maP, float* maC);
void random(struct DataC* dataN, int n, int rd_index[K], struct DataC* K1);
void euclidean(struct DataC* data, struct DataC* dataN, struct DataC* K1,  float dis[MAX_ROW][K], int n, int min[n]);
int get_minimum(float dis[MAX_ROW][K], int i, float minimum);
void calcualate_centers( int c[K], int n, struct DataC* dataN);
void mean(struct DataC* dataN, struct DataC* K2, int n, int c[K]);
void assign_mean(struct DataC* K1, struct DataC* K2);
int check_equal(struct DataC* K1, struct DataC* K2);
void write_csv(char *filename, struct DataC* dataN, int n, struct DataC* data);


// *******************************************************************************************************************************************
// 0 -false, 1 - true
int check_equal(struct DataC* K1, struct DataC* K2)
{
   int i;
   for( i = 0; i < K; i++)
   {
      if( fabsf(K1[i].Flow - K2[i].Flow) <= 0.03 && fabsf(K1[i].Temp - K2[i].Temp) <= 0.03 && fabsf(K1[i].DO - K2[i].DO) <= 0.03 && fabsf(K1[i].Sat - K2[i].Sat) <= 0.03 && 
         fabsf(K1[i].pH - K2[i].pH) <= 0.03 && fabsf(K1[i].Cond -K2[i].Cond) <= 0.03)
      {
         continue;
      }
      
      else
      {
         printf("1");
         assign_mean(K1,K2);
         return 1;
         
      }
   }
   
   printf("0");
   return 0;
}   
   
// *******************************************************************************************************************************************

void write_csv(char *filename, struct DataC* dataN, int n, struct DataC* data)
{
   int i;
   printf("\nCreating a csv file............");
   FILE *fp;
   filename = strcat(filename,".csv");
   fp=fopen(filename,"w+");
   fprintf(fp, "Date,ID,Site,Flow,Temp,DO,Sat,pH,Cond,Cluster\n");  //Cond,EColi,
   for(i=0;i<n;i++)
   {  
      fprintf(fp, "%s,%d,%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%d\n", data[i].Date, data[i].S_id, data[i].S_name, data[i].Flow, data[i].Temp, data[i].DO, data[i].Sat, data[i].pH,data[i].Cond, data[i].Class); // (c1+i)->EColi,   
   }
      
   printf("\nDone");
   fclose(fp);

}  

// *******************************************************************************************************************************************

 /*
   ****************************************************************
   Assigning new mean calculated to initial mean structure
   ****************************************************************
   */

void assign_mean(struct DataC* K1, struct DataC* K2)
{
   int i;
   for(i=0;i<K;i++)
   {
      K1[i].Flow = K2[i].Flow;
      K1[i].Temp = K2[i].Temp;
      K1[i].DO = K2[i].DO;
      K1[i].Sat = K2[i].Sat;
      K1[i].pH = K2[i].pH;
      K1[i].Cond = K2[i].Cond;
   }
}


// *******************************************************************************************************************************************
  
/*
   ****************************************************************
   Calcualte the new mean of the clusters.
   ****************************************************************
   */

void mean(struct DataC* dataN, struct DataC* K2, int n, int c[K])
{
   int i;
   for( i = 0; i< n; i++)
   {
      if(dataN[i].Class == 0)
      {
         K2[0].Flow = K2[0].Flow + dataN[i].Flow;
         K2[0].Temp = K2[0].Temp + dataN[i].Temp;
         K2[0].DO = K2[0].DO + dataN[i].DO;
         K2[0].Sat = K2[0].Sat + dataN[i].Sat;
         K2[0].pH = K2[0].pH + dataN[i].pH;
         K2[0].Cond = K2[0].Cond + dataN[i].Cond;
      }
      
      if(dataN[i].Class == 1)
      {
         K2[1].Flow = K2[1].Flow + dataN[i].Flow;
         K2[1].Temp = K2[1].Temp + dataN[i].Temp;
         K2[1].DO = K2[1].DO + dataN[i].DO;
         K2[1].Sat = K2[1].Sat + dataN[i].Sat;
         K2[1].pH = K2[1].pH + dataN[i].pH;
         K2[1].Cond = K2[1].Cond + dataN[i].Cond;
      }
      
      if(dataN[i].Class == 2)
      {
         K2[2].Flow = K2[2].Flow + dataN[i].Flow;
         K2[2].Temp = K2[2].Temp + dataN[i].Temp;
         K2[2].DO = K2[2].DO + dataN[i].DO;
         K2[2].Sat = K2[2].Sat + dataN[i].Sat;
         K2[2].pH = K2[2].pH + dataN[i].pH;
         K2[2].Cond = K2[2].Cond + dataN[i].Cond;
      }
      
      
   }
   
   for(i=0;i<K;i++)
   {
      K2[i].Flow = K2[i].Flow/c[i];
      K2[i].Temp = K2[i].Temp/c[i];
      K2[i].DO = K2[i].DO/c[i];
      K2[i].Sat = K2[i].Sat/c[i];
      K2[i].pH = K2[i].pH/c[i];
      K2[i].Cond = K2[i].Cond/c[i];
      
   }
}


// *******************************************************************************************************************************************

/*
   ****************************************************************
   Calcualte the number of data points assigned to class 0, 1 and
   2 so that it can be passed to mean function
   ****************************************************************
   */

void calcualate_centers( int c[K], int n, struct DataC* dataN)
{
   int i;
   
   for(i=0;i<K;i++)
   {
      c[i] =0 ;
   }
   
   for( i = 0; i< n ; i++)
   {      
      if(dataN[i].Class == 0)
      {
         c[0] = c[0] + 1;
      }
      
      if(dataN[i].Class == 1)
      {
         c[1] = c[1] + 1;
      }
      
      if(dataN[i].Class == 2)
      {
         c[2] = c[2] + 1;
      }
   }
}   

// *******************************************************************************************************************************************
  
int get_minimum(float dis[MAX_ROW][K], int i, float minimum)
{
   int j;
   int val;
   for(j=0;j<K;j++)
   {
      if (dis[i][j] <= minimum)
         {
            val = j;
         }
   }
   return val;
}


// *******************************************************************************************************************************************
   
  /*
   ****************************************************************
   Calculating Euclidean distance and finding the minimum value and 
   assigning the class to the normalized & riginal data structure
   ****************************************************************
   */
 
 
 void euclidean(struct DataC* data, struct DataC* dataN, struct DataC* K1,  float dis[MAX_ROW][K], int n, int min[n])
{
   int i,j;
   float minimum;
   for( i = 0; i< n; i++)
   {
      for( j = 0; j< K; j++)
      {
         dis[i][j] = sqrt(pow(dataN[i].Flow - K1[j].Flow, 2) + pow(dataN[i].Temp - K1[j].Temp, 2) + pow(dataN[i].DO - K1[j].DO, 2) + pow(dataN[i].Sat - K1[j].Sat, 2) + 
                     pow(dataN[i].pH - K1[j].pH, 2)+ pow(dataN[i].Cond - K1[j].Cond, 2)); 
      
      }
      
      // finding the minimum distance of all the points from the 3 centers
      minimum = dis[i][0];
      min[i] = get_minimum(dis, i, minimum);
      
      //assigning class as 0,1,2 based on the minimum distance between the 3 selected centers
      dataN[i].Class = min[i];   
      data[i].Class = min[i];
   }  
}
   
// *******************************************************************************************************************************************

  /*
   ****************************************************************
   Calling Random function which will declare 1st 3 random values 
   ****************************************************************
   */

void random(struct DataC* dataN, int n, int rd_index[K], struct DataC* K1)
{

   int r_val, u_flag;
   int j, i = 0;
   while(i< K)  
   {
      do 
      {
         u_flag = 1;
         r_val = rand() % n;
         for (j = 0; j < i && u_flag == 1; j++) 
         {
            if (rd_index[j] == r_val) 
            {
               u_flag = 0;
            }
         }
      } while (u_flag != 1);
   
      rd_index[i] = r_val;
      i++;   
   }
   
   for(int i =0; i<K; i++)
   {  
      K1[i].Flow = dataN[rd_index[i]].Flow;
      K1[i].Temp = dataN[rd_index[i]].Temp;
      K1[i].DO   = dataN[rd_index[i]].DO;
      K1[i].Sat  = dataN[rd_index[i]].Sat;
      K1[i].pH   = dataN[rd_index[i]].pH;
      K1[i].Cond = dataN[rd_index[i]].Cond;
      
   }   
}


   
   
// *******************************************************************************************************************************************   
void min(struct DataC *data, int n, float* miF, float* miT, float* miD, float* miS, float* miP, float* miC)
{
   int i;
   for( i=0;i<n;i++)
   {
      if (i==0)
      {   
         *miF=data[i].Flow;
         *miT=data[i].Temp;
         *miD=data[i].DO;
         *miS=data[i].Sat;
         *miP=data[i].pH;
         *miC=data[i].Cond;
      }
      
      else
      {
         if(data[i].Flow < *miF)
         {
            *miF = data[i].Flow;
         }
         
         if(data[i].Temp < *miT)
         {
            *miT = data[i].Temp;
         }
      
         if(data[i].DO < *miD)
         {
            *miD = data[i].DO;
         }
         
         if(data[i].Sat < *miS)
         {
            *miS = data[i].Sat;
         }
      
         if(data[i].pH < *miP)
         {
            *miP = data[i].pH;
         }
         
         if(data[i].Cond < *miC)
         {
            *miC = data[i].Cond;
         }
         
      }   
   }
  
}
   


// *******************************************************************************************************************************************   
void max(struct DataC *data, int n, float* maF, float* maT, float* maD, float* maS, float* maP, float* maC)
{
   
   int i;
   for (i=0; i<n; i++)  
   {
      if (i==0)
      {   
         *maF=data[i].Flow;
         *maT=data[i].Temp;
         *maD=data[i].DO;
         *maS=data[i].Sat;
         *maP=data[i].pH;
         *maC=data[i].Cond;
      }
      
      else
      {
         if (data[i].Flow > *maF)
         {
            *maF=data[i].Flow;
         }
     
         if (data[i].Temp > *maT)
         {
            *maT=data[i].Temp;
         }
     
         if (data[i].DO > *maD)
         {
            *maD= data[i].DO;
         }
     
         if (data[i].Sat > *maS)
         {
            *maS= data[i].Sat;
         }
     
         if (data[i].pH > *maP)
         {
            *maP=data[i].pH;
         }
     
         if (data[i].Cond > *maC)
         {
            *maC=data[i].Cond;
         }
      } 
     
   }
   
}  

// *******************************************************************************************************************************************   

 /*
   **************************************
   Calling normalization function.   
   **************************************
   */

void normalize(struct DataC *data, struct DataC *dataN, int n)
{
   int i;
   float maF, maT, maD, maS, maP, maC = 0.00;
   float miF, miT, miD, miS, miP, miC = 0.00;
      
   min(data, n, &miF, &miT, &miD, &miS, &miP, &miC);
   max(data, n, &maF, &maT, &maD, &maS, &maP, &maC);
   
   /*
   printf("\n------------Minimum Value value------------\n");
   printf("MinF -> %.2f\nMinT -> %.2f\nMinD -> %.2f\nMinS -> %.2f\nMinP -> %.2f\nMinC -> %.2f\n", miF, miT, miD, miS, miP, miC);
   printf("\n------------Maximum value------------\n");
   printf("MaxF -> %.2f\nMaxT -> %.2f\nMaxD -> %.2f\nMaxS -> %.2f\nMaxP -> %.2f\nMaxC -> %.2f\n", maF, maT, maD, maS, maP, maC);
   */
   
   for(i =0;i<n;i++)
   {
      dataN[i].Flow = (data[i].Flow - miF)/(maF - miF);
      dataN[i].Temp = (data[i].Temp - miT)/(maT - miT);
      dataN[i].DO   = (data[i].DO - miD)/(maD - miD);
      dataN[i].Sat  = (data[i].Sat - miS)/(maS - miS);
      dataN[i].pH   = (data[i].pH - miP)/(maP - miP);
      dataN[i].Cond = (data[i].Cond - miC)/(maC - miC);
   }
   
}

// *******************************************************************************************************************************************