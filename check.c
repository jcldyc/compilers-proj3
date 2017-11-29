#include <stdio.h>
#include "tree.h"
#include "y.tab.h"
#include "ST.h"

extern int top;
STentry st[100] = {0, 0, 0, 0}; 

void prST (void)
{
	int i;
	printf ("SYMBOL TABLE\n");
	for (i = 0; i <= top; i++) {
		int	t = st[i].kind;
		printf ("%3d %-10s\t%s\n", i, id_name (i), 
			t == Int ? "Int" : t == Boolean ? "Boolean" : "<none>");
	}
}

void buildST(tree t)
{	
	int location = 0;			// localization in sym table
	int scope = 0;				// scope level
	if (t == NULL){
		return;
	}		
	if(scope < 0){	
		printf("Scope somehow negative???\n");	
		return;
	}
	for (; t != NULL; t = t->next){
		switch (t->kind){
			// case Declare:
			// { 
			// 	scope = scope + 1;
			// 	break;
			// }
			case End:
			{ 
				printf("case end\n");
				scope = scope - 1;
				break;
			}
			// case For: 
			// {
			// 	scope = scope + 1;
			// 	break;	
			// }
			case Ident: 
			printf("case Ident\n");
			st[location].name = id_name(t->value);
			st[location].index = location;
			st[location].kind = t->kind;
			st[location].scope = scope;
			st[location].value = t->second->value;
			break;
			case IntConst:
			printf("case IntConst\n");
			st[location].name = id_name(t->value);
			st[location].index = location;
			st[location].kind = t->kind;
			st[location].scope = scope;
			st[location].value = t->second->value;
			break;
			default:
			{
				printf("default hit in buildST\n");
				st[location].name = id_name(t->value);
				st[location].index = location;
				st[location].kind = t->kind;
				st[location].scope = scope;
				st[location].value = t->value;
				printf("Name: %s index: %d kind: %d scope: %d value: %d\n", st[location].name, st[location].index, st[location].kind, st[location].scope, st[location].value);
				//printf("st[location].value: %d\n", st[location].value);
				break;
			}
		}
	}
	location = top;
}

static int check_expr (tree t){
	if (t == NULL) { 
		fprintf (stderr, "You shouldn't be here; missing expression\n"); 
		return NoType; 
	}
	switch (t->kind) {
		case Assign: 

		break;

		case NotEqual : 
			{int t1 = check_expr(t->first), t2 = check_expr(t->second);
						if (t1 != t2) {
							fprintf (stderr, "Type mismatch in  != comparison\n");
							return (t->value = NoType);
						}
						else {
							return (t->value = Boolean);
						}}
		break;

		case LessThan : 
			{int t1 = check_expr(t->first), t2 = check_expr(t->second);
						if (t1 != t2) {
							fprintf (stderr, "Type mismatch in LE comparison\n");
							return (t->value = NoType);
						}
						else {
							return (t->value = Boolean);
						}}
		break;

		case LessThanEq :
			{int t1 = check_expr(t->first), t2 = check_expr(t->second);
						if (t1 != t2) {
							fprintf (stderr, "Type mismatch in LT comparison\n");
							return (t->value = NoType);
						}
						else {
							return (t->value = Boolean);
						}}
		break;

		case GreaterThan : 
			{int t1 = check_expr(t->first), t2 = check_expr(t->second);
						if (t1 != t2) {
							fprintf (stderr, "Type mismatch in GT comparison\n");
							return (t->value = NoType);
						}
						else {
							return (t->value = Boolean);
						}}
		break;

		case GreaterThanEq :
			{int t1 = check_expr(t->first), t2 = check_expr(t->second);
						if (t1 != t2) {
							fprintf (stderr, "Type mismatch in GE comparison\n");
							return (t->value = NoType);
						}
						else {
							return (t->value = Boolean);
			
						}}
		break;

		case Plus :
			{int t1 = check_expr(t->first), t2 = check_expr(t->second);
						//check that they are numbers
						if( (t1 != Int && t1 != RealConst) || (t2 != Int && t2 != RealConst) ){
							return NoType;
						}
						else{
								//check that they are the same type
							if (t1==t2){
								return t1;
							}
							else{
								return RealConst;
							}
						}}
			break; 

		case Minus :
			{int t1 = check_expr(t->first), t2 = check_expr(t->second);
							//check that they are numbers
						if((t1 != Int && t1 != RealConst) || (t2 != Int && t2 != RealConst)){
							return NoType;
						}
						else{
								//check that they are the same type
							if (t1==t2){
								return t1;
							}
							else{
								return RealConst;
							}
						}}
			break;

		case Star :
			{int t1 = check_expr(t->first), t2 = check_expr(t->second);
							//check that they are numbers
						if((t1 != Int && t1 != RealConst) || (t2 != Int && t2 != RealConst)){
							return NoType;
						}
						else{
								//check that they are the same type
							if (t1==t2){
								return t1;
							}
							else{
								return RealConst;
							}
						}}
			break; 

		case Slash : {
			int t1 = check_expr(t->first), t2 = check_expr(t->second);
			//check that they are numbers
			if((t1 != Int && t1 != RealConst) || (t2 != Int && t2 != RealConst)){
				return NoType;
			}
			else{
					//check that they are the same type
				if (t1==t2){
					return t1;
				}
				else{
					return RealConst;
				}
			}}
			break;

		case Ident : 
			printf("case Ident\n");
			int pos = t->value;
			if (st[pos].index == 0) {
				st[pos].index = pos;
				st[pos].kind = Int;
			}
			return st[pos].kind;
		break;

		case IntConst :
			printf("case IntConst\n");
			return Int;
		break;
		case RealConst :
			printf("case RealConst\n");
			return RealConst;
		break;
		default:
			fprintf (stderr, "You shouldn't be here; invalid expression operator\n");
			break;
	}
}



// static void handle_decls (tree t)
// {
// 	for (t; t!= NULL; t = t->next) {
// 		int	kind = t->kind;
// 		printf("handling %d\n", kind);
// 		tree p;

// 		if (kind != Int && kind != Boolean) {
// 			fprintf (stderr, "Bad kind in decl\n"); return;
// 		}
// 		for (p = t->first; p != NULL; p = p->next) {
// 			int	pos = p->value;
// 			st[pos].index = pos;
// 			st[pos].kind = kind;
// 			}
// 		}
// }

void check (tree t){
	for (t; t != NULL; t = t->next) 
		//printf("working with %d\n", t->kind);
		switch (t->kind) {
			case Prog:
			printf("working with %d\n", t->kind);
			printf("case prog\n");
			check (t->first);
			printf ("\n");
			prST ();
			break;

			case Assign :
			printf("case assign\n");
			int pos = t->first->value;
			if (st[pos].index == 0) {
				st[pos].index = pos;
				st[pos].kind = Int;
			}
			if (check_expr (t->second) != st[pos].kind) 
				fprintf (stderr, "Type error in assignment to identifier %s\n", 
					id_name(t->first->value));
			break;

			case If :
			printf("case if\n");
			if (check_expr (t->first) != Boolean)
				fprintf (stderr, "Non-boolean in condition to IF\n");
			check (t->second);
			check (t->third);
			break;

			case While :
			printf("case while\n");
			if (check_expr (t->first) != Boolean)
				fprintf (stderr, "Non-boolean in condition to WHILE\n");
			check (t->second);
			break;


			default :
			fprintf (stderr, "You shouldn't be here; invalid statement\n");
		}
	}
