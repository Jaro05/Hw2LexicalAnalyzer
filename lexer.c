#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "lexer_output.h"
#include <ctype.h>

struct lexer{
    char* filename;
    FILE* filepointer;
    int column;
    int line;
}lexer;
struct lexer;

// Requires: fname != NULL
// Requires: fname is the name of a readable file
// Initialize the lexer and start it reading
// from the given file name
void lexer_open(const char *fname){
    lexer.filepointer = fopen(fname, "r");
}

// Close the file the lexer is working on
// and make this lexer be done
void lexer_close(){
    fclose(lexer.filepointer);
}

// Is the lexer's token stream finished
// (either at EOF or not open)?
bool lexer_done(){
    if(feof(lexer.filepointer) || (lexer.filepointer == NULL)){
        return(true);
    }else{
        return(false);
    }
}



//important reading info by Jacob
// fgets gets up to a newline
// fscanf gets up to blank space
// fgetc gets a character



// Requires: !lexer_done()
// Return the next token in the input file,
// advancing in the input
token lexer_next(){
    token t;
    t.text[0] = '\0';


    //Read in first char
    char ch = fgetc(lexer.filepointer);
    lexer.column++;

    if(ch == ' '){
        //if it is a space move on to the next one.
        ch = fgetc(lexer.filepointer);
        lexer.column++;
    }else if(ch == '\n'){
        ch = fgetc(lexer.filepointer);
        lexer.line++;
        lexer.column = 1;
    } 

    
    t.filename = lexer.filename;
    t.line = lexer.line;
    t.column = lexer.column;
    strncat(t.text, &ch, 1);

    
    if(isalpha(ch)){
        //Keep reading in more char until there are no more
        do{
            ch = fgetc(lexer.filepointer);
            lexer.column++;
            if(!isalnum(ch)){
                //if this is not a letter or digit, put it back on the input.
                ungetc(ch, lexer.filepointer);
                lexer.column--;
                break;
            }
            strncat(t.text, &ch, 1);
        }while(1);

        
    }else if(isdigit(ch)){


    }else{

    }


    t.typ = constsym;


    return(t);
}

// Requires: !lexer_done()
// Return the name of the current file
const char *lexer_filename(){
    return(lexer.filename);
}

// Requires: !lexer_done()
// Return the line number of the next token
unsigned int lexer_line(){
    return(lexer.line);
}

// Requires: !lexer_done()
// Return the column number of the next token
unsigned int lexer_column(){
    return(lexer.column);
}


int main(int argc, char *argv[]){
    lexer.filename = argv[1];
    lexer.column = 0;
    lexer.line = 1;

    //Open the lexer
    lexer_open(lexer.filename);

    //Call lexer_output to start printing tokens
    lexer_output();

    //Call lexer_close
    lexer_close();
}