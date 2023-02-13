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


// Requires: !lexer_done()
// Return the next token in the input file,
// advancing in the input
token lexer_next(){
    token t;
    t.text[0] = '\0';


    //Read in first char
    char ch = fgetc(lexer.filepointer);
    lexer.column++;

    //If the char is a space or a newline, move on to the next char and update the line/column.
    if(ch == ' '){
        ch = fgetc(lexer.filepointer);
        lexer.column++;
    }else if(ch == '\n'){
        ch = fgetc(lexer.filepointer);
        lexer.line++;
        lexer.column = 1;
    } 
    
    //Set the variables for this token
    t.filename = lexer.filename;
    t.line = lexer.line;
    t.column = lexer.column;
    strncat(t.text, &ch, 1);
    
    //If the character is a letter
    if(isalpha(ch)){
        //Keep reading in more char until there are no more for this word.
        do{
            ch = fgetc(lexer.filepointer);
            lexer.column++;
            if(!isalnum(ch)){
                //If this char is not a letter or digit, put it back on the input.
                ungetc(ch, lexer.filepointer);
                lexer.column--;
                break;
            }
            strncat(t.text, &ch, 1);
        }while(1);

        //Assign the correct type for the token.
        if(strcmp(t.text, "const") == 0){
            t.typ = constsym;
        }else if(strcmp(t.text, "var") == 0){
            t.typ = varsym;
        }else if(strcmp(t.text, "procedure") == 0){
            t.typ = procsym;
        }else if(strcmp(t.text, "call") == 0){
            t.typ = callsym;
        }else if(strcmp(t.text, "begin") == 0){
            t.typ = beginsym;
        }else if(strcmp(t.text, "end") == 0){
            t.typ = endsym;
        }else if(strcmp(t.text, "if") == 0){
            t.typ = ifsym;
        }else if(strcmp(t.text, "then") == 0){
            t.typ = thensym;
        }else if(strcmp(t.text, "else") == 0){
            t.typ = elsesym;
        }else if(strcmp(t.text, "while") == 0){
            t.typ = whilesym;
        }else if(strcmp(t.text, "do") == 0){
            t.typ = dosym;
        }else if(strcmp(t.text, "read") == 0){
            t.typ = readsym;
        }else if(strcmp(t.text, "write") == 0){
            t.typ = writesym;
        }else if(strcmp(t.text, "skip") == 0){
            t.typ = skipsym;
        }else if(strcmp(t.text, "odd") == 0){
            t.typ = oddsym;
        }else{
            t.typ = identsym;
        }

    //SAM do this part of the if else clause, when the character is a digit.
    }else if(isdigit(ch)){
        //read thru the whole number then assign it to token
        do
        {
            ch = fgetc(lexer.filepointer);
            lexer.column++;
            if (!isdigit(ch))
            {
                ungetc(ch, lexer.filepointer);
                lexer.column--;
                break;
            }
            strncat(t.text, &ch, 1);
        } 
        while (1);
        t.typ = numbersym;
        t.value = atoi(ch);
    //JORDAN do this part of the if else clause, when the character is a symbol.
    }else{
        //this is temporary just for compiling reasons.
        t.typ = constsym;
    }

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