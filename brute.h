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
	vector<int> m_unknown;	//����δ֪���ڱ��ʽ���±�
	vector<int> m_range;	//����ȡֵ��
	char m_task;	//����'+' '-' '*' '/'
	string m_term[3];	//��������
public:
	void split(string str);	//�����ʽ��ֳ��������term�У������Ŵ�����task�У���δ֪���±괢����vector<int>unknown��
	void process(void);	//��ȡ�û����룬�ṩȷ����Ϣ������¼��ٺķѵ�ʱ�䡣
	int get_index(int n);	//����vector<int>unknown������±꣬����n��Ӧterm[?][n]
	int get_term(int n);	//����vector<int>unknown������±꣬����n��Ӧterm[n][?]
	bool found_result(void);	//�ж�term[0]�Ӽ��˳�term[1]�Ƿ����term[2]
	bool check_duplicate(void);	//�ж�ȡֵ�Ƿ��ظ�
	void crypt_auto(int n);	//�ݹ�ʵ�ֶ�̬����forǶ�ײ���,ÿһ��δ֪������range��������п��ܣ�ֱ�����ʽ������
};