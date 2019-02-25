
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

void ASTFunctionDecl::codegen(std::ostream& out, CompileContext &context)const
{
throw std::runtime_error("Can't generate!");
}





//from statements.hpp

void ASTBlock::codegen(std::ostream& out, CompileContext &context)const
{
throw std::runtime_error("Can't generate!");
}

void ASTReturnStatement::codegen(std::ostream& out, CompileContext &context)const
{
throw std::runtime_error("Can't generate!");
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
throw std::runtime_error("Can't generate!");
}
