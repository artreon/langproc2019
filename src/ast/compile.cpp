
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>
#include <map>


#include "program.hpp"
#include "declarations.hpp"
#include "statements.hpp"
#include "expressions.hpp"
#include "node.hpp"

//from node.hpp


//from expressions.hpp


void ASTVariable::codegen(std::ostream& out, CompileContext &context)const
{

  auto search = context.variable_locations.find(name());
  if(search!=context.variable_locations.end()){
      out<<"lw, $"<<context.reg_no<<", "<<search->second<<"($fp)"<<std::endl;
      context.reg_no++;


  }
  else{throw std::runtime_error("Can't generate!");}

}
void ASTConstant::codegen(std::ostream& out, CompileContext &context)const
{
  out<<value();
//throw std::runtime_error("Can't generate!");
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
  if(type()->t() == ASTType::Int){
      if(initializer()){
        out<<"addiu $2,$0 ";
        initializer()->codegen(out,context);
        out<<std::endl;
      }
      else{out<<"addu $2, $0, $0 "<<std::endl;}
  }
  else{throw std::runtime_error("Can't generate!");}

  out<<"sw,$2, "<<context.offset<<"($fp)      #variable ";
  out << name()<<std::endl;

  context.variable_locations.insert(std::make_pair(name(),context.offset));
  context.offset+=4;

}

void ASTArgumentDecl::codegen(std::ostream& out, CompileContext &context)const
{
throw std::runtime_error("Can't generate!");
}

void ASTFunctionDecl::codegen(std::ostream& out, CompileContext &context)const//TO IMPLEMENT HI.c (only 0 arguments)
{
//throw std::runtime_error("Can't generate!");
  context.frame_val=32;
  out<<".align	2"<<std::endl;
  out<<".globl "<<name()<<std::endl;
  out<<".set	nomips16"<<std::endl;
  out<<".set	nomicromips"<<std::endl;
  out<<".ent "<<name()<<std::endl;
  out<<".type "<<name()<<", @function"<<std::endl;
  out<<name()<<":"<<std::endl;
  out<<".frame	$fp,"<<context.frame_val<<",$31		# vars= 0, regs= 1/0, args= 0, gp= 0"<<std::endl;
	out<<".mask	0x40000000,-"<<context.frame_val-4<<std::endl;
	out<<".fmask	0x00000000,0"<<std::endl;
	out<<".set	noreorder"<<std::endl;
	out<<".set	nomacro"<<std::endl;
	out<<"addiu	$sp,$sp,-"<<context.frame_val<<std::endl;
	out<<"sw	$fp,"<<context.frame_val-4<<"($sp)"<<std::endl;
	out<<"move	$fp,$sp"<<std::endl;

    body()->codegen(out, context);
    out<<std::endl;


  out<<".set	macro"<<std::endl;
	out<<".set	reorder"<<std::endl;
	out<<".end	"<<name()<<std::endl;
	out<<".size	"<<name()<<", .-"<<name()<<std::endl;
}





//from statements.hpp

void ASTBlock::codegen(std::ostream& out, CompileContext &context)const//TO IMPLEMENT HI.c (potentially more)
{

  std::vector<ASTNode*> stmts = statements();
  for(size_t i = 0; i<stmts.size();i++)
  {
    stmts[i]->codegen(out, context);
  }

//throw std::runtime_error("Can't generate!");
}

void ASTReturnStatement::codegen(std::ostream& out, CompileContext &context)const//TO IMPLEMENT HI.C ONLY
{
  if(expression()->type()==ASTExpression::Constant){
    out<<"addiu $2,$0,";
    expression()->codegen(out, context);
    out<<std::endl;
  }
  if(expression()->type()==ASTExpression::Variable){
    if(context.reg_no==2){
    expression()->codegen(out, context);
    }
    else{
      expression()->codegen(out, context);
      out<<"move $2, $"<<context.reg_no<<std::endl;
    }
  }


  out<<"move	$sp,$fp"<<std::endl;
  out<<"lw	$fp,"<<context.frame_val-4<<"($sp)"<<std::endl;
  out<<"addiu	$sp,$sp,"<<context.frame_val<<std::endl;
  out<<"j $31"<<std::endl;
  out<<"nop"<<std::endl;

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
  context.isGlobal = true;
	context.callerFunc = true;
	context.reg_no = 2;
  context.offset = 0;







  out<<".section .mdebug.abi32"<<std::endl;
  out<<".previous"<<std::endl;
  out<<".nan	legacy"<<std::endl;
  out<<".module	fp=xx"<<std::endl;
  out<<".module	nooddspreg"<<std::endl;
  out<<".abicalls"<<std::endl;
  out<<".text"<<std::endl;


  std::vector<ASTDeclaration*> decls = declarations();
  for(size_t i = 0; i<decls.size();i++){
  decls[i]->codegen(out, context);
  }
  out<<".ident	"<<"\""<<"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"<<"\""<<std::endl;

//throw std::runtime_error("Can't generate!");
}
