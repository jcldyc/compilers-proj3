extern char *yytext;
int yylex(void);


#define Ident 1
#define IntConst 2
#define RealConst 3


#define Var 11
#define Int 12
#define Real 13
#define Boolean 14
#define Record 21
#define While 22
#define Do 23
#define End 24
#define Begin 25
#define Loop 26
#define Exit 27
#define Bind 31
#define To 32
#define Assert 33
#define When 41
#define If 42
#define Then 43
#define Elsif 44
#define Else 45
#define Put 46
#define Or 51
#define And 52
#define Not 53
#define NotEqual 54
#define Div 55
#define Mod 56
#define Colon 61
#define Definition 62
#define LessThan 63
#define GreaterThan 64
#define LessThanEq 65
#define GreaterThanEq 66
#define Dot 67
#define Comma 68
#define Assign 71
#define Plus 72
#define Minus 73
#define Star 74
#define Slash 75
#define Semicolon 76
#define LPar 77
#define RPar 78
#define Prog 81
#define NoType 82
#define Field 83