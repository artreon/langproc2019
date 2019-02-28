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
	CompileContext(size_t count): tabCount(count){}
	size_t        tabCount;






	 /*regs [31]= {"$zero","$at",
		 											"$v0","$v1",
													"$a0","$a1","$a2","$a3",
													"$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7",
													"$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7",
													"t8","$t9",
													"k0","$k1",
													"$gp","$sp","$fp",
													"$ra"};*/
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
