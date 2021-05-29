#pragma once
#include"treenode.h"
void  OutToken(TokenType, const char*);
void  printError(TokenType, const char*);
char* copyString(char*);
TreeNode* newNode(Kind kind);
void  outTree(TreeNode*);
TreeNode* parse(void);
#define MAXTOKENLEN 30
extern   char  tokenString[MAXTOKENLEN + 1];
TokenType getTokens(void);