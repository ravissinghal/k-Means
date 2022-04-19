# include "func.h"

int main()
{

   int i = 0;
   int j;
   int c[K];
   int n_data = 0;
   struct DataC data[MAX_ROW];
   struct DataC dataN[MAX_ROW];
   struct DataC K1[K];
   struct DataC K2[K];
   int rd_index[K];
   float dis[MAX_ROW][K];
   int min[MAX_ROW];
   
   
   /*
   ****************************************************************************************
   The below code helps us to read the data from the file which is cleaned using R/Python.   
   ****************************************************************************************
   */
   
   FILE* fp;
   char *buf = malloc(MAX_LEN);
   
   //Reading a file
   if ( ( fp = fopen( "Book5.csv", "r" ) ) == NULL ) 
   {
      printf( "File could not be opened.\n" );
   }
   
   // Read header so that i dont have to store them in struct
   printf("%s",fgets(buf,MAX_LEN,fp));  
     
   
   while (fgets(buf, MAX_LEN, fp) != NULL)
   {
      if ((strlen(buf)>0) && (buf[strlen(buf)] == '\n'))
         buf[strlen(buf)] = '\0';  
      
      char *tmp = strtok(buf, ",");
      strcpy(data[i].Date,tmp);
            
      tmp = strtok(NULL, ",");
      data[i].S_id = atof(tmp);
      
      tmp = strtok(NULL, ",");
      strcpy(data[i].S_name,tmp);
      
      tmp = strtok(NULL, ",");
      data[i].Flow = atof(tmp);
      
      tmp = strtok(NULL, ",");
      data[i].Temp = atof(tmp);
      
      tmp = strtok(NULL, ",");
      data[i].DO = atof(tmp);
      
      tmp = strtok(NULL, ",");
      data[i].Sat = atof(tmp);
      
      tmp = strtok(NULL, ",");
      data[i].pH = atof(tmp);
      
      tmp = strtok(NULL, ",");
      data[i].Cond = atof(tmp);
      
      i++;
      
   }

   n_data = i;

   fclose(fp);
   
   /*
   
   for(i=0;i<n_data;i++)
   {  
      printf("%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",data[i].Flow, data[i].Temp, data[i].DO, data[i].Sat, data[i].pH, data[i].Cond);
   }
   
  */
   
   normalize(data, dataN, n_data);
   
   
   
   printf("\n------------Normalized value------------\n");
   for(i=0;i<n_data;i++)
   {  
      printf("%.2f  %.2f  %.2f  %.2f  %.2f  %.2f\n",dataN[i].Flow, dataN[i].Temp, dataN[i].DO, dataN[i].Sat, dataN[i].pH, dataN[i].Cond);
   }
   printf("\n----------------------------------------\n");
   
 
   
   random(dataN, n_data, rd_index, K1);
   
   
   printf("\n------------Random centers index value ------------\n");
   for(i=0; i<K; i++)
   {  
      printf("%d\n", rd_index[i]);
   }
   printf("\n----------------------------------------\n");
   
   
   printf("\n------------Random centers------------\n");
   for(i=0; i<K; i++)
   {  
      printf("%.2f  %.2f  %.2f  %.2f  %.2f  %.2f\n",K1[i].Flow, K1[i].Temp, K1[i].DO, K1[i].Sat, K1[i].pH, K1[i].Cond);
   }
   printf("\n----------------------------------------\n");
   
   
   for(j=0;j<100;j++)
   {
  
   
   euclidean(data, dataN, K1, dis, n_data, min);
   
   /*
   printf("\n------------Euclidean calculated ------------\n\n");
   printf("C-1\tC-2\tC-3\n");
   for(i=0;i<n_data;i++)
   {  
      for(j=0;j <K;j++)
      {
         printf("%.2f\t",dis[i][j]);
         
      }
      printf("\n");
   }
   printf("\n----------------------------------------\n");
   
   printf("\n------------Minmum ------------\n\n");
   for(i=0;i<n_data;i++)
   {  
      printf("%d\n",min[i]);
   }
   printf("\n----------------------------------------\n");
   
   printf("\n------------Original dataset with Class assigned ------------\n");
   for(i=0;i<n_data;i++)
   {  
      printf("%.2f  %.2f  %.2f  %.2f  %.2f  %.2f  %d\n",data[i].Flow, data[i].Temp, data[i].DO, data[i].Sat, data[i].pH, data[i].Cond, data[i].Class);
   }
   printf("\n----------------------------------------\n");
   
   
   printf("\n------------Normalized value with Class assigned ------------\n");
   for(i=0;i<n_data;i++)
   {  
      printf("%.2f  %.2f  %.2f  %.2f  %.2f  %.2f  %d\n",dataN[i].Flow, dataN[i].Temp, dataN[i].DO, dataN[i].Sat, dataN[i].pH, dataN[i].Cond, dataN[i].Class);
   }
   printf("\n----------------------------------------\n");
   
   
   
   */
   calcualate_centers(c, n_data, dataN);
   
   /*
   printf("\n------------Normalized value with Class assigned ------------\n");
   for(i=0;i<K;i++)
   {
      printf("%d\n",c[i]);
   }
   printf("\n----------------------------------------\n");
   
   */
   
   
   mean(dataN, K2, n_data, c);
   
   printf("\n------------Random centers - K2------------\n");
   for(i=0; i<K; i++)
   {  
      printf("%.2f  %.2f  %.2f  %.2f  %.2f  %.2f\n",K2[i].Flow, K2[i].Temp, K2[i].DO, K2[i].Sat, K2[i].pH, K2[i].Cond);
   }
   printf("\n----------------------------------------\n");
   
  
   
   assign_mean(K1,K2);
   
   printf("\n------------K1 centers------------\n");
   for(i=0; i<K; i++)
   {  
      printf("%.2f  %.2f  %.2f  %.2f  %.2f  %.2f\n",K1[i].Flow, K1[i].Temp, K1[i].DO, K1[i].Sat, K1[i].pH, K1[i].Cond);
   }
   printf("\n----------------------------------------\n");
   
   }
   
   /*
   int count = 0;
   while(check_equal(K1,K2))
   {
         if(count<3)
         {
         printf("Hello");
         euclidean(data, dataN, K1, dis, n_data, min);
         calcualate_centers(c, n_data, dataN);
         mean(dataN, K2, n_data, c);
         printf("Bye");
         count ++;
         }
      break;
   }
   */
   
   write_csv(str,dataN,n_data, data); 
   
   return 0;

}
