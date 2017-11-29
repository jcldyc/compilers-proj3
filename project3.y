%{
#include <stdlib.h>
#include "tree.h"

extern tree root;
%}
 
%union {int i; tree t; char *string;}

 
%start program
%token <i> Ident 1 IntConst 2 RealConst 3
%token Var 11 Int 12 Real 13 Boolean 14
%token Record 21 While 22 Do 23 End 24 Begin 25 Loop 26 Exit 27
%token Bind 31 To 32 Assert 33
%token When 41 If 42 Then 43 Elsif 44 Else 45 Put 46
%token Or 51 And 52 Not 53 NotEqual 54 Div 55 Mod 56
%token Colon 61 Definition 62
%token LessThan 63 GreaterThan 64 LessThanEq 65 GreaterThanEq 66
%token Dot 67 Comma 68
%token Assign 71 Plus 72 Minus 73 Star 74 Slash 75 Semicolon 76 LPar 77 RPar 78
%token Prog 81 NoType 82 Field 83
 

%type <t> pStateDeclSeq idlist type field_list state_decls declaration statement ref end_if expr and_expr not_expr rel_expr sum prod factor basic


%%
 





program:		pStateDeclSeq
					{ root = buildTree (Prog, $1, NULL, NULL); }

pStateDeclSeq: 	
					{$$ = NULL;}
				| statement Semicolon pStateDeclSeq
					{$$ = $1; $$->next = $3;}
				| Var idlist Colon type Semicolon pStateDeclSeq
					{$$ = buildTree(Var, $2, $4, NULL); $$->next = $6;}
				;



idlist: 		Ident 
					{$$ = buildIntTree(Ident, $1);}
				| Ident Comma idlist
					{$$ = buildIntTree(Ident, $1); $$->next = $3;}
				;

type: 			Int
					{$$ = buildTree(Int, NULL, NULL, NULL);}
				| Real
					{$$ = buildTree(Real, NULL, NULL, NULL);}
				| Boolean
					{$$ = buildTree(Boolean, NULL, NULL, NULL);}
				| Record field_list End Record
					{$$ = buildTree(Record, $2, NULL, NULL);}
				;

field_list: 	idlist Colon type
					{$$ = buildTree(Field, $1, $3, NULL);}
				| idlist Colon type Semicolon field_list
					{$$ = buildTree(Field, $1, $3, $5);}
				;

state_decls: 
					{$$ = NULL;}
				| statement Semicolon state_decls
					{$$ = $1; $$->next = $3;}
				| declaration Semicolon state_decls
					{$$ = $1; $$->next = $3;}
				;

declaration: 	Var idlist Colon type
					{$$ = buildTree(Var, $2, $4, NULL);}
				| Bind idlist To ref
					{$$ = buildTree(Bind, $2, $4, NULL);}
				| Bind Var idlist To ref
					{$$ = buildTree(Bind, buildTree(Var, $3, NULL, NULL), $5, NULL);}
				;

statement: 	 	ref Definition expr
					{$$ = buildTree(Definition, $1, $3, NULL);}
				| Assert expr
					{$$ = buildTree(Assert, $2, NULL, NULL);}
				| Begin state_decls End
					{$$ = buildTree(Begin, $2, NULL, NULL);}
				| Loop state_decls End Loop
					{$$ = buildTree(Loop, $2, NULL, NULL);}
				| Exit 
					{$$ = buildTree(Exit, NULL, NULL, NULL);}
				| Exit When expr
					{$$ = buildTree(Exit, buildTree(When, $3, NULL, NULL), NULL, NULL);}
				| If expr Then state_decls end_if
					{$$ = buildTree(If, $2, buildTree(Then, $4, NULL, NULL), $5);}
				;

ref: 			Ident
					{$$ = buildIntTree(Ident, $1);}
				| Ident Dot Ident
					{$$ = buildTree(Dot, buildIntTree(Ident, $1), buildIntTree(Ident, $3), NULL);}
				;

end_if: 		End If
					{$$ = NULL;}
				| Else state_decls end_if
					{$$ = buildTree(Else, $2, $3, NULL);}
				| Elsif expr Then state_decls end_if
					{$$ = buildTree(Elsif, $2, buildTree(Then, $4, NULL, NULL), $5);}
				;

expr: 			expr Or and_expr
					{$$ = buildTree(Or, $1, $3, NULL);} 
				| and_expr
					{$$ = $1;}
				;

and_expr: 		and_expr And not_expr 
					{$$ = buildTree(And, $1, $3, NULL);}
				| not_expr
					{$$ = $1;}
				;

not_expr: 		Not not_expr 
					{$$ = buildTree(Not, $2, NULL, NULL);}
				| rel_expr
					{$$ = $1;}
				;

rel_expr: 		sum 
					{$$ = $1;}
				| rel_expr Assign sum 
					{$$ = buildTree(Assign, $1 ,$3, NULL);}
				| rel_expr NotEqual sum
					{$$ = buildTree(NotEqual, $1 ,$3, NULL);}
				| rel_expr LessThan sum 
					{$$ = buildTree(LessThan, $1 ,$3, NULL);}
				| rel_expr LessThanEq sum
					{$$ = buildTree(LessThanEq, $1 ,$3, NULL);}
				| rel_expr GreaterThan sum 
					{$$ = buildTree(GreaterThan, $1 ,$3, NULL);}
				| rel_expr GreaterThanEq sum
					{$$ = buildTree(GreaterThanEq, $1 ,$3, NULL);}
				;

sum: 			prod 
					{$$ = $1;}
				| sum Plus prod 
					{$$ = buildTree(Plus, $1 ,$3, NULL);}
				| sum Minus prod
					{$$ = buildTree(Minus, $1 ,$3, NULL);}
				;

prod: 			factor 
					{$$ = $1;}
				| prod Star factor 
					{$$ = buildTree(Star, $1 ,$3, NULL);}
				| prod Slash factor
					{$$ = buildTree(Slash, $1 ,$3, NULL);}
				| prod Div factor
					{$$ = buildTree(Div, $1 ,$3, NULL);} 
				| prod Mod factor
					{$$ = buildTree(Mod, $1 ,$3, NULL);}
				;

factor: 		Plus basic 
					{$$ = buildTree(Plus, $2, NULL, NULL);}
				| Minus basic 
					{$$ = buildTree(Minus, $2, NULL, NULL);}
				| basic
					{$$ = $1;}
				;

basic: 			ref 
					{$$ = $1;}
				| LPar expr RPar 
					{$$ = $2;}
				| IntConst
					{$$ = buildIntTree(IntConst, $1);}
				| RealConst
					{$$ = buildIntTree(RealConst, $1);}
				;



 
%%