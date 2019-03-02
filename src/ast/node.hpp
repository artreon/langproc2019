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
	int						reg_no;
	int 					frame_val;//IDG HOW THIS WORKS TBF
	int						offset;
	std::map<std::string, int> variable_locations;

};


class ASTNode
{
public:
	virtual ~ASTNode()
	{}


	virtual void translate(std::ostream& out, TranslateContext &context) const=0;

	virtual void codegen(std::ostream& out, CompileContext &context) const=0;
};
