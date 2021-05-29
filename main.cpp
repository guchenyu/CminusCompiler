#include<iostream>
#include "global.h"
#include "util.h"
#include"lexical.h"
int  linenum = 0;
int  Error =false;
int  main(void)
{
	TreeNode* syntaxTree;
	lexical_analysize();
	syntaxTree = parse();
	outTree(syntaxTree);
	return 0;
}
