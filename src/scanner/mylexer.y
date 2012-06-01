%{
#include <stdio.h>
%}

%token ACTOK AIRSPACE_CLASS ALTOK AHTOK COMMENTTOK ANTOK DPTOK TEXT
%%
acline: ACTOK AIRSPACE_CLASS { printf("AC line detected:%s %s", $1, $2); };
anline: ANTOK TEXT { printf("Found AN: %s", $2); };
%%

int main (void) {
  return yyparse();
}

/* Added because panther doesn't have liby.a installed. */
int yyerror (char *msg) {
  return fprintf (stderr, "YACC: %s\n", msg);
}
