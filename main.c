#include<stdio.h>

int crossWordValid(char arr[]);
int isLetter(char character);
int wordCounter(char arr[]);
int letterCounter(char words[], int letterCountArr[]);
int hashtagCounter(char crossWord[], int hashtagCountArr[]);
int rowChecker(int rowCounter, char words[], int hashtagCountArr[], int letterCountArr[], int wordOrder[]);
void rowWriter(char crossWord[], char words[], int wordStartingIndex[], int wordOrder[]);
void arrayPrint(char arr[]);
int rowPossible(int rowCounter,char words[],int hashtagCountArr[],int letterCountArr[], int wordOrder[]);
void wordIndexing(int wordStartingIndex[],char words[]);


int main(){
    //declaring variables
    char crossWord[256] = {[0 ... 255] = 0};
    char words[256] = {[0 ... 255] = 0};
    int rowCounter=0;
    int index=0;
    int letterCountArr[256];
    int hashtagCountArr[256];
    int wordStartingIndex[256] = {[0 ... 255] = 0};
    int wordOrder[256] = {[0 ... 255] = 0};

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

    //Creating an array with starting index of words
    wordIndexing(wordStartingIndex, words);

    //--------------------Debugging-----------------------------------------------------------------------
    if(rowPossible(rowCounter, words, hashtagCountArr, letterCountArr, wordOrder)){
        rowWriter(crossWord, words, wordStartingIndex, wordOrder);
        arrayPrint(crossWord);
    }
    else{
        printf("Impossible");
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

//Function to get the count of how many words can be fit in crossword map
int rowChecker(int rowCounter, char words[], int hashtagCountArr[], int letterCountArr[], int wordOrder[]){
    int counter=0;
    int index=0;
    for(int i=0; i<rowCounter; i++){
        for(int j=0; j<wordCounter(words); j++){
            if(letterCountArr[j]==hashtagCountArr[i]){
                wordOrder[index]=j;
                letterCountArr[j]=0;
                counter++;
                index++;
                break;
            }
        }
    }
    return counter;
}

//Function to write words to crossword pattern
void rowWriter(char crossWord[], char words[], int wordStartingIndex[], int wordOrder[]){
    int index1=0;
    int index2=wordStartingIndex[wordOrder[0]];
    int index3=1;

    while(crossWord[index1]!='\0'){
        if(crossWord[index1]=='#' && words[index2]!='\n'){
            crossWord[index1]=words[index2];
            index2++;
        }
        else if(words[index2]=='\n'){
            index2=wordStartingIndex[wordOrder[index3]];
            index3++;
        }
        index1++;
    }
}

//Print array such as crossword
void arrayPrint(char arr[]){
    int index=0;
    while(arr[index]!='\0'){
        printf("%c", arr[index]);
        index++;
    }
}

//Function to check whether words can be added into rows
int rowPossible(int rowCounter,char words[],int hashtagCountArr[],int letterCountArr[], int wordOrder[]){
    if(rowChecker(rowCounter, words, hashtagCountArr, letterCountArr, wordOrder)==wordCounter(words)){
        return 1;
    }
    else{
        return 0;
    }
}

//Function to make array containing the starting index of words
void wordIndexing(int wordStartingIndex[],char words[]){
    int index1=0;
    int index2=0;
    while(words[index1]!='\0'){
        if(words[index1]=='\n'){
            wordStartingIndex[index2+1]=index1+1;
            index2++;
        }
        index1++;
    }

}
