#include<stdlib.h>
#include<stdio.h>
#include<string.h>
double** transpose(double **matrix, int i, int j){
    double **newMatrix = malloc(j*sizeof(double*));
  //  printf("J is: %d, and I is %d\n", j, i);

    for(int k = 0; k<j; k++){
        
        newMatrix[k] = malloc(i * sizeof(double)); 
        
    }
    for(int rows = 0; rows<j; rows++){
        for(int col = 0; col<i; col++){
                

            newMatrix[rows][col] = matrix[col][rows];
        }
    }
    return newMatrix;
}
double* THEWEIGHT(double**matrix,double* y, int n, int m){
    double * array = malloc(n*sizeof(double));
    //    printf("n is %d\n",n);
   //     printf("m is %d\n",m);


    for(int i = 0; i<n; i++){
            

        double sum = 0;
        for(int c = 0; c<m; c++){
     //       printf(" + %lf * %lf ", matrix[i][c],y[c]);
            sum = sum+ matrix[i][c]*y[c];
        }
       // printf("\n");
        array[i] = sum;
        
    } 
    return array;

}

double** multiplication(double**matrix1, double**matrix2, int i1, int j1, int i2, int j2){
    //matrix 1 is the transposed matrix and matrix 2 is the regular X
    //matrix1's dimensions are n,m and matrix 2 is m,n. (matrix has n many rows, and m many colomns.)
    //i1 == j2 and j1 = i2 foe the x^t * x
   // printf("ARE WE GETTING HERE?");
 //  printf("This is i1: %d, this is j1: %d, This is i2: %d and this is j2: %d\n", i1,j1,i2,j2);
   double**matrix = malloc(i1*sizeof(double *));
    for(int x = 0; x<i1; x++){
        matrix[x] = (double*)malloc(j2*sizeof(double));
    }

    for(int y = 0; y<i1; y++){
        for(int z = 0; z<j2; z++){
            double sum = 0;
            for(int c = 0; c<i2; c++){
                sum = sum+ matrix1[y][c] * matrix2[c][z];
            }
            matrix[y][z] = sum;
        }
    } 

    return matrix;
}

double**invert(double** M, int n){
    //this is a square matrix, so we have to malloc a double 2d array of size d*d
    
    double **N = (double **)malloc(n*sizeof(*N));
    for(int x = 0; x<n; x++){
        N[x] = malloc(n*sizeof(double));
    }
    for(int x = 0; x<n; x++){
        for (int y = 0; y < n; y++) {
            if (x == y ) N[x][y] = 1;
            else N[x][y] = 0;
        } 
    }
    
    //for p ←0, 1, ··· , n −1 do
    for(int p = 0; p<n; p++){
        //f ←Mp,p
        double f = M[p][p];
        //divide Mp by f
        for(int x = 0; x<n; x++){
            N[p][x] = N[p][x]/f;
        }
        //divide Np by f
        for(int x = 0; x<n; x++){
            M[p][x] = M[p][x]/f;
        }
        
       // N[p][p] = N[p][p]/f;
        for(int i = p+1; i<n; i++){
            // f = Mi,p
            f = M[i][p];
            //subtract Mp x f from Mi
            for(int x = 0; x<n; x++){
                M[i][x] = M[i][x]-(M[p][x]*f);
            }
            //subtract Np x f from Ni
            for(int x = 0; x<n; x++){
                N[i][x] = N[i][x]-(N[p][x]*f);
            }

        }
    }
    for(int p = n-1; p>=0; p--){
        for(int i = p-1; i>=0; i--){
            double f = M[i][p];
            for(int x = 0; x<n; x++){
                M[i][x] = M[i][x]-(M[p][x]*f);
            }
            //subtract Np x f from Ni
            for(int x = 0; x<n; x++){
                N[i][x] = N[i][x]-(N[p][x]*f);
            }
        }
    }
    return N;

}
int main(int argc, char** argv){
    
    FILE *train;
    double** X=NULL;
    //freed X, and weight
    double *weight=NULL;
    int n;
    int m;
   
    train = fopen(argv[1], "r");
        char* type=malloc(6*sizeof(char));
        fscanf(train, "%s", type);
      //  printf("%s\n", type);
       if(strcmp("train", type) == 0){
            
          //  printf("Are you getting here?\n");

            fscanf(train,"%d", &n);
            fscanf(train,"%d", &m);
            n++;

              //         printf("M is : %d \n N is equal to: %d \n", m,n);

            weight = malloc(m*sizeof(double));
            X = malloc(m*sizeof(double *));

            for(int i = 0; i<m; i++){
                X[i] = malloc(n*sizeof(double));
            }
            for(int x = 0; x<m; x++){
                X[x][0] = 1;
            }
            for(int x = 0; x<m; x++){
                for(int y = 1; y<n; y++){
                    fscanf(train, "%lf", &X[x][y]);
                }
                fscanf(train,"%lf", &weight[x]);
            }
            for(int j = 0; j<m; j++){
                for(int k = 0; k<n; k++){
        //            printf("%lf ", X[j][k]);
                }
         //       printf("\n");
            }

            for(int j = 0; j<m; j++){
       //        printf("%lf \n", weight[j]);

            }
                       //printf("M is : %d \n N is equal to: %d \n", m,n);

        }
    fclose(train);
   // printf("Are tiy egtting here 2\n");
         //  printf("M is : %d \n N is equal to: %d \n", m,n);

   double **transposedX = transpose(X, m,n);
//freeTransposedX with n
    double **multi1 = multiplication(transposedX,X,n,m,m,n);
    //free multi1 with n

    double **inverse = invert(multi1,n);


       // printf("Are tiy egtting here 2\n");
    //    printf("M is : %d \n N is equal to: %d \n", m,n);
  //  printf("Hardcoded at [1] [0] %lf\n", multi1[1][1]);
   double **multi2 = multiplication(inverse,transposedX,n,n,n,m);

 //   printf("(XtX)^-1Xt");
   for(int x = 0; x<n; x++){
        for(int y = 0; y<m; y++){
 //           printf("%lf ", multi2[x][y]);
        }
  //      printf("\n");
   }

   for(int x = 0; x<m; x++){
   // printf("%lf\n", weight[x]);
   }
   double *W = THEWEIGHT(multi2,weight,n,m);
   for(int x = 0; x<n; x++){
  //      printf("fella %lf \n", W[x]);
   }
   FILE*data;
   data = fopen(argv[2],"r");
   
   char*name = malloc(5*sizeof(char));
   fscanf(data,"%s",name);
   
   if(strcmp(name,"data")==0){
       //printf("%s",name);

        int row;
        int col;
        fscanf(data, "%d", &col);
        fscanf(data, "%d", &row);
        for(int x = 0; x<row; x++){
            double sum = W[0];
          //  printf("%lf ",W[0]);
            //printf("This is the bias %lf\n",W[0]);
            for(int y = 1; y<col+1; y++){
          //      printf("this is the nimber of rows %d\n", row);
                double L;
           //     printf("This is y: %d\n", y);
                fscanf(data, "%lf", &L);
             //   printf("L is %lf\n", L);
              //  printf(" + %lf * %lf ", W[y],L);
                sum = sum+ (W[y] * L);
            }
            printf("%.0f\n",sum);
        }
    }
    fclose(data);
    
    for(int i = 0; i<m; i++){
        free(X[i]);
    }
    free(X);
    free(weight);
    for(int i = 0; i<n; i++){
        free(transposedX[i]);
    }
    free(transposedX);

    for(int i = 0; i<n; i++){
        free(multi1[i]);
    }
    free(multi1);
    for(int i = 0; i<n; i++){
        free(inverse[i]);
    }
    free(inverse);
    for(int i = 0; i<n; i++){
        free(multi2[i]);
    }
    free(multi2);
    free(W);
    //free(data);
    free(name);
    free(type);

    




}
    