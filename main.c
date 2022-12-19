#include<stdio.h>

int crossWordValid(char arr[]);

int main(){
    //declaring variables
    char crossWord[256] = {[0 ... 255] = 0};
    char words[256] = {[0 ... 255] = 0};
    int hashtagCounter=0;
    int letterCounter=0;
    int index=0;

    //Input of the crossword pattern
    while(1){
        scanf("%c", &crossWord[index]);
        if(index>0){
            if(crossWord[index] == '\n' && crossWord[index-1] == '\n'){
                break;
            }
        }
        if(crossWord[index]=='#'){
            hashtagCounter++;
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
        if(words[index]!='\n'){
            letterCounter++;
        }
        index++;
    }

    //printf("%d\n", letterCounter);


    return 0;
}

int crossWordValid(char arr[]){
    int index=0;

    while(arr[index] != '\0'){
        if(arr[index] != '#' && arr[index] != '*' && arr[index] != '\n'){
            return 1;
        }
        index++;
    }
    return 0;
}
