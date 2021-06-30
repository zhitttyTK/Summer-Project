#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>
#include <map>

using namespace std;

class Exhaustive
{
private:
	map<char, vector<int>> m_variable;	//储存变量名，及它们的下标集
	vector<char> m_key;	//储存变量列表以供访问map
	vector<int> m_range;	//储存取值表
	char m_task;	//储存'+' '-' '*' '/'
	string m_term[3];	//储存三项
	bool solved;
public:
	Exhaustive();	//构造函数，为solved提供初始值false
	void split(string str);	//将表达式拆分成三项储存在term中，将符号储存在task中，将变量名和下标集储存在variable中，关键字储存在m_key中。
	void process(void);	//获取用户输入，提供确认信息，并记录穷举耗费的时间。
	int get_index(int n);	//解析variable储存的下标，返回n对应term[?][n]
	int get_term(int n);	//解析variable储存的下标，返回n对应term[n][?]
	bool found_result(void);	//判断term[0]加减乘除term[1]是否等于term[2]
	bool check_duplicate(int n);	//判断取值是否重复
	void crypt_auto(int n);	//递归实现动态决定for嵌套层数,每一个变量遍历range储存的所有可能，直至表达式成立。
};