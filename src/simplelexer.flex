%option noyywrap

%{
// Avoid error "error: 'fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);


#include "simpleparser.tab.hpp"
#include <string>


%}

DIGIT					 [0-9]
OCT						 [0-7]
HEX					   [a-fA-F0-9]
ID						 [a-zA-Z_]
USS						 [uU]
LGS						 [Ll]

%%

"//"[^\n]*    {;}
[ \t\n]+      {;}

"{"			      {return L_BRACE;}
"}"				     {return R_BRACE;}
"("			      {return L_BRACKET;}
")"			      {return R_BRACKET;}
";"           {return SEMI_COLON;}
","           {return COMMA;}
"&"           {return AMPERSAND;}

"="           {return T_EQUALS;}
"+"           {return T_PLUS;}
"-"           {return T_MINUS;}
"/"           {return T_DIVIDE;}
"*"           {return T_MULT;}
"%"           {return T_MOD;}

"<"			      {return T_LESSTHAN;}
">"			      {return T_MORETHAN;}
"=="			    {return T_EQUALSTO;}
"!="			    {return T_NOT_EQUAL;}
"<="			    {return T_LESSOREQUAL;}
">="			    {return T_MOREOREQUAL;}
"&&"			    {return T_ANDCOND;}
"||"			    {return T_ORCOND;}


{DIGIT}+        { yylval.literal = new std::string(yytext); return NUMBER;}
"'"."'"           { yylval.literal = new std::string(yytext); return CHAR_WORD;}

"\""[^\"]+"\""           {yylval.literal = new std::string(yytext); return WORD;}


"return"      {return RETURN; }

"int"         {return INT;}
"char"        {return CHAR;}
"void"        {return VOID;}
"if"          {return IF;}
"else"          {return ELSE;}
"while"       {return WHILE;}




{ID}({DIGIT}|{ID})*			 {yylval.literal = new std::string(yytext); return IDENTIFIER;}



 %%
