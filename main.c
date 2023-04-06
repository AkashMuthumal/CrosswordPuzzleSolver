/**
 * E/19/453 Withanaarachchi W.A.A.M.T
 * E/19/431 Wickramaarachchi I.W.A.P.D.
 * 
 * 
 * **/

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50
#define MAX_GRID_ROWS 100
#define MAX_GRID_COLS 100
#define CORD 2
#define ARRAY_SIZE 256

char grid[MAX_GRID_ROWS][MAX_GRID_COLS];
int *grid_rows, *grid_cols;
char words[MAX_WORDS][MAX_WORD_LENGTH];
int *pos;
int *word_count;
int *wordAvailable;

void printGrid();
void gridBuild(char arr[]);
int gridValid();
int isLetter(char character);
void wordBuild(char arr[]);
int find();
int find1();
int validRow(int wordNo, int x, int y);
int solve();
int validCol(int wordNo, int x, int y);

int main(){
    int index=0;

    char *cross_word = (char*)malloc(sizeof(char)*ARRAY_SIZE);

    grid_rows = (int*)malloc(sizeof(int));
    *grid_rows = 0;

    grid_cols = (int*)malloc(sizeof(int));
    *grid_cols = 0;

    while(1){
        scanf("%c", &cross_word[index]);
        if(index>0){
            if(cross_word[index] == '\n' && cross_word[index-1] == '\n'){
                break;
            }
        }
        if(cross_word[index]=='\n'){
            if(*grid_cols==0){
                *grid_cols=index;
            }
            *grid_rows = *grid_rows + 1;
        }
        index++;
    }

    gridBuild(cross_word);

    free(cross_word);
    char *sub_words = (char*)malloc(sizeof(char)*ARRAY_SIZE);
    

    if(gridValid()){
        printf("INVALID INPUT\n");
        return 0;
    }

    index=0;
    while(1){
        scanf("%c", &sub_words[index]);
        if(sub_words[index] == '\n' && sub_words[index-1] == '\n'){
            break;
        }
        index++;
    }
    wordBuild(sub_words);
    free(sub_words);

    solve();
    
    for(int i=0; i<*word_count; i++){
        if(wordAvailable[i]){
            printf("IMPOSSIBLE\n");
            free(wordAvailable);
            free(word_count);
            free(pos);
            free(grid_rows);
            free(grid_cols);
            return 0;
        }
    }

    printGrid();

    free(wordAvailable);
    free(word_count);
    free(pos);
    free(grid_rows);
    free(grid_cols);

    return 0;

}

//Function to print the grid
void printGrid(){
    for(int i=0; i<*grid_rows; i++){
        for(int j=0; j<*grid_cols; j++){
            printf("%c", grid[i][j]);
        }
        putchar('\n');
    }
}

//function to build the grid for 2D array usin input 1D array
void gridBuild(char arr[]){
    int index=0;
    for(int i=0; i<*grid_rows; i++){
        for(int j=0; j<*grid_cols; j++){
            if(arr[index]=='\n'){
                index++;
            }
            grid[i][j] = arr[index];
            index++;
        }
    }
}

//function to build the word 2D array usin input word 1D array
void wordBuild(char arr[]){
    int index=0;
    int row_index=0;
    int col_index=0;
    wordAvailable = (int*)malloc(sizeof(int)*MAX_WORDS);

    word_count = (int*)malloc(sizeof(int));
    *word_count = 0;

    while(arr[index]!=0){

        if(arr[index]=='\n'){
            row_index++;
            col_index=0;
            index++;
            *word_count = *word_count + 1;
            wordAvailable[*word_count-1] = 1;
        }
        
        words[row_index][col_index] = arr[index];

        col_index++;
        index++;
    }
    
}

//Function to check whether input crossword pattern is valid
//Valid characters are # * newline and any letter
int gridValid(){
    for(int i=0; i<*grid_rows; i++){
        for(int j=0; j<*grid_cols; j++){
            if(grid[i][j] != '#' && grid[i][j] != '*' && grid[i][j] != '\n' && !isLetter(grid[i][j])){
                return 1;
            }
        }
    }
    return 0;
}

//Function to check whether a character is a letter
int isLetter(char character){
    if((character>=65 && character<=90) || (character>=97 && character<=122)){ //A-Z or a-z or #
        return 1;
    }
    else{
        return 0;
    }
}

//Save the position in grid that has # character
int find(){
    for(int i=0; i<*grid_rows; i++){
        for(int j=0; j<*grid_cols; j++){
            if(grid[i][j]=='#'){
                pos[0] = j;
                pos[1] = i;
                return 0;
            }
            
        }
    }
    return 1;
}

//Save the position of in grid that has any letter
int find1(){
    for(int i=0; i<*grid_rows; i++){
        for(int j=0; j<*grid_cols; j++){
            for(int k=0; k<*word_count; k++){
                if(!wordAvailable[k]){
                    continue;
                }
                if(isLetter(grid[i][j])){
                    if(words[k][0]==grid[i][j] && grid[i][j+1]=='#'){
                        pos[0] = j;
                        pos[1] = i;
                        return 0;
                    }
                    if(words[k][0]==grid[i+1][j] && grid[i][j]=='#'){
                        pos[0] = j;
                        pos[1] = i;
                        return 0;
                    }
                    
                }
            }
        }
    }
    return 1;
}

//Check validity of word that can be inserted for rows
int validRow(int wordNo, int x, int y){
    int NoOfHash=0;
    for(int i=x; i<*grid_cols; i++){
        if(isLetter(grid[y][i])){
            for(int j=0; j<*word_count; j++){
                if(!wordAvailable[j]){
                    continue;
                }
                if(grid[y][i] == words[j][i-x]){
                    NoOfHash++;
                    break;
                }
                else{
                    return 0;
                }
            }
        }
        else if(grid[y][i]==35){
            NoOfHash++;
        }
        else{
            break;
        }
    }
    //if the space is equel with size of word returns 0
    if(NoOfHash==(int) strlen(words[wordNo])){
        return 1;
    }
    else{
        return 0;
    }
}

//Check validity of word that can be inserted for columns
int validCol(int wordNo, int x, int y){
    int NoOfHash=0;
    for(int i=y; i<*grid_rows; i++){
        if(isLetter(grid[i][x])){
            
            for(int j=0; j<*word_count; j++){
                    if(!wordAvailable[j]){
                        continue;
                    }
                    if(grid[i][x] == words[j][i-y]){
                        NoOfHash++;
                        break;
                    }
                    else{
                        return 0;
                    }
                }
        }
        else if(grid[i][x]==35){
            NoOfHash++;
        }
        else{
            break;
        }
    }
    //if the space is equel with size of word returns 0
    if(NoOfHash==(int)strlen(words[wordNo])){
        return 1;
    }
    else{
        return 0;
    }

}

//This is the main function that solves the crossword puzzle
//This is a recursive function with backtrack
int solve(){

    pos = (int*)malloc(sizeof(int)*CORD);
    //Get the index of a position in grid that can insert a word
    if(find1()){
        find();
    }

    int x=pos[0];
    int y=pos[1];
    int count=0;

    //Check whether all the words are inserted
    for(int i=0; i<*word_count; i++){
        if(!wordAvailable[i]){
            count++;;
        }
        if(count==*word_count){
            return 1;
        }
    }
    
    for(int i=0; i<*word_count; i++){
        if(!wordAvailable[i]){
            continue;
        }

        if(validRow(i, x, y)){

            for(int j=0; j<(int)strlen(words[i]); j++){
                grid[y][x+j]=words[i][j];
            }

            wordAvailable[i]=0;

            if(solve()){
                return 1;
            }

            wordAvailable[i]=1;

            for(int j=0; j<(int)strlen(words[i]); j++){
                grid[y][x+j]='#';
            }
            
        }
        if(validCol(i, x, y)){
            for(int j=0; j<(int)strlen(words[i]); j++){
                grid[y+j][x]=words[i][j];
            } 

            wordAvailable[i]=0;
            

            if(solve()){
                return 1;
            }

            wordAvailable[i]=1;

            for(int j=0; j<(int)strlen(words[i]); j++){
                grid[y+j][x]='#';
            }
            
        } 
    }
    return 0;
}