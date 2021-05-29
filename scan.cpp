#include<string>
#include<algorithm> 
#include<iostream>
#include<cstring>
#include<fstream>
#include"global.h"
#include "util.h"
using namespace std;
#define BUFFERSIZE 256
typedef   enum
{
    START,
    INCOMPARE, 
    INCOMMENT2,
    INOPERATE,
    INNUM,
    INCOMMENT, 
    INID,
    DONE,
    INCHAR,
    INSTRING,
    INNUM2
}  StateType;
char  tokenString[MAXTOKENLEN + 1];

TokenType doubleOp;
int  quote;
int  line = 0;
int  bufsize = 0;
bool  EOF_flag = false;
string  lineBuffer;  
ifstream filein(INPUTFILE);
static  char  getNextChar(void)
{
    if (line == 0)
        cout << "<-------------------------------The Source Code is below------------------------------->" << endl<<endl;
    if (!(line < bufsize)||lineBuffer.empty())
    {
        linenum++;
        if (getline(filein,lineBuffer))
        {
            cout<< linenum<<"\t"<<lineBuffer<<endl;
            bufsize = lineBuffer.length();
            line = 0;
            return lineBuffer[line++];
        }
        else
        {
            EOF_flag = true;
            return EOF;
        }
    }
    else
    {
        return lineBuffer[line++];
    }
}

static struct
{
    char* str;
    TokenType tok;
} 
reservedWords[6]=
{
    {"else",ELSE},
    {"if",IF}, 
    {"int",INT},
    {"return",RETURN},
    {"void",VOID},
    {"while", WHILE}
};
static void ungetNextChar(void)
{
    if (!EOF_flag)
    {
        line--;
    }
}
static TokenType reservedLookup(string s)
{
    int i;
    for (i = 0; i < 6; i++)
        if (!s.compare(reservedWords[i].str))
            return reservedWords[i].tok;
    return ID;
}
TokenType getTokens(void)
{

    int tokenStringIndex = 0;
    TokenType currentToken;
    StateType state = START;
    bool isSave;
    while (state != DONE)
    {
        char c = getNextChar();
        isSave =true;
        switch (state)
        {
        case START:
            if (isdigit(c))
            {
                state = INNUM;
            }
            else if (isalpha(c) || c == '_')
            {
                state = INID;
            }
            else if (c == '>' || c == '<' || c == '!' || c == '=')
            {
                state = INCOMPARE;
                switch (c)
                {
                case '<':
                    doubleOp = LT;
                    break;
                case '>':
                    doubleOp = GT;
                    break;
                case '=':
                    doubleOp = EQ;
                    break;
                case '!':
                    doubleOp = NEQ;
                    break;
                }
            }
            else if (c == '+' || c == '-' || c == '*')
            {
                state = INOPERATE;
                if (c == '+')
                {
                    doubleOp = PLUS;
                }
                if (c == '-')
                {
                    doubleOp = MINUS;
                }
                if (c == '*')
                {
                    doubleOp = TIMES;
                }
               
            }
            else if (c == 34 || c == 39) /* ÒýºÅ */
            {
                isSave = false;
                if (c == 34)
                {
                    state = INSTRING;
                    quote = 34;
                }
                if (c == 39)
                {
                    state = INCHAR;
                    quote = 39;
                }
            }
            else if ((c == ' ') || (c == '\t') || (c == '\n'))
            {
                isSave = false;
            }
            else if (c == '/')
            {
                c = getNextChar();
                if (c == '*')
                {
                    isSave = false;
                    state = INCOMMENT;
                }
                else
                {
                    ungetNextChar();
                    state = DONE;
                    currentToken = OVER;
                }
            }
            else
            {
                state = DONE;
                switch (c)
                {
                case EOF:
                    isSave = false;
                    currentToken = ENDFILE;
                    break;
                case '(':
                    currentToken = LPAREN;
                    break;
                case ')':
                    currentToken = RPAREN;
                    break;
                case ';':
                    currentToken = SEMI;
                    break;
                case ':':
                    currentToken = COLON;
                    break;
                case ',':
                    currentToken = COMMA;
                    break;
                case '[':
                    currentToken = LBRACKET;
                    break;
                case ']':
                    currentToken = RBRACKET;
                    break;
                case '{':
                    currentToken = LCBRACKET;
                    break;
                case '}':
                    currentToken = RCBRACKET;
                    break;
                default:
                    currentToken = ERROR;
                    break;
                }
            }
            break;
        case INCOMMENT:
            isSave = false;
            switch (c)
            {
            case '*':
                state = INCOMMENT2;
                break;
            default:
                state = INCOMMENT;
                break;
            }
            break;
            break;
        case INCOMMENT2:
            isSave = false;
            switch (c)
            {
            case '*':
                state = INCOMMENT2;
                break;
            case '/':
                state = START;
                break;
            default:
                state = INCOMMENT;
                break;
            }
            break;
        case INCOMPARE:
            state = DONE;
            if (c == '=')
            {
                if (doubleOp == LT)
                {
                    currentToken = LEQ;
                }
                if (doubleOp == GT)
                {
                    currentToken = GEQ;
                }
                if (doubleOp == EQ)
                {
                    currentToken = EQ;
                }
                if (doubleOp == NEQ)
                {
                    currentToken = NEQ;
                }
            }
            else
            {

                ungetNextChar();
                isSave = false;
                currentToken = ASSIGN;
            }
            break;
        case INOPERATE:
            state = DONE;
            if (c == '=')
            {
                if (doubleOp == PLUS)
                {
                    currentToken = PLUSASSIGN;
                }
                if (doubleOp == MINUS)
                {
                    currentToken = MINUSASSIGN;
                }
                if (doubleOp == TIMES)
                {
                    currentToken = TIMESASSIGN;
                }
            }
            else if (doubleOp == PLUS && c == '+')
            {
                currentToken = SELFPLUS;
            }
            else if (doubleOp == MINUS && c == '-')
            {
                currentToken = SELFPLUS;
            }
            else
            {
                ungetNextChar();
                isSave = false;
                currentToken = doubleOp;
            }
            break;
        case INCHAR:
            switch (c)
            {
            case EOF:
                state = DONE;
                currentToken = ENDFILE;
                break;
            case 39:
                if (quote == 39)
                {
                    isSave = false;
                    state = DONE;
                    currentToken = CHARACTER;
                }
                break;
            }
            break;
        case INSTRING:
            switch (c)
            {
            case EOF:
                state = DONE;
                currentToken = ENDFILE;
                break;
            case 34:
                if (quote == 34)
                {
                    isSave = false;
                    state = DONE;
                    currentToken = STRING;
                }
                break;
            }
            break;
        case INNUM:
            if (!isdigit(c) && c != '.')
            {
                /* backup in the input */
                ungetNextChar();
                isSave = false;
                state = DONE;
                currentToken = NUM;
            }
            if (c == '.')
            {
                state = INNUM2;
                currentToken = NUM;
            }
            break;
        case INNUM2:
            if (!isdigit(c))
            {
                /* backup in the input */
                ungetNextChar();
                isSave = false;
                state = DONE;
                currentToken = NUM;
            }
            break;
        case INID:
            if (!(isalpha(c) || isdigit(c) || c == '_'))
            {
                /* backup in the input */
                ungetNextChar();
                isSave = false;
                state = DONE;
                currentToken = ID;
            }
            break;
        case DONE:
        default: /* should never happen */
            cout<< "Scanner Bug: state= "<< state<<endl;
            state = DONE;
            currentToken = ERROR;
            break;
        }
        if ((isSave) && (tokenStringIndex <= MAXTOKENLEN))
        {
            tokenString[tokenStringIndex++] = (char)c;
        }
        if (state == DONE)
        {
            tokenString[tokenStringIndex] = '\0';
            if (currentToken == ID)
            {
                currentToken = reservedLookup(tokenString);
            }
        }
    }
    return currentToken;
}
