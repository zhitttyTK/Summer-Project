#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>
using namespace std;

class Exhaustive
{
private:
	vector<int> m_unknown;	//储存未知数在表达式的下标
	vector<int> m_range;	//储存取值表
	char m_task;	//储存'+' '-' '*' '/'
	string m_term[3];	//储存三项
public:
	void split(string str);	//将表达式拆分成三项储存在term中，将符号储存在task中，将未知数下标储存在vector<int>unknown中
	void process(void);	//获取用户输入，提供确认信息，并记录穷举耗费的时间。
	int get_index(int n);	//解析vector<int>unknown储存的下标，返回n对应term[?][n]
	int get_term(int n);	//解析vector<int>unknown储存的下标，返回n对应term[n][?]
	bool found_result(void);	//判断term[0]加减乘除term[1]是否等于term[2]
	bool check_duplicate(void);	//判断取值是否重复
	void crypt_auto(int n);	//递归实现动态决定for嵌套层数,每一个未知数遍历range储存的所有可能，直至表达式成立。
};