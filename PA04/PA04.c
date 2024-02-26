#include <stdio.h>
#include <string.h>
#define MAX_LENGTH_ROW 250
#define MAX_NUM_ROW 100
#define MAX_WORD_LENGTH 11

int searchWord(char puzzleWords[MAX_NUM_ROW][MAX_LENGTH_ROW],int rowSize,char *word, int *row, int *col, int *direction);

int main(){

    FILE *input1 = fopen("input1.txt", "r");
    FILE *input2 = fopen("input2.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int rowSize=0;

    char puzzleWords[MAX_NUM_ROW][MAX_LENGTH_ROW];
    char words[MAX_WORD_LENGTH];
    
    while (fscanf(input2,"%s",puzzleWords[rowSize])==1) // taking the puzzle from text to 2d array
        ++rowSize;

    while (fscanf(input1,"%s",words)==1) {// taking the words from input file to 2d words array
        int row, col, direction;  

        if (searchWord(puzzleWords, rowSize, words, &row, &col, &direction)) { // sending puzzle and word to searchWord Fucntion to find is there word or not 
            fprintf(output, "%s (%d,%d) ", words, row, col);

            switch (direction) { // rigthing the postion of word based on direction
                case 1:
                    fprintf(output, "Horizontal\n");
                    break;
                case 2:
                    fprintf(output, "Vertical\n");
                    break;
                case 3:
                    fprintf(output, "Diagonal\n");
                    break;
            }
        }
        
    }   
    return 0;
}

int searchWord(char puzzleWords[MAX_NUM_ROW][MAX_LENGTH_ROW],int rowSize,char *word, int *row, int *col, int *direction){

    int rowcolleng;
    int wordleng=strlen(word); // taking word leng 
    
    for (int i = 0; i < rowSize; i++) // first loop travelling in rows
    {   
        rowcolleng=strlen(puzzleWords[i]);

        for (int j = 0; j < rowcolleng; j++) // second loop traveling in spesfic row's column
        {    
            // Checking Horizontal
            if (rowcolleng>=j+wordleng){  // if there is no enough chrahcter at that area there will be no word so there is no need to check 
                int match=1; // if there is the match value will be true
                for (int k = 0; k < wordleng; k++){// then we have to look if the chrahter is matching or not
                    if (puzzleWords[i][j+k] != word[k]) 
                    {   match = 0;
                        break;
                    }   
                }
                if (match)
                {
                    *row= i + 1;
                    *col= j + 1;
                    *direction=1; // horizontal
                    return 1;
                }    
            }           
            // Checking Vertical
            if (rowSize >= i + wordleng)
            {   int match = 1;
                for (int k = 0; k < wordleng; k++){   
                    if (puzzleWords[i+k][j] != word[k])
                    {   match = 0;
                        break;
                    }   
                } 
                if (match)
                {
                    *row= i + 1;
                    *col= j + 1;
                    *direction=2; // Vertical
                    return 1;
                } 
            }
            if(rowSize >= i + wordleng && rowcolleng>=j+wordleng){
                int match =1;
                for (int k = 0; k < wordleng; k++){   
                    if (puzzleWords[i+k][j+k] != word[k])
                    {   match = 0;
                        break;
                    }   
                }
                if (match)
                {
                    *row= i + 1;
                    *col= j + 1;
                    *direction=3; // Vertical
                    return 1;
                }
            }    
        }
    }
    return 0;
}