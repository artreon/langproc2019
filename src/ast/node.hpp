#pragma once

#include <typeinfo>
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>
#include <map>



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
	//void incTab();
	//void decTab();
	std::vector<std::string> globals;
	bool          isGlobal;
	bool					callerFunc;
	std::string				variable_used;
	int 					frame_val;//IDG HOW THIS WORKS TBF
	int						offset;
	std::map<std::string, int> variable_locations;//in mem
	int used_regs[2][22]= {
		{4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25},
		{0,0,0,0,0,0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 }
	};
											 					/*reg no, in use?
																reg no: 0-always 0
																reg no: 2,3 - return values
																reg no: 4-7 - arguments
																reg no: 8-15 - temps (callers job to save if needed)
																reg no: 16-23 - callee needs to save
																reg_no: 24,25 - temps
																rest are the pointers */
	int get_temp_reg(int used_reg[2][22]);
	void free_temp_regs(int used_reg[2][22]);
	void use_temp_reg(int used_reg[2][22]);


};


class ASTNode
{
public:
	virtual ~ASTNode()
	{}


	virtual void translate(std::ostream& out, TranslateContext &context) const=0;

	virtual void codegen(std::ostream& out, CompileContext &context) const=0;
};
