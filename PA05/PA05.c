#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARB_CAL_1G 4 /* Number of calories in 1g carbohydrate */
#define PROTEIN_CAL_1G 4 /* Number of calories in 1g protein */
#define FAT_CAL_1G 9 /* Number of calories in 1g fat */
#define WATER_CAL_1G 0 /* Number of calories in 1g water */
#define MAX_ITEMS 20
#define MAX_ITEM_LENGTH 30

struct macroNutrients{   
    double a;
    double b;
    double c;
    double d;
    double e;
};

struct percp{
    double p;
    double c;
    double f;
};

void nutrition(char *nutr,struct macroNutrients* ca);
void parseItems(char items[MAX_ITEMS][MAX_ITEM_LENGTH],char input[MAX_ITEM_LENGTH*MAX_ITEMS],int *itemNum);
int isbase(char * nutr);
void editName(char *name);
double getAmount(char* name);

int main(){
    char meal[MAX_ITEM_LENGTH];
    printf("> What is the meal?\n");
    scanf("%s", meal);
    // Allocate memory for the struct macroNutrients
    struct macroNutrients *ca = malloc(sizeof(struct macroNutrients));
    // Initialize the struct members to zero
    memset(ca, 0, sizeof(struct macroNutrients));
    nutrition(meal, ca);
    ca->a=ca->c+ca->d+ca->e;
    ca->c=(ca->c*100)/ca->a;
    ca->d=(ca->d*100)/ca->a;
    ca->e=(ca->e*100)/ca->a;
    printf("Total calories is %.2lf in %.2lfg Hamburger. %.2lf%% calories from carbs, %.2lf%% from proteins, %.2lf%% from fats.", ca->a,ca->b,ca->c,ca->d,ca->e);
    // Free allocated memory
    free(ca);
}

void nutrition(char *nutr, struct macroNutrients* ca){

    int itemNum=1;
    
    if(isbase(nutr)){
        struct percp p;
        double value= getAmount(nutr);
        editName(nutr);
        fflush(stdin);
        printf(">> List the amount macro nutrients in %s\n",nutr);
        scanf("%lf%lf%lf", &p.c, &p.p, &p.f);
        ca->b+=value;
        ca->c+=(((p.c)/100)*value)*CARB_CAL_1G;
        ca->d+=(((p.p)/100)*value)*PROTEIN_CAL_1G;
        ca->e+=(((p.f)/100)*value)*FAT_CAL_1G;
        return;
    }
    printf("> What is a %s\n",nutr);
    char word[MAX_ITEM_LENGTH*MAX_ITEMS];
    char items[MAX_ITEMS][MAX_ITEM_LENGTH];
    parseItems(items,word,&itemNum);
    struct macroNutrients *temp=ca;
    for (int i = 0; i < itemNum; i++)
    {
        nutrition(items[i],temp);
    }  
}

int isbase(char * nutr){
    int i=strlen(nutr);
    if(nutr[i-1]==')') // controlling the word is base or not with the help of last index of word
        return 1;     
    else
        return 0; 
}

void editName(char *name){
    int i=0;
    while (name[i]!='(') // when pointer see ( charahter it loop will stop and that value will be \0
        ++i;
    name[i]='\0';    
}


double getAmount(char* name){
    int i=1;
    while (name[0]!='('){ // search the array when see the there is no ( increment the pointer then pointer will point next value untill see the (
        name+=1;
        ++i;    
    }
    name++;
    double value=atoi(name); // with atoi fucntion we will take the string to integer
    while(i!=0){
        name-=1; // this time decrement the pointer for point the name again
        i--;
    }
    return value;
}

void parseItems(char items[][MAX_ITEM_LENGTH],char input[MAX_ITEM_LENGTH*MAX_ITEMS],int *itemNum){
    int itemCount = 0;
    fflush(stdin);
    fgets(input, MAX_ITEM_LENGTH*MAX_ITEMS, stdin);
    if (input[strlen(input) - 1] == '\n') {// Remove trailing newline from fgets
        input[strlen(input) - 1] = '\0';
    }
    char *token = strtok(input, ",");  // Tokenize the input based on commas
    while (token != NULL && itemCount <= MAX_ITEMS) {
        while (*token == ' ' || *token == '\t') { // Remove leading whitespaces from the token
            token++;
        }
        strncpy(items[itemCount], token, MAX_ITEM_LENGTH - 1);// Copy the token to the items array
        items[itemCount][MAX_ITEM_LENGTH - 1] = '\0'; // Ensure null-termination
        itemCount++;
        // Get the next token
        token = strtok(NULL, ",");
    }
    *itemNum=itemCount;
}