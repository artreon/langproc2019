#pragma once

#include "expressions.hpp"
#include <vector>

using ASTStatementList = std::vector<ASTNode*>;

class ASTBlock : public ASTNode
{
private:
	ASTStatementList _statements;

public:
	~ASTBlock(){}
	ASTBlock() = delete;
	ASTBlock(const ASTBlock &) = delete;


	ASTBlock(ASTStatementList statements)
		: _statements(statements){}

	ASTStatementList statements() const { return _statements; }
	bool emptyBlock(ASTStatementList statements) const;

	void translate(std::ostream& out, TranslateContext &context) const override;
	 void codegen(std::ostream& out, CompileContext &context) const override;


};

class ASTReturnStatement : public ASTNode
{
private:
	ASTExpression* _expr;

public:
	~ASTReturnStatement(){}
	ASTReturnStatement(const ASTReturnStatement &) = delete;

	ASTReturnStatement(ASTExpression* expr = nullptr)
		: _expr(expr){}

	ASTExpression* expression() const { return _expr; }

	 void translate(std::ostream& out, TranslateContext &context) const override;
	 void codegen(std::ostream& out, CompileContext &context) const override;


};

class ASTExpressionStatement : public ASTNode
{
private:
	ASTExpression* _expr;

public:
	~ASTExpressionStatement(){}
	ASTExpressionStatement() = delete;
	ASTExpressionStatement(const ASTExpressionStatement &) = delete;

	ASTExpressionStatement(ASTExpression* expr)
		: _expr(expr){}

	ASTExpression* expression() const { return _expr; }

	 void translate(std::ostream& out, TranslateContext &context) const override;
	 void codegen(std::ostream& out, CompileContext &context) const override;


};

class ASTSelectiveStatement : public ASTNode
{
private:
	ASTExpression* _condition;
	ASTNode*       _if;
	ASTNode*       _else;

public:
	~ASTSelectiveStatement(){}
	ASTSelectiveStatement() = delete;
	ASTSelectiveStatement(const ASTSelectiveStatement &) = delete;

	ASTSelectiveStatement(ASTExpression* condition, ASTNode* ifBranch, ASTNode* elseBranch = nullptr)
		: _condition(condition), _if(ifBranch), _else(elseBranch){}

	ASTExpression* condition() const { return _condition; }
	ASTNode* ifBranch() const { return _if; }
	ASTNode* elseBranch() const { return _else; }

	void translate(std::ostream& out, TranslateContext &context) const override;
	void codegen(std::ostream& out, CompileContext &context) const override;


};

class ASTLoopingStatement : public ASTNode
{
private:
	ASTExpression* _condition;
	ASTBlock* _block;

public:
	~ASTLoopingStatement(){}
	ASTLoopingStatement() = delete;
	ASTLoopingStatement(const ASTLoopingStatement &) = delete;

	ASTLoopingStatement(ASTExpression* condition, ASTBlock* block)
	: _condition(condition), _block(block){}

	ASTBlock* body() const {return _block;}
	ASTExpression* condition() const {return _condition;}

	void translate(std::ostream& out, TranslateContext &context) const override;
	void codegen(std::ostream& out, CompileContext &context) const override;

};
