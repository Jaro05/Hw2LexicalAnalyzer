#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "lexer_output.h"

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
    return(false);
}

// Requires: !lexer_done()
// Return the next token in the input file,
// advancing in the input
token lexer_next(){
    token t;
    char buff[255];
    fgets(buff, 255, lexer.filepointer);
    printf("%s", buff);

    t.text = buff;
    t.typ = varsym;

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

}

// Requires: !lexer_done()
// Return the column number of the next token
unsigned int lexer_column(){

}


int main(int argc, char *argv[]){
    lexer.filename = argv[1];

    lexer_open(lexer.filename);

    //Call lexer_output to start printing tokens
    lexer_output();

    //Call lexer_close

}