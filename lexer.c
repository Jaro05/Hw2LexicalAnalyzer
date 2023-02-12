#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "lexer_output.h"
#include <ctype.h>

struct lexer{
    char* filename;
    FILE* filepointer;
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
    


    //Read in first char
    char ch = getc(lexer.filepointer);
    strncat(t.text, &ch, 1);

    if(isalpha(ch)){
        //Keep reading in more char until there are no more
        do{
            ch = fgetc(lexer.filepointer);
            if(!isalnum(ch)){
                //if this is not a letter or digit, put it back on the input.
                fputc(ch, lexer.filepointer);
                break;
            }
            strncat(t.text, &ch, 1);
        }while(1);


        

        
    }else if(isdigit(ch)){


    }else{

    }



    t.typ = constsym;
    t.filename = lexer.filename;
    t.line = 1;
    t.column = 1;
    t.value = 0;

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
    if (!lexer_done())
    {
        return lexer_next().line;
    }
}

// Requires: !lexer_done()
// Return the column number of the next token
unsigned int lexer_column(){
    if (!lexer_done)
    {
        return lexer_next().column;
    }
}


int main(int argc, char *argv[]){
    lexer.filename = argv[1];

    //Open the lexer
    lexer_open(lexer.filename);

    //Call lexer_output to start printing tokens
    lexer_output();

    //Call lexer_close
    lexer_close();
}