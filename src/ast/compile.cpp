
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>


#include "program.hpp"
#include "declarations.hpp"
#include "statements.hpp"
#include "expressions.hpp"
#include "node.hpp"

//from node.hpp


//from expressions.hpp


void ASTVariable::codegen(std::ostream& out, CompileContext &context)const
{
throw std::runtime_error("Can't generate!");
}

void ASTConstant::codegen(std::ostream& out, CompileContext &context)const
{
throw std::runtime_error("Can't generate!");
}

void ASTFunctionCall::codegen(std::ostream& out, CompileContext &context)const
{
throw std::runtime_error("Can't generate!");
}

void ASTBinaryExpression::codegen(std::ostream& out, CompileContext &context)const
{
throw std::runtime_error("Can't generate!");
}



//from declarations.hpp
void ASTType::codegen(std::ostream& out, CompileContext &context)const
{
throw std::runtime_error("Can't generate!");
}

void ASTVariableDecl::codegen(std::ostream& out, CompileContext &context)const
{
throw std::runtime_error("Can't generate!");
}

void ASTArgumentDecl::codegen(std::ostream& out, CompileContext &context)const
{
throw std::runtime_error("Can't generate!");
}

void ASTFunctionDecl::codegen(std::ostream& out, CompileContext &context)const//TO IMPLEMENT HI.c (only 0 arguments)
{
//throw std::runtime_error("Can't generate!");
  out<<".globl "<<name()<<std::endl;
  out<<".type "<<name()<<" @function"<<std::endl;
  out<<name()<<":"<<std::endl;
  body()->codegen(out, context);
}





//from statements.hpp

void ASTBlock::codegen(std::ostream& out, CompileContext &context)const//TO IMPLEMENT HI.c (potentially more)
{
  std::vector<ASTNode*> stmts = statements();
  for(size_t i = 0; i<stmts.size();i++){
    stmts[i]->codegen(out, context);
  }
//throw std::runtime_error("Can't generate!");
}

void ASTReturnStatement::codegen(std::ostream& out, CompileContext &context)const//TO IMPLEMENT HI.C ONLY
{
  out<<"addiu $sp, $sp, -4"<<std::endl;
  out<<"addi $v0, $zero, 10"<<std::endl;
  out<<"addiu $sp, $sp, 4"<<std::endl;
  out<<"jr $ra"<<std::endl;

//throw std::runtime_error("Can't generate!");
}

void ASTExpressionStatement::codegen(std::ostream& out, CompileContext &context)const
{
throw std::runtime_error("Can't generate!");
}

void ASTSelectiveStatement::codegen(std::ostream& out, CompileContext &context)const
{
throw std::runtime_error("Can't generate!");
}

void ASTLoopingStatement::codegen(std::ostream& out, CompileContext &context)const
{
throw std::runtime_error("Can't generate!");
}


//from program.hpp

void ASTProgram::codegen(std::ostream& out, CompileContext &context)const
{

  std::vector<ASTDeclaration*> decls = declarations();
  for(size_t i = 0; i<decls.size();i++){
  decls[i]->codegen(out, context);
  }
//throw std::runtime_error("Can't generate!");
}
