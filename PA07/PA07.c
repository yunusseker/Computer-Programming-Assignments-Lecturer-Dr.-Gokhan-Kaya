#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define gate types
#define INPUT 1
#define OUTPUT 2
#define AND 3
#define OR 4
#define NOT 5
#define FLIPFLOP 6

// Define the gate structure
struct gate {
    int type;
    char name[20];
    struct gate* inp1;
    struct gate* inp2;
    int output;
    int former_out; // only for flipflop
    int flag;
};

//Function to count gates
int countGates();

//Helper Free Function
void freeTree(struct gate* root);

// Function to read the circuit description from circuit.txt
void readCircuitFile(struct gate** gates, int numGates,int* inputNum);

// Function to evaluate the gate and its inputs recursively
int evaluate(struct gate* g);

// Function to read input values from input.txt and evaluate the circuit
void evaluateCircuit(struct gate* gates, int numGates,int inputNum);

// Function to free allocated memory for gates
void freeMemory(struct gate* gates);

int main() {
    struct gate* gates = NULL;
    int numGates = 0;
    int inputNum = 0;
    numGates=countGates();

    // Read the circuit description from circuit.txt
    readCircuitFile(&gates, numGates,&inputNum);

    // Evaluate the circuit based on input values from input.txt
    evaluateCircuit(gates, numGates,inputNum);

    // Free allocated memory
    freeMemory(gates);
    
    return 0;
}


int countGates(){

    FILE* circuitFile = fopen("circuit.txt", "r");
    int numGates=0 ;
    char line[100]; 
    while (fgets(line, sizeof(line), circuitFile) != NULL) {
        char* token = strtok(line, " \n");
        if (strcmp(token, "GATE") == 0) {
            (numGates)++;
        } 
    }
    return numGates;
}



void readCircuitFile(struct gate** gates, int numGates,int* inputNum) {
    FILE* circuitFile = fopen("circuit.txt", "r");
   
    fseek(circuitFile, 0, SEEK_SET);
    *gates = (struct gate*)malloc(numGates * sizeof(struct gate));

    // Read the file line by line
    char line[60]; // adjust the size as needed
    int j=0;
    while (fgets(line, sizeof(line), circuitFile) != NULL) {
        char* token = strtok(line, " \n");// split the line into tokens
        if (strcmp(token, "GATE") == 0) {
            // Allocate memory for a new gate
            struct gate* newGate = (struct gate*)malloc(sizeof(struct gate));
            // Read gate type and name
            token = strtok(NULL, " \n");
            if (strcmp(token, "INPUT") == 0) {
                newGate->type = INPUT;
                (*inputNum)++;
            } else if (strcmp(token, "OUTPUT") == 0) {
                newGate->type = OUTPUT;
            } else if (strcmp(token, "AND") == 0) {
                newGate->type = AND;
            } else if (strcmp(token, "OR") == 0) {
                newGate->type = OR;
            } else if (strcmp(token, "NOT") == 0) {
                newGate->type = NOT;
            } else if (strcmp(token, "FLIPFLOP") == 0) {
                newGate->type = FLIPFLOP;
            }

            token = strtok(NULL, " \n");
            strcpy(newGate->name, token);

            // Initialize other fields
            newGate->inp1 = NULL;
            newGate->inp2 = NULL;
            newGate->output = 0;
            newGate->former_out = 0;
            newGate->flag=0;

            // Add the new gate to the array
            (*gates)[j] = *newGate;
            free(newGate); // free the temporary gate structure
            j++;
            
        } else if (strcmp(token, "CONNECTION") == 0) {
            // Read the connection and link the gates
            token = strtok(NULL, " \n");
            char* fromGate = token;

            token = strtok(NULL, " \n");
            char* toGate = token;

            // Find the gates with the given names
            struct gate* from = NULL;
            struct gate* to = NULL;
            for (int i = 0; i < j; i++) {
                if (strcmp((*gates)[i].name, fromGate) == 0) {
                    from = &((*gates)[i]);
                } else if (strcmp((*gates)[i].name, toGate) == 0) {
                    to = &((*gates)[i]);
                }
            }

            // Connect the gates
            if (from != NULL && to != NULL) {
                if (to->inp1 == NULL) {
                    to->inp1 = from;
                } else {
                    to->inp2 = from;
                }
            }
        }
    }

    fclose(circuitFile);
}

int evaluate(struct gate* g) {
    if (g->type == INPUT) {
        return g->output;
    } else if (g->type == FLIPFLOP) {
        if (g->flag == 0 )
        {
            int input = evaluate(g->inp1);
            g->output = (g->former_out == input) ? 0 : 1;
            g->former_out = g->output;
            g->flag = 1; 
        }
        return g->output;

    } else {
        int inp1 = evaluate(g->inp1);
        int inp2 = (g->inp2 != NULL) ? evaluate(g->inp2) : 0;

        if (g->type == AND) {
            return inp1 && inp2;
        } else if (g->type == OR) {
            return inp1 || inp2;
        } else if (g->type == NOT) {
            return !inp1;
        } else if (g->type == OUTPUT) {
            return inp1;
        }
    }

    printf("Error: Unknown gate type %d for gate %s\n", g->type, g->name);
    exit(EXIT_FAILURE);
}

void evaluateCircuit(struct gate* gates, int numGates,int inputNum) {
    
    FILE* inputFile = fopen("input.txt", "r");
    char* line = (char*)malloc((inputNum+1) * sizeof(char));// allocating memory for input
    // Read the input values line by line 

    while (fgets(line, sizeof(line), inputFile) != NULL) {
        // Remove newline character from the end of the line
        line[strcspn(line, "\n")] = '\0';
        // Assign input values to INPUT gates
        int j=0;
        for (int i = 0; i <numGates; i++) {
            if (gates[i].type == INPUT) {
                gates[i].output = line[j] - '0';
                j++;
            }
            
        }

        // Evaluate the circuit for each OUTPUT gate
        int outputResult = 0;
        for (int i = 0; i < numGates; i++) { 
            if (gates[i].type == OUTPUT) {
                outputResult = evaluate(&gates[i]);  
            }
        }

        // Print the final output result
        printf("%d\n", outputResult);

        for (int i = 0; i < numGates; i++)
        {
            gates[i].flag=0; 
        }

    }
    free(line);
    fclose(inputFile);
}

void freeMemory(struct gate* gates) {
    
    free(gates);

}
