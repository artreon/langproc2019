#pragma once

#include "declarations.hpp"

class ASTProgram : public ASTNode
{
private:
	ASTGlobalDeclarations _decls;


public:
	~ASTProgram(){}
	ASTProgram() = delete;
	ASTProgram(const ASTProgram &) = delete;

	ASTProgram(ASTGlobalDeclarations decls)
		: _decls(decls){}

	ASTGlobalDeclarations declarations() const { return _decls; }

	 void translate(std::ostream& out, TranslateContext &context) const override;

	 void codegen(std::ostream& out, CompileContext &context) const override;

};
