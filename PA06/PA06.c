#include <stdio.h>
#include <math.h>
#include <string.h>

#define FILE_NUM 6
#define ALPHABET_SIZE 27

void countGrams(FILE *file, char *alphabet, float arr[][ALPHABET_SIZE]) {
    char prev,current;
    int x=-1,y=-1,match;
    if (fscanf(file,"%c",&prev)==1){   
        while (fscanf(file,"%c",&current)==1){
            match=1;
            for (int i = 0; i <27; i++)
            {   
                if(prev==alphabet[i])
                    x=i;
                if(current==alphabet[i])
                    y=i;
                if(prev=='\n')
                    x=26;
                if(current=='\n')
                    y=26;
                if ((prev == ' ' || prev == '\n') && (current == ' ' || current == '\n'))
                    match = 0;
            }
            if (match)
                arr[x][y]+=1;
            prev = current;
        }
    }
}

void total(float arr[][ALPHABET_SIZE],float *total){
    for (int i = 0; i < ALPHABET_SIZE; i++){
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            (*total)+=arr[i][j];
        } 
    }
}
void calculateFrequencies(float arr[][ALPHABET_SIZE]){
    float fTotal=0;
    total(arr,&fTotal);
    for (int i = 0; i < ALPHABET_SIZE; i++){
        for (int j = 0; j < ALPHABET_SIZE; j++)
            arr[i][j]=arr[i][j]/fTotal;  
    }    
}
void calculateDissimilarity(float arr1[][ALPHABET_SIZE],float arr2[][ALPHABET_SIZE]){
    float fRatio,sRatio;
    float dissimilarity=0;
    for (int i = 0; i < ALPHABET_SIZE; i++){

        for (int j = 0; j < ALPHABET_SIZE; j++){   
            fRatio=arr1[i][j];
            sRatio=arr2[i][j];
            dissimilarity+=fabs(fRatio-sRatio);
        }  
    }
    printf("%.6lf \n",dissimilarity);
}

int main() {

    float langArr[ALPHABET_SIZE][ALPHABET_SIZE]= {{0}};
    float langArrX[ALPHABET_SIZE][ALPHABET_SIZE]= {{0}};
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz ";
    FILE *languageFiles[FILE_NUM] = {
        fopen("language_x.txt", "r"),
        fopen("language_1.txt", "r"),
        fopen("language_2.txt", "r"),
        fopen("language_3.txt", "r"),
        fopen("language_4.txt", "r"),
        fopen("language_5.txt", "r") 
    };
    countGrams(languageFiles[0],alphabet,langArrX);
    calculateFrequencies(langArrX);
    fclose(languageFiles[0]);
    for (int i = 1; i < FILE_NUM; ++i) {
        countGrams(languageFiles[i], alphabet,langArr);
        calculateFrequencies(langArr);
        calculateDissimilarity(langArrX,langArr);
        memset(langArr, 0, sizeof(langArr));
        fclose(languageFiles[i]);
    }
    return 0;
}