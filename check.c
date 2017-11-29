#include <stdio.h>
#include "tree.h"
#include "y.tab.h"
#include "st.h"

extern int top;
STentry ST[100] = {0, NoType, o};
int scope = 0;


void printST (void)
{
        int i;

        printf ("SYMBOL TABLE\n");
        for (i = 0; i <= top; i++) 
     {
                int     t = ST[i].type;
                printf ("%3d %-10s\t%s\n", i, id_name (i),
                                 t == Integer ? "int" : t == Boolean ? "boolean" : t == Real ? "real" : "<none>", ST[i].scope);

     }

static int check_expr (tree t)
{
        if (t == NULL)
        {
                fprintf (stderr, "You shouldn't be here, missing expression\n");
                return NoType;
        }
        switch (t->kind)
         {              
      	        case Equal : case NotEqual :
                case LessThan : case LTET :
                case GreaterThan : case GTET :
                {
                        int t1 = check_expr (t->first);
                        int t2 = check_expr (t->second);

                         if(t1 == t2){

                                        return (t->value = Boolean);
                                }
                                else if(t1 == Real || t2 == Integer){

                                        return(t->value = Real);
                                }
                                else if(t1 == Integer || t2 == Real){

                                        return(t->value = Real);
                                }
                                else{

                                        fprintf(stderr, "Type mismatch in comparison\n");
                                        return (t->value = NoType);
                                }
                        }
                        break;

                 }
                break;

                case Plus : case Minus :
                case Star : case Mod :
                {
                        int t1 = check_expr (t->first);
                        int t2 = check_expr (t->second);

		        if (t1 == Integer && t2 == Integer)
                           return (t->value = Integer);
			   
			else if(t1 == Real && t2 == Real)
			   return(t->value = Real);
				 
			else                  
                        {
                                fprintf (stderr, "Type mismatch in binary arithmetic expression\n");
                                return (t->value = 0);
                        }
                       
                }
                break;
		
		case Slash:
                        {

                                int t1 = check_expr(t->first);
                                int t2 = check_expr(t->second);

                                if( t1 != t2){

                                        fprintf(stderr, "Type mismatch in arithmetic expression\n");
                                        return(t->value = NoType);
                                }
                                else{

                                        return(t->value = Real);
                                }
                        }
                        break;

                case Div:
                        {

                          int t1 = check_expr(t->first);
                          int t2 = check_expr(t->second);

                          if( t1 != t2){

                             fprintf(stderr, "Type mismatch in arithmentic expression\n");
                             return(t->value = NoType);
                                }
                                else{

                                 return(t->value = Integer);
                                }
                        }
                        break;

                 case And : case Or :
                 {

                   int t1 = check_expr(t->first);
                   int t2 = check_expr(t->second);

                      if(t1 != Boolean || t2 != Boolean){

                          fprintf(stderr, "Type mismatch in And expression\n");
                              return(t->value = NoType);
                                }
                                else{

                                        return(t->value = Boolean);
                                }
                        }break;


		case Not :
		{
		         int t1 = check_expr (t1->first);
                         
                         if(t1 == Boolean)
				return(t->value = Boolean);

			else
                        {
                                fprintf (stderr, "Type mismatch in Not  expression. It should be Boolean\n");
                                return (t->value = NoType);
                        }

		}

		break; 

                case Ident :
                {
                        int pos = t->value;
                        if (ST[pos].index == 0)
                        {
                                ST[pos].index = pos;
                                ST[pos].type = Integer;
                                ST[pos].scope = scope;
                        }
                        return ST[pos].type;
                        break;
                }

                case IntConst :
                {
                        return Integer;            /* t->val contains other info */        
                }
		break;

		case RealConst :
		{
			return Real;
		}
		break;

                default:
                {

                        fprintf (stderr, "You shouldn't be here; invalid expression operator\n");
                }
        }
}

static void handle_decls (tree t)
{
        for (t; t!= NULL; t = t->next) {
                int     type = t->kind;
                tree    p;
                if (type != Integer && type != Boolean) 
		{
                        fprintf (stderr, "Bad type in decl\n"); 
			return;
                }
                for (p = t->first; p != NULL; p = p->next) 
		{
                        int     pos = p->value;
                        ST[pos].index = pos;
                        ST[pos].type = type;
			ST[pos].scope = scope;

                }
}


void check (tree t)
{
	for (t; t != NULL; t = t->next)

	        switch (t->kind){
        	
                	case Prog:
				handle_decls (t->first);
                       		check (t->second);
                       		printf ("\n");
                       		printST ();
                       		break;
                      
                	case SemiColon:
			{
                		 check(t->first);
                      		 if(t->second != NULL)
                        		check(t->second);
                        }
                 	 break;                
		case Integer:
                {

                   if(check_expr(t->first) != Int)
			fprintf(stderr, "Type error in Type\n");
                                
                    break;
                 }

                        case Real:
                        {

                           if(check_expr(t->first) != Real)
				fprintf(stderr, "Type error in Type\n");
                                
                                break;
                        }

                        case Boolean:
                        {
				if(check_expr(t->first) != Boolean)
					fprintf(stderr, "Type error in Type\n");
                                
                                break;
                        }


	/*	case Colon:
                {
                   check(t->first);
                   if(t->two)
                        check(t->two);
                   break;
                }

                 case Var:
                {
                   scope++;
		   check_expr(t->first);
		   check(t->second);
		   scope--;
		   break;     
                }
         */

			
                case Assign :
                {
                        int pos = t->first->value;
                        if (ST[pos].index == 0)
                        {
                                SymT[pos].index = pos;
                                SymT[pos].type = Integer;
                                SymT[pos].scope = scope;
                        }
                        if (check_expr (t->first) != ST[pos].type)
                         printf (stderr, "Type error in assignment to identifier %s\n", id_name(t->one->val));
                 }       
                  break;
                

		case Assert :
		{
                   check(t->first); 
		   if(check_expr(t->second)=! Boolean);
			printf("Error Values in Assert are non Boolean\n");

		   break; 
		}
                 
		 case Begin :
                {  
                   scope++;
              	   if(check_expr(t->first) =! Boolean);
			 printf("Error Values in Begin are non Boolean\n");

                   check(t->second);
                   scope--;


		    break;
                }

		 case Loop :
                {  scope++;
                   
                   if(check_expr(t->first)=! Boolean);

                         printf("Error Values in Loop are non Boolean\n");
                   check(t->second);
		   scope--;

		   break;
                }
		
		case Exit :
		{
		 check(t->first);
		 scope--;
                        
                        break;
		}

		case If :
		{
                  scope++;
                  if (check_expr (t->first) != Boolean)
                     fprintf (stderr, "Non-boolean in condition to IF\n");
                  check (t->second);
                  check (t->third);
                  scope--;             
                  break;
		}


		 case Else :
                {
                   scope++;
                   handle_decls(t->first);
                   check(t->second);
		   scope--;
                   break;
		   
                }
		break;
		
		 case ElsIf :
                {
                  scope++;
                  if (check_expr (t->first) != Boolean)
                     fprintf (stderr, "Non-boolean in condition to ElsIf\n");
                  check (t->second);
                  check (t->third);
		  scope--;
                                
                  break;
                }
                
                case When:
                {
                        if (check_expr(t->first) != Boolean)
                        	fprintf (stderr, "Non-boolean in condition to WHEN\n");
                        
                        break;
                }
                case While :
                {    
			if (check_expr (t->first) != Boolean)
                          fprintf (stderr, "Non-boolean in condition to WHILE\n");
                        
                        check (t->second);
                        break;
                }

		 case Period :
                        {

                         check(t->first);
                         if(check_expr(t->second) != Integer || check_expr(t->third) != Integer)
				fprintf(stderr, "Type mismatch in condition Period\n");
                                
                                break;
                        }

                default :
                        fprintf (stderr, "You shouldn't be here; invalid statement\n"); }
   	        
            }

