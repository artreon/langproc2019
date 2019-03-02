%code requires{
	#include <fstream>
	#include <string>
	#include <iostream>
	#include <cassert>

	extern int yylex();
	extern int yyparse();
	extern FILE *yyin;


	#include "ast/program.hpp"
	extern ASTProgram* program;

	void yyerror(const char *s);
}

%union {
	std::string* literal;
	ASTGlobalDeclarations* global_decls;
	ASTDeclaration* declaration;
	ASTBlock* block;
	ASTStatementList* stmt_list;
	ASTNode* node;
	ASTExpression* expr;
	ASTArgumentsList* args_list;
	ASTArgumentsFormal* args_formal;
	ASTType* type;
}

%token  INT CHAR VOID CHAR_WORD COMMA IF ELSE AMPERSAND WHILE
%token IDENTIFIER RETURN NUMBER WORD
%token L_BRACE R_BRACE L_BRACKET R_BRACKET SEMI_COLON
%token T_EQUALS T_PLUS T_DIVIDE T_MOD T_MULT T_MINUS
%token T_EQUALSTO T_LESSTHAN T_MORETHAN T_LESSOREQUAL T_MOREOREQUAL T_NOT_EQUAL T_ANDCOND T_ORCOND

%type <literal> IDENTIFIER WORD CHAR_WORD NUMBER
%type <global_decls> global_decl
%type <declaration> function_decl variable_decl declaration
%type <block> block
%type <stmt_list> statement_list
%type <node> statement selective_statement looping_statement
%type <expr> expression logic_or_expression logic_and_expression cmp_expression add_sub_expression term factor function_call
%type <args_list> arguments
%type <args_formal> arguments_formal
%type <type> type


%%

program:
				 global_decl									{ program = new ASTProgram(*$1); }

global_decl:
				 declaration									{ $$ = new ASTGlobalDeclarations(); $$->push_back($1); }
				| global_decl declaration		 	{ $1->push_back($2); }

declaration
				: variable_decl		{ $$ = $1; }
			  | function_decl		{ $$ = $1; }

function_decl:
				 type IDENTIFIER L_BRACKET arguments_formal R_BRACKET block		 			{ $$ = new ASTFunctionDecl(*$2, $1, *$4, $6); }
				| type IDENTIFIER L_BRACKET R_BRACKET block													{ $$ = new ASTFunctionDecl(*$2, $1, ASTArgumentsFormal(), $5); }
				| type IDENTIFIER L_BRACKET arguments_formal R_BRACKET SEMI_COLON		{ $$ = new ASTFunctionDecl(*$2, $1, *$4); }
				| type IDENTIFIER L_BRACKET R_BRACKET SEMI_COLON										{ $$ = new ASTFunctionDecl(*$2, $1, ASTArgumentsFormal()); }

block:
				 L_BRACE statement_list R_BRACE					{ $$ = new ASTBlock(*$2); }
				| L_BRACE R_BRACE	 											{ $$ = new ASTBlock(ASTStatementList()); }

statement_list:
	 			statement													{ $$ = new ASTStatementList(); $$->push_back($1); }
				| statement_list statement				{ $1->push_back($2); }

statement:
				 expression SEMI_COLON							{ $$ = new ASTExpressionStatement($1); }
				| RETURN expression SEMI_COLON			{ $$ = new ASTReturnStatement($2); }
				| RETURN SEMI_COLON									{ $$ = new ASTReturnStatement(); }
				| variable_decl											{ $$ = $1; }
				| selective_statement								{ $$ = $1; }
				| looping_statement									{ $$ = $1; }
				| block															{ $$ = $1; }

selective_statement:
				 IF L_BRACKET expression R_BRACKET statement									{ $$ = new ASTSelectiveStatement($3, $5); }
				| IF L_BRACKET expression R_BRACKET statement ELSE statement	{ $$ = new ASTSelectiveStatement($3, $5, $7); }

looping_statement:
		 		WHILE L_BRACKET expression R_BRACKET block									{$$ = new ASTLoopingStatement($3, $5);}

variable_decl:
				 type IDENTIFIER SEMI_COLON																	{ $$ = new ASTVariableDecl(*$2, $1); }
				| type IDENTIFIER COMMA IDENTIFIER SEMI_COLON		 											{ $$ = new ASTVariableDecl(*$2, $1); $$ = new ASTVariableDecl(*$4,$1); }
				| type IDENTIFIER T_EQUALS expression SEMI_COLON						{ $$ = new ASTVariableDecl(*$2, $1, $4); }

expression:
				 logic_or_expression																				{ $$ = $1; }
				| IDENTIFIER T_EQUALS expression														{ $$ = new ASTBinaryExpression(new ASTVariable(*$1), $3, ASTBinaryExpression::OpAssign); }

logic_or_expression:
				 logic_and_expression																				{ $$ = $1; }
				| logic_or_expression T_ORCOND logic_and_expression					{ $$ = new ASTBinaryExpression($1, $3, ASTBinaryExpression::OpLogicOr); }

logic_and_expression:
				 cmp_expression																							{ $$ = $1; }
				| logic_and_expression T_ANDCOND cmp_expression							{ $$ = new ASTBinaryExpression($1, $3, ASTBinaryExpression::OpLogicAnd); }

cmp_expression:
				 add_sub_expression																					{ $$ = $1; }
				| cmp_expression T_EQUALSTO add_sub_expression							{ $$ = new ASTBinaryExpression($1, $3, ASTBinaryExpression::OpEqual); }
				| cmp_expression T_LESSTHAN add_sub_expression							{ $$ = new ASTBinaryExpression($1, $3, ASTBinaryExpression::OpLess); }
				| cmp_expression T_LESSOREQUAL add_sub_expression						{	$$ = new ASTBinaryExpression($1, $3, ASTBinaryExpression::OpLessOrEqual); }
				| cmp_expression T_MORETHAN add_sub_expression							{ $$ = new ASTBinaryExpression($1, $3, ASTBinaryExpression::OpGreater); }
				| cmp_expression T_MOREOREQUAL add_sub_expression						{ $$ = new ASTBinaryExpression($1, $3, ASTBinaryExpression::OpGreaterOrEqual); }
				| cmp_expression T_NOT_EQUAL add_sub_expression							{ $$ = new ASTBinaryExpression($1, $3, ASTBinaryExpression::OpNotEqual); }

add_sub_expression:
				 term																			{ $$ = $1; }
				| add_sub_expression T_PLUS term					{ $$ = new ASTBinaryExpression($1, $3, ASTBinaryExpression::OpAdd); }
				| add_sub_expression T_MINUS term					{ $$ = new ASTBinaryExpression($1, $3, ASTBinaryExpression::OpSub); }

term:
				 factor																		{ $$ = $1; }
				| term T_MULT factor											{ $$ = new ASTBinaryExpression($1, $3, ASTBinaryExpression::OpMul); }
				| term T_DIVIDE factor										{ $$ = new ASTBinaryExpression($1, $3, ASTBinaryExpression::OpDiv); }
				| term T_MOD factor												{ $$ = new ASTBinaryExpression($1, $3, ASTBinaryExpression::OpMod); }

factor:
				 NUMBER																{ $$ = new ASTConstant(*$1); }
				| CHAR_WORD														{ $$ = new ASTConstant(*$1); }
				| WORD																{ $$ = new ASTConstant(*$1); }
				| IDENTIFIER													{ $$ = new ASTVariable(*$1); }
				| function_call												{ $$ = $1; }
			/*	| T_MULT IDENTIFIER
				| AMPERSAND IDENTIFIER*/
				| L_BRACKET expression R_BRACKET			{ $$ = $2; }

function_call:
				 IDENTIFIER L_BRACKET arguments R_BRACKET		{ $$ = new ASTFunctionCall(*$1, *$3); }
				| IDENTIFIER L_BRACKET R_BRACKET						{ $$ = new ASTFunctionCall(*$1, ASTArgumentsList()); }

arguments_formal:
				 type IDENTIFIER														{ $$ = new ASTArgumentsFormal(); $$->push_back(new ASTArgumentDecl(*$2, $1)); }
				| arguments_formal COMMA type IDENTIFIER		{ $1->push_back(new ASTArgumentDecl(*$4, $3)); }

arguments:
				 expression														{ $$ = new ASTArgumentsList(); $$->push_back($1); }
				| arguments COMMA expression					{ $1->push_back($3); }

type:
				 INT								{ $$ = new ASTType(ASTType::Int); }
				| CHAR							{ $$ = new ASTType(ASTType::Char); }
				| VOID							{ $$ = new ASTType(ASTType::Void); }
				| type T_MULT				{ $$ = new ASTType(ASTType::Pointer, $1); }
	%%



	ASTProgram* program = nullptr;

int main(int argc, char* argv[])
{

	if(argc != 5){
      std::cout<< "incorrect arguments";
      return -1;
  }

	FILE *myfile = fopen(argv[2], "r");

	if (!myfile) {
		std::cout << "cant open c file" << std::endl;
		return -1;
	}

	if(std::string(argv[1])== "--translate"){

		yyin = myfile;

		yyparse();


		std::ofstream py_out;

		py_out.open(argv[4]);
		size_t count = 0;
		TranslateContext cont(count);

    program->translate(py_out, cont);

		py_out<<std::endl;
    py_out<<"# Boilerplate"<<std::endl;
    py_out<<"if __name__ == \"__main__\":"<<std::endl;
    py_out<<"\timport sys"<<std::endl;
    py_out<<"\tret=main()"<<std::endl;
    py_out<<"\tsys.exit(ret)"<<std::endl;

		py_out.close();
	}
	if(std::string(argv[1])=="-S"){

		yyin = myfile;

		yyparse();


		std::ofstream mips_out;

		mips_out.open(argv[4]);

		size_t count = 0;
		CompileContext cont(count);
		mips_out<<".file	1 "<<"\""<<argv[2]<<"\""<<std::endl;
    program->codegen(mips_out, cont);

		//std::cout<<"only translate function is supported"<<std::endl;

		return -1;
	}




	return 0;
}




void yyerror(const char *s)
{
	std::cout << " error.  Msg: " << s << std::endl;

	exit(-1);
}
