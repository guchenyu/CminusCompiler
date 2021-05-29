#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
using namespace std;
#define INPUTFILE "t4.txt"
typedef   enum

{
    ENDFILE, ERROR,
//else 、 if 、 int 、 return 、 void 、 while
    ELSE,IF,INT,RETURN,VOID,WHILE,
   
//num 、 id
    ID, NUM, CHARACTER, STRING,
// + 、 - 、 * 、 / 、 ++ 、 -- 、 += 、 -= 、 *= 、 < 、 <= 、 > 、 >= 、 == 、 != 、 = 、 ; 、 , 、 ( 、 ) 、 [ 、 ] 、 { 、 } 、 /* 、 */ 、 :
    PLUS, MINUS, TIMES, OVER, SELFPLUS, SELFMINUS, PLUSASSIGN, MINUSASSIGN, TIMESASSIGN, LT, LEQ, GT, GEQ, EQ, NEQ, ASSIGN, SEMI, COMMA, LPAREN,
    RPAREN, LBRACKET, RBRACKET, LCBRACKET, RCBRACKET, LCOMMENT, RCOMMENT, COLON
}  TokenType;
extern   int  linenum;
/**********************************************************/
typedef   enum {
    IntK, IdK, VoidK, ConstK, Var_DeclK, Arry_DeclK, FunK, ParamsK,
    ParamK, CompK, Selection_StmtK, Selection_StmtK1, Iteration_StmtK, Return_StmtK, AssignK, OpK,
    Arry_ElemK, CallK, ArgsK, UnkownK
} Kind;
typedef enum { Void, Integer } ExpType;
extern int Error;



