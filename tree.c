#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "y.tab.h"

tree buildTree (int kind, tree one, tree two, tree three)
{
	tree p = (tree)malloc(sizeof (node));
	p->kind = kind;
	p->first = one;
	p->second = two;
	p->third = three;
	p->next = NULL;
	return p;
}

tree buildIntTree (int kind, int val)
{
	tree p = (tree)malloc(sizeof (node));
	p->kind = kind;
	p->value = val;
	p->first = p->second = p->third = NULL;
	p->next = NULL;
	return p;
}

char TokName[][13] = 
	{"", 
	"Ident", "IntConst", "RealConst", "", "", "", "", "", "", "",
	"Var", "Int", "Real", "Boolean", "", "", "", "", "", "",
	"Record", "While", "Do", "End", "Begin", "Loop", "Exit", "", "", "",
	"Bind", "To", "Assert", "", "", "", "", "", "", "",
	"When", "If", "Then", "Elsif", "Else", "Put", "", "", "", ""
	"Or", "And", "Not", "NotEqual", "Div", "Mod", "", "", "", "",
	"Colon", "Definition", "LessThan", "GreaterThan", "LessThanEq", "GreaterThanEq", "Dot", "Comma", "", "",
	"Assign", "Plus", "Minus", "Star", "Slash", "Semicolon", "LPar", "RPar", "", "",
	"Prog", "NoType", "Field"};

static int indent = 0;
void printTree (tree p)
{
	if (p == NULL) return;
	for (; p != NULL; p = p->next) {
		printf ("%*s%s\n", indent, "", TokName[p->kind]);
		switch (p->kind) {
			case Ident: 
				//printf ("Ident:  %s\n", p->value);
				break;
			case IntConst:
				//printf ("IntConst: %d\n", p->value);
				break;
			case RealConst:
				//printf("RealConst: %d\n", p->value);
			default:
				printf ("\n");
				indent += 2;
				printTree (p->first);
				printTree (p->second);
				printTree (p->third);
				indent -= 2;
			}
		}
}
