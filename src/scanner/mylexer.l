%{
#include <stdio.h>
#include "y.tab.h"
%}

%%
\*				return COMMENTTOK;
AC				return ACTOK;
[ABCDEFGPQRW]|GP|CTR|TMZ	return AIRSPACE_CLASS;
[a-z][a-z]* 			return TEXT;
AN 				return ANTOK;
AH 				return AHTOK;
AL 				return ALTOK;
DP 				return DPTOK;
%%
