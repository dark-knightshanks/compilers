#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// lexer for minimal operations of pythonn staring with functions , operators , variables and numerical values

enum token {
    tok_eof = -1,
    tok_def = -2,
    tok_return = -3,
  // primary
    tok_identifier = -4,
    tok_number = -5,
};

static string IdentifierStr;
static double NumValue;

static int gettok(){
    static int LastChar = ' ';
    while(isspace(LastChar)) // skip whitespace
        LastChar = getchar();
    if(isalpha(LastChar)){ // checks for alphabets and numbers betwee  0-9 and stores operators just in case for further processing 
        IdentifierStr = LastChar;
        while(isalnum(LastChar = getchar())){
            IdentifierStr += LastChar;
        }
        if(IdentifierStr == "def"){
            return tok_def;
        }
        if(IdentifierStr == "return"){
            return tok_return;
        }
        return tok_identifier;
    }
    if(isdigit(LastChar) || LastChar == '.'){    // checks for floating point numbers hence runs atleats once 
        string NumStr;
        do{
            NumStr += LastChar;
            LastChar = getchar();    
        }while(isdigit(LastChar) || LastChar == '.');
        NumValue = strtod(NumStr.c_str(),0);
        return tok_number;
    }
    if(LastChar == '#'){ // read charcters until we are not on a new line 
        do{
            LastChar = getchar();
        }while(LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF)
        return gettok();
    }
    if(LastChar == EOF){
        return tok_eof;
    }
    int ThisChar = LastChar; // return ascii value of the charcter like opertors
    LastChar = getchar();
    return ThisChar;
}


int main(){
   int tok;
   while((tok = gettok()) != tok_eof){
    cout<<"Token: "<< tok << endl;
   }
}