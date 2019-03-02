#pragma once

#include "node.hpp"

#include <string>
#include <vector>


class ASTExpression : public ASTNode
{
public:
	enum Type {
		BinaryExpression,
		Variable,
		Constant,
		FunctionCall
	};
	~ASTExpression(){}
	ASTExpression() = delete;
	ASTExpression(const ASTExpression &) = delete;

	ASTExpression(Type type)
	: _type(type){}

	Type type() const { return _type; }

private:
	Type _type;
};

class ASTBinaryExpression : public ASTExpression
{
public:
	enum Operator {
		OpAdd,
		OpSub,
		OpMul,
		OpDiv,
		OpMod,
		OpLess,
		OpLessOrEqual,
		OpGreater,
		OpGreaterOrEqual,
		OpEqual,
		OpNotEqual,
		OpLogicAnd,
		OpLogicOr,
		OpAssign
	};
	~ASTBinaryExpression(){}
	ASTBinaryExpression(ASTExpression* leftOperand, ASTExpression* rightOperand, Operator op)
		: ASTExpression(ASTExpression::BinaryExpression), _left(leftOperand), _right(rightOperand), _op(op)
	{}

	int priority() const
	{
		switch (_op) {
			case OpAssign:
				return 0;

			case OpLogicOr:
				return 1;

			case OpLogicAnd:
				return 2;

			case OpLess:
			case OpLessOrEqual:
			case OpGreater:
			case OpGreaterOrEqual:
			case OpEqual:
			case OpNotEqual:
				return 3;

			case OpAdd:
			case OpSub:
				return 4;

			default:
				return 5;
		}
	}

	Operator op() const { return _op; }
	ASTExpression* left() const { return _left; }
	ASTExpression* right() const { return _right; }

	 void translate(std::ostream& out, TranslateContext &context) const override;
	 void codegen(std::ostream& out, CompileContext &context) const override;


private:
	ASTExpression* _left;
	ASTExpression* _right;
	Operator       _op;
};






class ASTVariable : public ASTExpression
{
private:
	std::string _name;


public:
	~ASTVariable(){}
	ASTVariable(const std::string& name)
		: ASTExpression(ASTExpression::Variable), _name(name){}

	std::string name() const { return _name; }

	 void translate(std::ostream& out, TranslateContext &context) const override;
	 void codegen(std::ostream& out, CompileContext &context) const override;


};




class ASTConstant : public ASTExpression
{
private:
	std::string _value;

public:
	~ASTConstant(){}
	ASTConstant(const std::string& value)
		: ASTExpression(ASTExpression::Constant), _value(value){}

	std::string value() const { return _value; }

	 void translate(std::ostream& out, TranslateContext &context) const override;
	 void codegen(std::ostream& out, CompileContext &context) const override;



};

using ASTArgumentsList = std::vector<ASTExpression*>;

class ASTFunctionCall : public ASTExpression
{
private:
	std::string _name;
	ASTArgumentsList _args;


public:
	~ASTFunctionCall(){}
	ASTFunctionCall(const std::string& name, ASTArgumentsList args)
		: ASTExpression(ASTExpression::FunctionCall), _name(name), _args(args)
	{
		if (name.empty())
			throw std::runtime_error("Name can not be empty");
	}

	ASTArgumentsList arguments() const { return _args; }
	std::string name() const { return _name; }

	void translate(std::ostream& out, TranslateContext &context) const override;
	void codegen(std::ostream& out, CompileContext &context) const override;



};
