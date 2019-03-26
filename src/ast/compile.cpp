
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
void CompileContext::use_temp_reg(int used_reg[2][22]){
  for(int i=4;i<11;i++){
    if(used_reg[1][i]==0){
      used_reg[1][i]=1;
      return;
    }
  }
}
int CompileContext::get_temp_reg(int used_reg[2][22]){
  for(int i=4;i<11;i++){
    if(used_reg[1][i]==0){return i+4;}
  }
  throw std::runtime_error("cant get a temp reg!");
  return -1;
}
void CompileContext::free_temp_regs(int used_reg[2][22]){
  for(int i=4;i<11;i++){
    used_reg[1][i]=0;
  }
}





//from expressions.hpp


void ASTVariable::codegen(std::ostream& out, CompileContext &context)const
{

  auto search = context.variable_locations.find(name());
  if(search!=context.variable_locations.end()){
      out<<"lw  $"<<context.get_temp_reg(context.used_regs)<<", "<<search->second<<"($fp)      #variable "<<name()<<" in reg "<<context.get_temp_reg(context.used_regs)<<std::endl;
      context.variable_used = name();
      context.use_temp_reg(context.used_regs);
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
  context.callerFunc=true;
  out<<".option	pic0"<<std::endl;
  out<<"jal "<<name()<<std::endl;
  out<<"nop "<<std::endl;
  out<<std::endl;
  out<<".option	pic2"<<std::endl;

//throw std::runtime_error("Can't generate function call!");
}

void ASTBinaryExpression::codegen(std::ostream& out, CompileContext &context)const
{
  //throw std::runtime_error("Can't generate!");


  if (left()->type() == ASTExpression::BinaryExpression &&
			priority() > dynamic_cast<ASTBinaryExpression*>(left())->priority())
		{
			left()->codegen(out, context);
      throw std::runtime_error("slick!");

		}


  switch (op()) {
    case ASTBinaryExpression::OpAdd:
    {

      switch(left()->type()){
        case ASTExpression::Constant:
        {
          out<<"addiu $"<<context.get_temp_reg(context.used_regs)<<",$0, ";
          left()->codegen(out, context);
          out<<std::endl;
          context.use_temp_reg(context.used_regs);
        }
        break;
        case ASTExpression::Variable:
        {
          left()->codegen(out, context);

        }
        break;
        case ASTExpression::FunctionCall:
        {
          //throw std::runtime_error("Can't generate!1");
          left()->codegen(out, context);
          out<<"addu $"<<context.get_temp_reg(context.used_regs)<<",$0,$2     #function call return val"<<std::endl;
          context.use_temp_reg(context.used_regs);
        }
        break;
        case ASTExpression::BinaryExpression:
        {
          left()->codegen(out, context);
        }
        break;
      }

      switch(right()->type()){
        case ASTExpression::Constant:
        {
          out<<"addiu $"<<context.get_temp_reg(context.used_regs)-1<<",$"<<context.get_temp_reg(context.used_regs)-1<<", ";
          right()->codegen(out, context);
          out<<std::endl;
        }
        break;
        case ASTExpression::Variable:
        {
          right()->codegen(out, context);

          out<<"addu $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-1<<std::endl;

        }
        break;
        case ASTExpression::FunctionCall:
        {
          //throw std::runtime_error("Can't generate!5");
          left()->codegen(out, context);
          out<<"addu $"<<context.get_temp_reg(context.used_regs)<<",$0,$2     #function call return val"<<std::endl;
          out<<"addu $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-1<<std::endl;
        }
        break;
        case ASTExpression::BinaryExpression:
        {
          right()->codegen(out, context);
        }
        break;
      }
      break;




    }
    break;
    case ASTBinaryExpression::OpSub:
    {

      switch(left()->type()){
        case ASTExpression::Constant:
        {
          out<<"addiu $"<<context.get_temp_reg(context.used_regs)<<",$0, ";
          left()->codegen(out, context);
          out<<std::endl;
          context.use_temp_reg(context.used_regs);
        }
        break;
        case ASTExpression::Variable:
        {
          left()->codegen(out, context);

        }
        break;
        case ASTExpression::FunctionCall:
        {
          //throw std::runtime_error("Can't generate!1");
          left()->codegen(out, context);
          out<<"addu $"<<context.get_temp_reg(context.used_regs)<<",$0,$2     #function call return val"<<std::endl;
          context.use_temp_reg(context.used_regs);
        }
        break;
        case ASTExpression::BinaryExpression:
        {
          left()->codegen(out, context);
        }
        break;
      }

      switch(right()->type()){
        case ASTExpression::Constant:
        {
          out<<"addiu $"<<context.get_temp_reg(context.used_regs)-1<<",$"<<context.get_temp_reg(context.used_regs)-1<<", -";
          right()->codegen(out, context);
          out<<std::endl;
        }
        break;
        case ASTExpression::Variable:
        {
          right()->codegen(out, context);

          out<<"sub $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-1<<std::endl;

        }
        break;
        case ASTExpression::FunctionCall:
        {
          //throw std::runtime_error("Can't generate!5");
          left()->codegen(out, context);
          out<<"addu $"<<context.get_temp_reg(context.used_regs)<<",$0,$2     #function call return val"<<std::endl;
          out<<"sub $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-1<<std::endl;
        }
        break;
        case ASTExpression::BinaryExpression:
        {
          right()->codegen(out, context);
        }
        break;
      }
      break;




    }
    break;
    case ASTBinaryExpression::OpMul:
    {

      switch(left()->type()){
        case ASTExpression::Constant:
        {
          out<<"addiu $"<<context.get_temp_reg(context.used_regs)<<",$0, ";
          left()->codegen(out, context);
          out<<std::endl;
          context.use_temp_reg(context.used_regs);
        }
        break;
        case ASTExpression::Variable:
        {
          left()->codegen(out, context);

        }
        break;
        case ASTExpression::FunctionCall:
        {
          throw std::runtime_error("Can't generate!4");
        }
        break;
        case ASTExpression::BinaryExpression:
        {
          left()->codegen(out, context);
        }
        break;
      }

        switch(right()->type()){
          case ASTExpression::Constant:
          {
            out<<"addiu $"<<context.get_temp_reg(context.used_regs)<<",$0, ";
            right()->codegen(out, context);
            out<<std::endl;
            context.use_temp_reg(context.used_regs);
            out<<"multu $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-1<<std::endl;
             out<<"mflo $"<<context.get_temp_reg(context.used_regs)-1<<std::endl;


          }
          break;
          case ASTExpression::Variable:
          {
            right()->codegen(out, context);
            out<<"multu $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-1<<std::endl;
             out<<"mflo $"<<context.get_temp_reg(context.used_regs)-1<<std::endl;



          }
          break;
          case ASTExpression::FunctionCall:
          {
            throw std::runtime_error("Can't generate!5");
          }
          break;
          case ASTExpression::BinaryExpression:
          {
            right()->codegen(out, context);
          }
          break;
        }
        break;



    }
    break;
    case ASTBinaryExpression::OpDiv:
    {

      switch(left()->type()){
        case ASTExpression::Constant:
        {
          out<<"addiu $"<<context.get_temp_reg(context.used_regs)<<",$0, ";
          left()->codegen(out, context);
          out<<std::endl;
          context.use_temp_reg(context.used_regs);
        }
        break;
        case ASTExpression::Variable:
        {
          left()->codegen(out, context);

        }
        break;
        case ASTExpression::FunctionCall:
        {
          throw std::runtime_error("Can't generate!4");
        }
        break;
        case ASTExpression::BinaryExpression:
        {
          left()->codegen(out, context);
        }
        break;
      }

        switch(right()->type()){
          case ASTExpression::Constant:
          {
            out<<"addiu $"<<context.get_temp_reg(context.used_regs)<<",$0, ";
            right()->codegen(out, context);
            out<<std::endl;
            context.use_temp_reg(context.used_regs);
            out<<"divu $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-1<<std::endl;
             out<<"mflo $"<<context.get_temp_reg(context.used_regs)-1<<std::endl;


          }
          break;
          case ASTExpression::Variable:
          {
            right()->codegen(out, context);
            out<<"divu $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-1<<std::endl;
             out<<"mflo $"<<context.get_temp_reg(context.used_regs)-1<<std::endl;



          }
          break;
          case ASTExpression::FunctionCall:
          {
            throw std::runtime_error("Can't generate!5");
          }
          break;
          case ASTExpression::BinaryExpression:
          {
            right()->codegen(out, context);
          }
          break;
        }
        break;



    }


    break;
    case ASTBinaryExpression::OpMod:

    break;
    case ASTBinaryExpression::OpAssign:
    {
      if(left()->type()==ASTExpression::Variable){
        left()->codegen(out, context);
        context.temp_reg_location=context.get_temp_reg(context.used_regs)-1;

      }
      else{
        throw std::runtime_error("Can't generate!6");
      }

      switch(right()->type()){
        case ASTExpression::Constant:
        {
          out<<"addiu $"<<context.get_temp_reg(context.used_regs)-1<<",$0, ";
          right()->codegen(out, context);
          out<<std::endl;

          auto search1 = context.variable_locations.find(context.variable_used);
          if(search1!=context.variable_locations.end())
          {
            out<<"sw  $"<<context.temp_reg_location<<", "<<search1->second<<"($fp)     #variable "<<context.variable_used<<std::endl;
          }

        }
        break;
        case ASTExpression::Variable:
        {
          throw std::runtime_error("Can't generate!7");
        }
        break;
        case ASTExpression::FunctionCall:
        {
          right()->codegen(out, context);
          out<<"addu $"<<context.get_temp_reg(context.used_regs)<<",$0,$2     #function call return val"<<std::endl;

          out<<"addu $"<<context.temp_reg_location<<", $"<<context.temp_reg_location<<", $"<<context.get_temp_reg(context.used_regs)<<std::endl;
          auto search2 = context.variable_locations.find(context.variable_used);
          if(search2!=context.variable_locations.end())
          {
            out<<"sw  $"<<context.temp_reg_location<<", "<<search2->second<<"($fp)     #variable "<<context.variable_used<<std::endl;
          }

          //throw std::runtime_error("Can't generate!8");
        }
        break;
        case ASTExpression::BinaryExpression:
        {
          right()->codegen(out, context);
          out<<"addu $"<<context.temp_reg_location<<",$0,$"<<context.get_temp_reg(context.used_regs)-1<<std::endl;
          auto search3 = context.variable_locations.find(context.variable_used);
          if(search3!=context.variable_locations.end())
          {
            out<<"sw  $"<<context.temp_reg_location<<", "<<search3->second<<"($fp)     #variable "<<context.variable_used<<std::endl;
          }

        }
        break;






      }
      context.free_temp_regs(context.used_regs);
      break;
    }
    break;
    case ASTBinaryExpression::OpLess:
    {
      switch(left()->type()){
        case ASTExpression::Constant:
        {
          out<<"addiu $"<<context.get_temp_reg(context.used_regs)<<",$0, ";
          left()->codegen(out, context);
          out<<std::endl;
          context.use_temp_reg(context.used_regs);
        }
        break;
        case ASTExpression::Variable:
        {
          left()->codegen(out, context);

        }
        break;
        case ASTExpression::FunctionCall:
        {
          throw std::runtime_error("Can't generate!4");
        }
        break;
        case ASTExpression::BinaryExpression:
        {
          left()->codegen(out, context);
        }
        break;
      }

        switch(right()->type()){
          case ASTExpression::Constant:
          {
            out<<"addiu $"<<context.get_temp_reg(context.used_regs)<<",$0, ";
            right()->codegen(out, context);
            out<<std::endl;
            context.use_temp_reg(context.used_regs);

            out<<"slt $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-1<<std::endl;
            out<<"beq $"<<context.get_temp_reg(context.used_regs)-2<<", $0"<<", L"<<context.branch_to<<std::endl;


          }
          break;
          case ASTExpression::Variable:
          {
            right()->codegen(out, context);
            out<<"slt $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-1<<std::endl;
            out<<"beq $"<<context.get_temp_reg(context.used_regs)-2<<", $0"<<", L"<<context.branch_to<<std::endl;


          }
          break;
          case ASTExpression::FunctionCall:
          {
            throw std::runtime_error("Can't generate!5");
          }
          break;
          case ASTExpression::BinaryExpression:
          {
            right()->codegen(out, context);
          }
          break;
        }
        break;

    }
    break;
    case ASTBinaryExpression::OpLessOrEqual:

    break;
    case ASTBinaryExpression::OpGreater:
    {
      switch(left()->type()){
        case ASTExpression::Constant:
        {
          out<<"addiu $"<<context.get_temp_reg(context.used_regs)<<",$0, ";
          left()->codegen(out, context);
          out<<std::endl;
          context.use_temp_reg(context.used_regs);
        }
        break;
        case ASTExpression::Variable:
        {
          left()->codegen(out, context);

        }
        break;
        case ASTExpression::FunctionCall:
        {
          throw std::runtime_error("Can't generate!4");
        }
        break;
        case ASTExpression::BinaryExpression:
        {
          left()->codegen(out, context);
        }
        break;
      }

        switch(right()->type()){
          case ASTExpression::Constant:
          {
            out<<"addiu $"<<context.get_temp_reg(context.used_regs)<<",$0, ";
            right()->codegen(out, context);
            out<<std::endl;
            context.use_temp_reg(context.used_regs);

            out<<"slt $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-1<<std::endl;
            out<<"bne $"<<context.get_temp_reg(context.used_regs)-2<<", $0"<<", L"<<context.branch_to<<std::endl;


          }
          break;
          case ASTExpression::Variable:
          {
            right()->codegen(out, context);
            out<<"slt $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-1<<std::endl;
            out<<"bne $"<<context.get_temp_reg(context.used_regs)-2<<", $0"<<", L"<<context.branch_to<<std::endl;


          }
          break;
          case ASTExpression::FunctionCall:
          {
            throw std::runtime_error("Can't generate!5");
          }
          break;
          case ASTExpression::BinaryExpression:
          {
            right()->codegen(out, context);
          }
          break;
        }
        break;

    }
    break;
    case ASTBinaryExpression::OpGreaterOrEqual:

    break;
    case ASTBinaryExpression::OpEqual:
    {
      switch(left()->type()){
        case ASTExpression::Constant:
        {
          out<<"addiu $"<<context.get_temp_reg(context.used_regs)<<",$0, ";
          left()->codegen(out, context);
          out<<std::endl;
          context.use_temp_reg(context.used_regs);
        }
        break;
        case ASTExpression::Variable:
        {
          left()->codegen(out, context);

        }
        break;
        case ASTExpression::FunctionCall:
        {
          throw std::runtime_error("Can't generate!4");
        }
        break;
        case ASTExpression::BinaryExpression:
        {
          left()->codegen(out, context);
        }
        break;
      }

        switch(right()->type()){
          case ASTExpression::Constant:
          {
            out<<"addiu $"<<context.get_temp_reg(context.used_regs)<<",$0, ";
            right()->codegen(out, context);
            out<<std::endl;
            context.use_temp_reg(context.used_regs);
            out<<"bne $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-1<<", L"<<context.branch_to<<std::endl;

          }
          break;
          case ASTExpression::Variable:
          {
            right()->codegen(out, context);
            out<<"bne $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-1<<", L"<<context.branch_to<<std::endl;


          }
          break;
          case ASTExpression::FunctionCall:
          {
            throw std::runtime_error("Can't generate!5");
          }
          break;
          case ASTExpression::BinaryExpression:
          {
            right()->codegen(out, context);
          }
          break;
        }
        break;

    }
    break;
    case ASTBinaryExpression::OpNotEqual:
    {
    switch(left()->type()){
      case ASTExpression::Constant:
      {
        out<<"addiu $"<<context.get_temp_reg(context.used_regs)<<",$0, ";
        left()->codegen(out, context);
        out<<std::endl;
        context.use_temp_reg(context.used_regs);
      }
      break;
      case ASTExpression::Variable:
      {
        left()->codegen(out, context);

      }
      break;
      case ASTExpression::FunctionCall:
      {
        throw std::runtime_error("Can't generate!4");
      }
      break;
      case ASTExpression::BinaryExpression:
      {
        left()->codegen(out, context);
      }
      break;
    }

      switch(right()->type()){
        case ASTExpression::Constant:
        {
          out<<"addiu $"<<context.get_temp_reg(context.used_regs)<<",$0, ";
          right()->codegen(out, context);
          out<<std::endl;
          context.use_temp_reg(context.used_regs);
          out<<"beq $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-1<<", L"<<context.branch_to<<std::endl;

        }
        break;
        case ASTExpression::Variable:
        {
          right()->codegen(out, context);
          out<<"beq $"<<context.get_temp_reg(context.used_regs)-2<<", $"<<context.get_temp_reg(context.used_regs)-1<<", L"<<context.branch_to<<std::endl;


        }
        break;
        case ASTExpression::FunctionCall:
        {
          throw std::runtime_error("Can't generate!5");
        }
        break;
        case ASTExpression::BinaryExpression:
        {
          right()->codegen(out, context);
        }
        break;
      }
      break;
    }
    break;
    case ASTBinaryExpression::OpLogicAnd:
    {
      switch(left()->type()){
        case ASTExpression::Constant:
        {
          throw std::runtime_error("Can't generate!5");

        }
        break;
        case ASTExpression::Variable:
        {

          throw std::runtime_error("Can't generate!5");

        }
        break;
        case ASTExpression::FunctionCall:
        {
          throw std::runtime_error("Can't generate!4");
        }
        break;
        case ASTExpression::BinaryExpression:
        {
          left()->codegen(out, context);
        }
        break;
      }

        switch(right()->type()){
          case ASTExpression::Constant:
          {
            throw std::runtime_error("Can't generate!5");

          }
          break;
          case ASTExpression::Variable:
          {
            throw std::runtime_error("Can't generate!5");

          }
          break;
          case ASTExpression::FunctionCall:
          {
            throw std::runtime_error("Can't generate!5");
          }
          break;
          case ASTExpression::BinaryExpression:
          {
            right()->codegen(out, context);
          }
          break;
        }
        break;

    }
    break;
    case ASTBinaryExpression::OpLogicOr:

    break;

  }


  if (right()->type() == ASTExpression::BinaryExpression &&
			priority() > dynamic_cast<ASTBinaryExpression*>(right())->priority())
		{

			right()->codegen(out, context);

    }




}



//from declarations.hpp
void ASTType::codegen(std::ostream& out, CompileContext &context)const
{
throw std::runtime_error("Can't generate!10");
}

void ASTVariableDecl::codegen(std::ostream& out, CompileContext &context)const
{
  if(context.isGlobal==true){
    out<<".globl	"<<name()<<std::endl;
  	out<<".data"<<std::endl;
  	out<<".align	2"<<std::endl;
  	out<<".type	"<<name()<<", @object"<<std::endl;
  out<<".size	"<<name()<<", 4"<<std::endl;
  out<<name()<<":"<<std::endl;
  out<<".word	";
  initializer()->codegen(out, context);
  out<<std::endl;
  out<<".text"<<std::endl;
  }
  else{





  if(type()->t() == ASTType::Int){

      if(initializer()){
        out<<"addiu $"<<context.get_temp_reg(context.used_regs)<<",$0, ";
        initializer()->codegen(out,context);
        out<<std::endl;
        context.use_temp_reg(context.used_regs);
      }
      else{context.use_temp_reg(context.used_regs);}

  }
  else{throw std::runtime_error("Can't generate non int");}

  out<<"sw $"<<context.get_temp_reg(context.used_regs)-1<<", "<<context.offset<<"($fp)      #variable ";
  out << name()<<std::endl;
  context.free_temp_regs(context.used_regs);

  context.variable_locations.insert(std::make_pair(name(),context.offset));
  context.offset+=4;

}
}

void ASTArgumentDecl::codegen(std::ostream& out, CompileContext &context)const
{
throw std::runtime_error("Can't generate!12");
}

void ASTFunctionDecl::codegen(std::ostream& out, CompileContext &context)const//TO IMPLEMENT HI.c (only 0 arguments)
{
//throw std::runtime_error("Can't generate!13");
context.isGlobal = false;
  context.frame_val+= 32;
  out<<".align	2"<<std::endl;
  out<<".globl "<<name()<<std::endl;
  out<<".set	nomips16"<<std::endl;
  out<<".set	nomicromips"<<std::endl;
  out<<".ent "<<name()<<std::endl;
  out<<".type "<<name()<<", @function"<<std::endl;
  out<<name()<<":"<<std::endl;
  out<<".frame	$fp,"<<context.frame_val<<",$31		# vars= 0, regs= 1/0, args= 0, gp= 0"<<std::endl;
	out<<".mask	0x40000000,-4"<<std::endl;
	out<<".fmask	0x00000000,0"<<std::endl;
	out<<".set	noreorder"<<std::endl;
	out<<".set	nomacro"<<std::endl;
	out<<"addiu	$sp,$sp,-"<<context.frame_val<<std::endl;
  //int temp = context.frame_val;
  //if(context.callerFunc==true){
    //out<<"sw $31,"<<temp-4<<"($sp)"<<std::endl;
	//out<<"sw $fp,"<<temp-8<<"($sp)"<<std::endl;}
  //else{
  out<<"sw $fp,"<<context.frame_val-4<<"($sp)"<<std::endl;
  //}

	out<<"move	$fp,$sp"<<std::endl;

    body()->codegen(out, context);
    out<<std::endl;


  out<<".set	macro"<<std::endl;
	out<<".set	reorder"<<std::endl;
	out<<".end	"<<name()<<std::endl;
	out<<".size	"<<name()<<", .-"<<name()<<std::endl;
  context.isGlobal = true;
}





//from statements.hpp

void ASTBlock::codegen(std::ostream& out, CompileContext &context)const//TO IMPLEMENT HI.c (potentially more)
{

  std::vector<ASTNode*> stmts = statements();
  for(size_t i = 0; i<stmts.size();i++)
  {
    stmts[i]->codegen(out, context);
  }

//throw std::runtime_error("Can't generate!14");
}

void ASTReturnStatement::codegen(std::ostream& out, CompileContext &context)const//TO IMPLEMENT HI.C ONLY
{
  if(expression()->type()==ASTExpression::Constant){
    out<<"addiu $2,$0,";
    expression()->codegen(out, context);
    out<<std::endl;
  }
  if(expression()->type()==ASTExpression::Variable){

      expression()->codegen(out, context);
      out<<"move $2, $"<<context.get_temp_reg(context.used_regs)-1<<std::endl;

  }


  out<<"move	$sp,$fp"<<std::endl;
  //int temp = context.frame_val;
  //if(context.callerFunc==true){
    //out<<"lw $31,"<<temp-4<<"($sp)"<<std::endl;
	//out<<"sw $fp,"<<temp-8<<"($sp)"<<std::endl;}
  //else{
    out<<"lw	$fp,"<<context.frame_val-4<<"($sp)"<<std::endl;
  //}
  out<<"addiu	$sp,$sp,"<<context.frame_val<<std::endl;
  out<<"j $31"<<std::endl;
  out<<"nop"<<std::endl;

//throw std::runtime_error("Can't generate!15");
}

void ASTExpressionStatement::codegen(std::ostream& out, CompileContext &context)const
{
  expression()->codegen(out, context);
//throw std::runtime_error("Can't generate!15");
}

void ASTSelectiveStatement::codegen(std::ostream& out, CompileContext &context)const
{
condition()->codegen(out, context);
ifBranch()->codegen(out, context);
if(elseBranch()){
  out<<"j Next"<<std::endl;
}
out<<"L"<<context.branch_to<<":"<<std::endl;
context.branch_to++;

if(elseBranch()){
  elseBranch()->codegen(out, context);

  out<<"Next:"<<std::endl;
}



//throw std::runtime_error("Can't generate!16");
}

void ASTLoopingStatement::codegen(std::ostream& out, CompileContext &context)const
{
//throw std::runtime_error("Can't generate!17");
out<<"L"<<context.branch_to<<":"<<std::endl;
context.branch_to++;
condition()->codegen(out, context);
body()->codegen(out, context);
out<<"j L"<<context.branch_to-1<<std::endl;
out<<"L"<<context.branch_to<<":"<<std::endl;




}


//from program.hpp

void ASTProgram::codegen(std::ostream& out, CompileContext &context)const
{
  context.isGlobal = true;
	context.callerFunc = false;
  context.offset = 0;
  context.branch_to=0;
  context.frame_val=0;








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
