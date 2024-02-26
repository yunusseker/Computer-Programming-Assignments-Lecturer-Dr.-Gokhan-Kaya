#include <stdio.h>
#include <stdlib.h>

#define MAX_NGRAMS 100 // Maximum number of 2-grams

int main(){


    // Define arrays to store 2-grams and their counts
    int ngrams1[MAX_NGRAMS];// First element of 2-gram 
    int ngrams2[MAX_NGRAMS];// Second element of 2-gram
    int counts[MAX_NGRAMS];// Count of each 2-gram


    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

  if(inputFile == NULL || outputFile == NULL){
      printf("File open error!\n");
      return 1;
    }

    int prev, current;
    int num2Grams = 0;

    // Read the first integer from the input file and store it in prev
    if (fscanf(inputFile,"%d", &prev) != EOF) {
        while (fscanf(inputFile, "%d", &current) != EOF) { // Continue reading integers from the input file until the end of the file is reached
            int found = 0; // Flag to indicate if the current 2-gram is found in the arrays
            for (int i = 0; i < num2Grams; i++) {// Search for the current 2-gram in the arrays of 2-grams
                if (ngrams1[i] == prev && ngrams2[i] == current) {// Check if the current 2-gram matches the one stored in the arrays
                    counts[i]++;// If found, increment the count for this 2-gram and set found to 1
                    found = 1;
                    break;
                }
            }

            // If the current 2-gram is not found in the arrays add it
            if (!found) {
                if (num2Grams < MAX_NGRAMS) {// Ensure we don't exceed the maximum number of 2-grams (MAX_NGRAMS)
                    ngrams1[num2Grams] = prev;// Store the new 2-gram and set its count to 1
                    ngrams2[num2Grams] = current;
                    counts[num2Grams] = 1;
                    num2Grams++;// Increment the count of unique 2-grams
                }
            }

            prev = current; // Update prev for the next iteration
        }
    }
    
    // Write 2-gram counts to the output file
    for (int i = 0; i < num2Grams; i++) {
        fprintf(outputFile, "%d %d:%d\n", ngrams1[i], ngrams2[i], counts[i]);
    }



    
    // Close files
    fclose(inputFile);
    fclose(outputFile);
    

}