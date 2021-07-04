#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>
#include <map>
#include <cmath>
#include <iomanip>

using namespace std;

class Exhaustive
{
private:
	map<char, vector<int>> m_variable;	//储存变量名，及它们的下标集
	vector<char> m_key;	//储存变量列表以供访问map
	vector<int> m_range;	//储存取值表
	char m_task;	//储存'+' '-' '*' '/'
	string m_term[3];	//储存三项
	bool lead_zero();	//判断有没有哪一项以0开头
	bool solved;
	int get_index(int n);	//解析variable储存的下标，返回n对应term[?][n]
	int get_term(int n);	//解析variable储存的下标，返回n对应term[n][?]
	bool found_result(void);	//判断term[0]加减乘除term[1]是否等于term[2]
	bool check_duplicate(int n);	//判断取值是否重复
	void crypt_auto(int n);	//递归实现动态决定for嵌套层数,每一个变量遍历range储存的所有可能，直至表达式成立。
	void split(string str);	//将表达式拆分成三项储存在term中，将符号储存在task中，将变量名和下标集储存在variable中，关键字储存在m_key中。
public:
	Exhaustive();	//构造函数，为solved提供初始值false
	void process(void);	//获取用户输入，提供确认信息，并记录穷举耗费的时间。
};

struct Term
{
	char op;
	double coefficient;
	char variable;
};

class Equation
{
private:
	vector<string> m_equation;	//储存用户输入
	vector<vector<Term>> m_term;	//Term储存项的符号、系数、变量，term[n]储存第n个方程的所有项
	vector<vector<double>> m_determinant;	//系数行列式	'D'
	double m_denominator;	//储存系数行列式的解，避免多次运算浪费性能
	vector<vector<double>> m_temp_deter;	//临时储存 'Dj'
	vector<double> m_solution;	//储存解，用于验算
	vector<char> order;	//变量表
	vector<double> const_term;	//常量表
	
	double decode(const Term* c);	//解析正负号，返回系数
	void sum_liked_term(Term* a, Term* b);	//合并同类项，储存在a
	Term* dup_variable(int n, char ch);	//检查该行有没有同类项，如有则返回它的指针，否则返回nullptr
	bool is_linear(void);	//判断是否为线性方程组
	void format(void);	//将equation按变量名排序每一项，合并常量移到等式右边，确保格式符合线性方程组，并储存在format中
	void mk_det(void);	//解析format，生成系数行列式
	void convert(int j);	//将系数行列式的第j列改为方程组等式右边的常量，储存在temp_deter
	bool check(void);	//在所有运算结束后，将答案代入原式，检查结果是否正确。
	void cramer_rule(void);	//克莱姆法则，Xn = Dn/D
public:
	Equation();	//构造函数
	void process(void);	//获取用户输入，提供确认信息，并记录计算时间
};

class Determinant
{
private:
	void swap(vector<int>& idx, int i, int j);	//交换下标列表的两个元素
	void permutation(vector<int>& ini, vector<vector<int>>& result, int current);	//全排列储存在result
	vector<int> inivec(int n);	//生成初始下标列表
	bool is_even(int num);	//判断是否为偶数
	bool term_positive(vector<int>& seq);	//通过逆序数判断幂是否为正
public:
	double calc(vector<vector<double>> deter, int n);	//全排列求解行列式
	void process(void);	//接口
};