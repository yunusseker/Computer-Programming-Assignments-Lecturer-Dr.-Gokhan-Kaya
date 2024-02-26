#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_POLY_LENGTH 1000
#define MAX_VALUES 100

int countDigits(double number);

int main(){

    FILE *valuesFile = fopen("values.txt", "r");
    FILE *fp = fopen("polynomials.txt", "r");
    FILE *evaluationsFile = fopen("evaluations.txt", "w");

    if (valuesFile == NULL || fp == NULL || evaluationsFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    char valuesLine[MAX_POLY_LENGTH];
    double values[MAX_VALUES];
    char polynomial[MAX_POLY_LENGTH];
    int counter=0; 
    double coefficient; 
    int exponent;
    char* term;
    int numValues = 0;


    // Read values from values.txt
    if (fgets(valuesLine, sizeof(valuesLine), valuesFile) != NULL) {
       
        char *token = strtok(valuesLine, " ");

        while(token!=NULL){
            sscanf(token, "%lf", &values[numValues]);
            numValues++;
            token = strtok(NULL, " ");
        }                 
    }

    int exArr[1000];
    int coArr[1000];

     // Process each polynomial from polynomials.txt
    while(fgets(polynomial, sizeof(polynomial), fp) != NULL){ 
        term=polynomial; 
        counter=0;
        while(*term != '\0' && *term != '\n'){
            if (sscanf(term, "%lfx^%d", &coefficient, &exponent) == 2) {
                term+=countDigits(coefficient)+4;  
                exArr[counter]=exponent;
                coArr[counter]=coefficient;
                counter++;
            }

            else if (sscanf(term, "%lfx", &coefficient) == 1) {
               
                term+=countDigits(coefficient)+1;
                exArr[counter]=exponent;
                coArr[counter]=coefficient;
                counter++;    
            }

            else if(sscanf(term, "+x^%d", &exponent) == 1){
                coefficient=1; 
                exArr[counter]=exponent;
                coArr[counter]=coefficient;
                counter++;
                term+=2;   
            }
            
            else if(sscanf(term, "-x^%d", &exponent) == 1){
                coefficient=-1;
                exArr[counter]=exponent;
                coArr[counter]=coefficient;
                counter++;
                term+=4;
            }

            else if(sscanf(term, "x^%d", &exponent) == 1){     
                coefficient=1;
                exArr[counter]=exponent;
                coArr[counter]=coefficient;
                counter++;
                term+=4;    
            }

            else{   
                coefficient=1;
                exArr[counter]=exponent;
                coArr[counter]=coefficient;
                counter++;
                term++;   
            }
        }

        double val;// Evaluate the polynomial for each value
        for (int i = 0; i <numValues; i++)
        {  for (int j = 0; j < counter; j++){
                val+=pow(values[i],exArr[j])*coArr[j];
            }
            
            fprintf(evaluationsFile, "%.2f ", val);
            val=0;
        }
        fprintf(evaluationsFile, "\n");
        
        term ++;
      
    }

    fclose(valuesFile);
    fclose(fp);
    fclose(evaluationsFile);

    return 0;
}



int countDigits(double number) {
    char buffer[15];  
    int numDigits;

    // Convert the double to a string
    sprintf(buffer, "%f", number);

    // Calculate the length of the string
    numDigits = 1;
    for (int i = 0; buffer[i] != '\0' && buffer[i] != '0'; i++) {
        if (buffer[i] >= '0' && buffer[i] <= '9') {
            numDigits++;
        }
    }

    return numDigits;
}