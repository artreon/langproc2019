#pragma once

#include "expressions.hpp"
#include "statements.hpp"
#include <iostream>
#include <vector>

class ASTType : public ASTNode
{
public:
	enum Type {
		Void,
		Int,
		Char,
		Pointer
	};

	~ASTType(){}
	ASTType() = delete;
	ASTType(const ASTType &) = delete;

	ASTType(Type type, ASTType* pointerTo = nullptr)
		: _type(type), _pointer(pointerTo)
	{
		if (pointerTo && type != Pointer)
			throw std::runtime_error("Pointer!");
	}

	Type t() const { return _type; }
	ASTType* pointerTo() const { return _pointer; }

	 void translate(std::ostream& out, TranslateContext &context) const override;
	 void codegen(std::ostream& out, CompileContext &context) const override;


private:
	Type _type;
	ASTType* _pointer;
};

class ASTDeclaration : public ASTNode
{
private:
	std::string _name;
	ASTType*    _type;


public:
	~ASTDeclaration(){}
	ASTDeclaration() = delete;
	ASTDeclaration(const ASTDeclaration &) = delete;

	ASTDeclaration(const std::string& name, ASTType* type)
		: _name(name), _type(type)
	{
		if (name.empty())
			throw std::runtime_error("Name can not be empty");
	}

	ASTType* type() const { return _type; }
	std::string name() const { return _name; }


};

using ASTGlobalDeclarations = std::vector<ASTDeclaration*>;

class ASTVariableDecl : public ASTDeclaration
{
private:
	ASTExpression* _initializer;

public:
	~ASTVariableDecl(){}
	ASTVariableDecl(const std::string& name, ASTType* type, ASTExpression* initializer = nullptr)
		: ASTDeclaration(name, type), _initializer(initializer)
	{
		if (type->t() == ASTType::Void)
			throw std::runtime_error("Variable type can not be void");
	}

	ASTExpression* initializer() const { return _initializer; }

 void translate(std::ostream& out, TranslateContext &context) const override;
 void codegen(std::ostream& out, CompileContext &context) const override;



};

class ASTArgumentDecl : public ASTVariableDecl
{
public:
	~ASTArgumentDecl(){}
	ASTArgumentDecl(const std::string& name, ASTType* type)
		: ASTVariableDecl(name, type){}


	 void translate(std::ostream& out, TranslateContext &context) const override;
	 void codegen(std::ostream& out, CompileContext &context) const override;

};


using ASTArgumentsFormal = std::vector<ASTArgumentDecl*>;

class ASTFunctionDecl : public ASTDeclaration
{
private:
	ASTArgumentsFormal _args;
	ASTBlock*          _body;


public:
	~ASTFunctionDecl(){}
	ASTFunctionDecl(const std::string& name, ASTType* type, ASTArgumentsFormal args, ASTBlock* body = nullptr)
		: ASTDeclaration(name, type), _args(args), _body(body)
	{}

	ASTArgumentsFormal arguments() const { return _args; }
	ASTBlock* body() const { return _body; }

	 void translate(std::ostream& out, TranslateContext &context) const override;
	 void codegen(std::ostream& out, CompileContext &context) const override;


};
