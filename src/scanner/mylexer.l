%{
#include <stdio.h>
#include "y.tab.h"
%}

%%
\*				return COMMENTTOK;
AC				{ printf("Detected AC-token"); return ACTOK; }
AN 				{ printf("Detected AN-token"); return ANTOK; }
AH 				return AHTOK;
AL 				return ALTOK;
[ABCDEFGPQRW]|GP|CTR|TMZ	return AIRSPACE_CLASS;
DP 				return DPTOK;
[a-z][a-z]* 			return TEXT;
%%
