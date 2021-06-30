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
	map<char, vector<int>> m_variable;	//����������������ǵ��±꼯
	vector<char> m_key;	//��������б��Թ�����map
	vector<int> m_range;	//����ȡֵ��
	char m_task;	//����'+' '-' '*' '/'
	string m_term[3];	//��������
	bool solved;
public:
	Exhaustive();	//���캯����Ϊsolved�ṩ��ʼֵfalse
	void split(string str);	//�����ʽ��ֳ��������term�У������Ŵ�����task�У������������±꼯������variable�У��ؼ��ִ�����m_key�С�
	void process(void);	//��ȡ�û����룬�ṩȷ����Ϣ������¼��ٺķѵ�ʱ�䡣
	int get_index(int n);	//����variable������±꣬����n��Ӧterm[?][n]
	int get_term(int n);	//����variable������±꣬����n��Ӧterm[n][?]
	bool found_result(void);	//�ж�term[0]�Ӽ��˳�term[1]�Ƿ����term[2]
	bool check_duplicate(int n);	//�ж�ȡֵ�Ƿ��ظ�
	void crypt_auto(int n);	//�ݹ�ʵ�ֶ�̬����forǶ�ײ���,ÿһ����������range��������п��ܣ�ֱ�����ʽ������
};