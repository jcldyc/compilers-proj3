%{
	#include <stdio.h>
	#include "y.tab.h"

	int line_no = 1;

	int yyerror (char *s);

	typedef union {
		int value;
		int i;
		char *string;	/* to store variable names */
	} YYSTYPE;
	extern YYSTYPE yylval;

%}

L	[A-Za-z]
D	[0-9]

%%
[ \t]+ ; /* skip white space */
[\n] line_no++; /* count lines */
while { return While; }
do { return Do; }




 



var {return Var;}
int {return Int;}
real {return Real;}
boolean {return Boolean;}
record {return Record;}
end {return End;}
bind {return Bind;}
to {return To;}
assert {return Assert;}
begin {return Begin;}
loop {return Loop;}
exit {return Exit;}
when {return When;}
if {return If;}
then {return Then;}
elsif {return Elsif;}
else {return Else;}
put {return Put;}
or {return Or;}
and {return And;}
not {return Not;}
not"=" {return NotEqual;}
div {return Div;}
mod {return Mod;}


":" {return Colon;}
":=" {return Definition;}
"<" {return LessThan;}
">" {return GreaterThan;}
">=" {return GreaterThanEq;}
"<=" {return LessThanEq;}
"." {return Dot;}
"," {return Comma;}




{L}({L}|{D}|_)* {yylval.string = strdup(yytext);
				yylval.i = lookup(yytext);
				return Ident;}
{D}+ {yylval.value = atoi(yytext);
	return IntConst;}
[0-9]+(\.[0-9]+)?(([Ee](\+|\-)[0-9])?) {yylval.string = strdup(yytext);
										return RealConst;}

"=" { return Assign; }
"+" { return Plus; }
"-" { return Minus; }
"*" { return Star; }
"/" { return Slash; }
";" { return Semicolon; }
"(" { return LPar; }
")" { return RPar; }
. { yyerror ("Unrecognized Character"); }

%%

int yywrap (void) {return 1;}
int yyerror (char *s)
{
	fprintf (stderr, "%s in line %d, token %s\n", s, line_no, yytext);
}

typedef char name[15];
static char Names[200][15] = {"<no name>"};
int top = 0;


//lookup the 
int lookup (char s[]){
	printf("looking up %s\n",s);
	int	i;
	//loop through and see if it already exists
	for (i = 1; i <= top; i ++){
		if (strcmp (s, Names[i]) == 0){
			return i;
		}
	}
	//if it does not exist add to Names and return top
	strcpy (Names[++top], s);
	return top;
}

void printNames (void)
{
	int i = 0;

	for (; i <= top; i++)
		printf ("%d\t%s\n", i, Names[i]);
}

char *id_name (int i)
{
	return Names[i];
}




