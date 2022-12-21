#include<stdio.h>

int crossWordValid(char arr[]);
int isLetter(char character);
int wordCounter(char arr[]);
int letterCounter(char words[], int letterCountArr[]);
int hashtagCounter(char crossWord[], int hashtagCountArr[]);

int main(){
    //declaring variables
    char crossWord[256] = {[0 ... 255] = 0};
    char words[256] = {[0 ... 255] = 0};
    int rowCounter=0;
    int index=0;
    int letterCountArr[256];
    int hashtagCountArr[256];

    //Input of the crossword pattern
    while(1){
        scanf("%c", &crossWord[index]);
        if(index>0){
            if(crossWord[index] == '\n' && crossWord[index-1] == '\n'){
                break;
            }
        }
        if(crossWord[index]=='\n'){
            rowCounter++;
        }
        index++;
    }

    //Check whether crossword pattern is valid
    if(crossWordValid(crossWord)){
        printf("Invalid input");
        return 0;
    }

    //Input of the word for crossword
    index=0;
    while(1){
        scanf("%c", &words[index]);
        if(index>0){
            if(words[index] == '\n' && words[index-1] == '\n'){
                break;
            }
        }
        index++;
    }

    //Creating an array to get the number of letters in input words
    letterCounter(words, letterCountArr);

    //Creating an array to get the number of hashtags in crossword pattern
    hashtagCounter(crossWord, hashtagCountArr);


    //--------------------Debugging-----------------------------------------------------------------------
    for(int i=0; i<rowCounter; i++){
        printf(" %d", hashtagCountArr[i]);
    }
    //--------------------Debugging-----------------------------------------------------------------------

    return 0;
}

//Function to check whether crossword pattern is valid
int crossWordValid(char arr[]){
    int index=0;

    while(arr[index] != '\0'){
        if(arr[index] != '#' && arr[index] != '*' && arr[index] != '\n' && !isLetter(arr[index])){
            return 1;
        }
        index++;
    }
    return 0;
}

//Function to check whether input character is a letter
int isLetter(char character){
    if((character>=65 && character<=90) || (character>=97 && character<=122)){
        return 1;
    }
    else{
        return 0;
    }
}

//Function to find words in input
int wordCounter(char arr[]){
    int counter=0;
    int index=0;
    while(arr[index]!=0){
        if(arr[index]=='\n'){
            counter++;
        }
        index++;
    }
    return counter-1;
}

//Function to find letters in a word array
int letterCounter(char words[], int letterCountArr[]){
    int index=0;
    int arrayIndex=0;
    int counter=0;
    while(words[index]!=0){
        if(words[index]=='\n'){
            letterCountArr[arrayIndex]=counter;
            arrayIndex++;
            counter=0;
        }
        else{
            counter++;
        }
        index++;
    }
}

//Function to find letters in a word array
int hashtagCounter(char crossWord[], int hashtagCountArr[]){
    int index=0;
    int arrayIndex=0;
    int counter=0;
    while(crossWord[index]!=0){
        if(crossWord[index]=='\n'){
            hashtagCountArr[arrayIndex]=counter;
            arrayIndex++;
            counter=0;
        }
        else{
            if(crossWord[index]=='#'){
            counter++;
            }
        }
        index++;
    }
}



