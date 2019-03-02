
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
void TranslateContext::printTabs(std::ostream& out)
{
		for (size_t i = 0; i < tabCount; i++)
			 out << "\t";

}



void TranslateContext::incTab() { tabCount++; }

void TranslateContext::decTab() { tabCount = (tabCount > 0 ? tabCount - 1 : 0);}



//from expressions.hpp


void ASTVariable::translate(std::ostream& out, TranslateContext &context) const
{
  out<<name();
}

void ASTConstant::translate(std::ostream& out, TranslateContext &context) const
{
  out<<value();
}

void ASTFunctionCall::translate(std::ostream& out, TranslateContext &context) const
{
  auto args = arguments();

		out << name() << '(';

		for (size_t i = 0; i < args.size(); i++) {
			args[i]->translate(out, context);
			if (i < args.size() - 1)
				out << ", ";
		}
		out << ')';
}

void ASTBinaryExpression::translate(std::ostream& out, TranslateContext &context) const
{
  if (left()->type() == ASTExpression::BinaryExpression &&
			priority() > dynamic_cast<ASTBinaryExpression*>(left())->priority())
		{
			out << "(";
			left()->translate(out, context);
			out << ")";
		}
	else
			left()->translate(out, context);

		switch (op()) {
			case ASTBinaryExpression::OpAdd:
				out << " + ";
				break;
			case ASTBinaryExpression::OpSub:
				out << " - ";
				break;
			case ASTBinaryExpression::OpMul:
				out << " * ";
				break;
			case ASTBinaryExpression::OpDiv:
				out << " / ";
				break;
			case ASTBinaryExpression::OpMod:
				out << " % ";
				break;
			case ASTBinaryExpression::OpAssign:
				out << " = ";
				break;
			case ASTBinaryExpression::OpLess:
				out << " < ";
				break;
			case ASTBinaryExpression::OpLessOrEqual:
				out << " <= ";
				break;
			case ASTBinaryExpression::OpGreater:
				out << " > ";
				break;
			case ASTBinaryExpression::OpGreaterOrEqual:
				out << " >= ";
				break;
			case ASTBinaryExpression::OpEqual:
				out << " == ";
				break;
			case ASTBinaryExpression::OpNotEqual:
				out << " != ";
				break;
			case ASTBinaryExpression::OpLogicAnd:
				out << " and ";
				break;
			case ASTBinaryExpression::OpLogicOr:
				out << " or ";
				break;
		}

		if (right()->type() == ASTExpression::BinaryExpression &&
			priority() > dynamic_cast<ASTBinaryExpression*>(right())->priority())
		{
			out << "(";
			right()->translate(out, context);
			out << ")";
		}
		else
			right()->translate(out, context);
}

//from declarations.hpp
void ASTType::translate(std::ostream& out, TranslateContext &context) const
{
  out<<" ";
}

void ASTVariableDecl::translate(std::ostream& out, TranslateContext &context) const
{
  bool isString = false;

    if (type()->t() == ASTType::Pointer) {
        if (type()->pointerTo()->t() == ASTType::Char){isString = true;}
        else {return;}
    }

    context.printTabs(out);

    out << name();
		if(context.isGlobal){
			context.globals.push_back(name());
		}


      if (initializer()) {
        out << " = ";
        initializer()->translate(out, context);
      }
      else {
      if (isString) {out << " = \"\"";}
      else {out << " = 0";}
      }

  out << std::endl;
}

void ASTArgumentDecl::translate(std::ostream& out, TranslateContext &context) const
{
  out << name();
}

void ASTFunctionDecl::translate(std::ostream& out, TranslateContext &context) const
{



    out << "def " << name() << "(";
    auto args = arguments();

    //if (name() == "main"){mainFuncIsPresent  = true;}

    for (size_t i = 0; i < args.size(); i++) {
      args[i]->translate(out, context);
      if (i < args.size() - 1)
      out << ", ";
    }

    out << "):" << std::endl;

			if(name()=="main"){}
			else{
					if(context.globals.empty()){
					out<< std::endl;
					}
					else{
						for(size_t i=0;i<context.globals.size();i++){
					out<<"	global "<<context.globals[i];
					out<<std::endl;}
					}
			}
			context.isGlobal = false;

		context.incTab();
		 body()->translate(out, context);


    context.decTab();
}





//from statements.hpp
bool ASTBlock::emptyBlock(ASTStatementList statements) const
{
	if (statements.empty()){return true;}
	else{return false;}
}

void ASTBlock::translate(std::ostream& out, TranslateContext &context) const
{

  std::vector<ASTNode*> stmts = statements();
	if(emptyBlock(stmts)){out<<"	pass" << std::endl;}
  for(size_t i = 0; i<stmts.size();i++){
    stmts[i]->translate(out, context);
  }
}
void ASTReturnStatement::translate(std::ostream& out, TranslateContext &context) const
{
  context.printTabs(out);
  if (expression()) {
    out << "return ";
    expression()->translate(out, context);
    out << std::endl;
  }
  else {out << "return" << std::endl;}
}

void ASTExpressionStatement::translate(std::ostream& out, TranslateContext &context) const
{
	context.isGlobal = false;
  context.printTabs(out);
  expression()->translate(out, context);
  out << std::endl;
}

void ASTSelectiveStatement::translate(std::ostream& out, TranslateContext &context) const
{
  context.printTabs(out);
		out << "if(";
		condition()->translate(out, context);
		out<<") ";
		out << ":" << std::endl;
		context.incTab();
		ifBranch()->translate(out, context);
		context.decTab();
		if (elseBranch()) {
			context.printTabs(out);
			out << "else:" << std::endl;
			context.incTab();
			elseBranch()->translate(out, context);
			context.decTab();
		}
}

void ASTLoopingStatement::translate(std::ostream& out, TranslateContext &context) const
{
context.printTabs(out);
out<< "while(";
condition()->translate(out, context);
out<<") ";
out << ":" << std::endl;
context.incTab();
body()->translate(out, context);
context.decTab();
}


//from program.hpp

void ASTProgram::translate(std::ostream& out, TranslateContext &context) const
{
	context.isGlobal = true;
  std::vector<ASTDeclaration*> decls = declarations();
  for(size_t i = 0; i<decls.size();i++){
    decls[i]->translate(out, context);
  }

}
