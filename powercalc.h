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
	map<char, vector<int>> m_variable;	//����������������ǵ��±꼯
	vector<char> m_key;	//��������б��Թ�����map
	vector<int> m_range;	//����ȡֵ��
	char m_task;	//����'+' '-' '*' '/'
	string m_term[3];	//��������
	bool lead_zero();	//�ж���û����һ����0��ͷ
	bool solved;
	int get_index(int n);	//����variable������±꣬����n��Ӧterm[?][n]
	int get_term(int n);	//����variable������±꣬����n��Ӧterm[n][?]
	bool found_result(void);	//�ж�term[0]�Ӽ��˳�term[1]�Ƿ����term[2]
	bool check_duplicate(int n);	//�ж�ȡֵ�Ƿ��ظ�
	void crypt_auto(int n);	//�ݹ�ʵ�ֶ�̬����forǶ�ײ���,ÿһ����������range��������п��ܣ�ֱ�����ʽ������
	void split(string str);	//�����ʽ��ֳ��������term�У������Ŵ�����task�У������������±꼯������variable�У��ؼ��ִ�����m_key�С�
public:
	Exhaustive();	//���캯����Ϊsolved�ṩ��ʼֵfalse
	void process(void);	//��ȡ�û����룬�ṩȷ����Ϣ������¼��ٺķѵ�ʱ�䡣
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
	vector<string> m_equation;	//�����û�����
	vector<vector<Term>> m_term;	//Term������ķ��š�ϵ����������term[n]�����n�����̵�������
	vector<vector<double>> m_determinant;	//ϵ������ʽ	'D'
	double m_denominator;	//����ϵ������ʽ�Ľ⣬�����������˷�����
	vector<vector<double>> m_temp_deter;	//��ʱ���� 'Dj'
	vector<double> m_solution;	//����⣬��������
	vector<char> order;	//������
	vector<double> const_term;	//������
	
	double decode(const Term* c);	//���������ţ�����ϵ��
	void sum_liked_term(Term* a, Term* b);	//�ϲ�ͬ���������a
	Term* dup_variable(int n, char ch);	//��������û��ͬ��������򷵻�����ָ�룬���򷵻�nullptr
	bool is_linear(void);	//�ж��Ƿ�Ϊ���Է�����
	void format(void);	//��equation������������ÿһ��ϲ������Ƶ���ʽ�ұߣ�ȷ����ʽ�������Է����飬��������format��
	void mk_det(void);	//����format������ϵ������ʽ
	void convert(int j);	//��ϵ������ʽ�ĵ�j�и�Ϊ�������ʽ�ұߵĳ�����������temp_deter
	bool check(void);	//��������������󣬽��𰸴���ԭʽ��������Ƿ���ȷ��
	void cramer_rule(void);	//����ķ����Xn = Dn/D
public:
	Equation();	//���캯��
	void process(void);	//��ȡ�û����룬�ṩȷ����Ϣ������¼����ʱ��
};

class Determinant
{
private:
	void swap(vector<int>& idx, int i, int j);	//�����±��б������Ԫ��
	void permutation(vector<int>& ini, vector<vector<int>>& result, int current);	//ȫ���д�����result
	vector<int> inivec(int n);	//���ɳ�ʼ�±��б�
	bool is_even(int num);	//�ж��Ƿ�Ϊż��
	bool term_positive(vector<int>& seq);	//ͨ���������ж����Ƿ�Ϊ��
public:
	double calc(vector<vector<double>> deter, int n);	//ȫ�����������ʽ
	void process(void);	//�ӿ�
};