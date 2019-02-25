#pragma once

#include <typeinfo>
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>



class TranslateContext{
public:
	~TranslateContext(){}
	TranslateContext(size_t count): tabCount(count){}
	void printTabs(std::ostream& out);
	void incTab();
	void decTab();
	size_t        tabCount;
	std::vector<std::string> globals;
	bool          isGlobal;

};

class CompileContext{
public:
	~CompileContext(){}
	//REGS AND STUFF??????
};


class ASTNode
{
public:
	virtual ~ASTNode()
	{}


	virtual void translate(std::ostream& out, TranslateContext &context) const=0;

	virtual void codegen(std::ostream& out, CompileContext &context) const=0;
};
