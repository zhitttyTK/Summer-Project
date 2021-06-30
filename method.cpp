#include "brute.h"

using namespace std;

int Exhaustive::get_index(int n)
{
	if (n < m_term[0].length())
		return n;
	else if (n > m_term[0].length() && n <= m_term[0].length() + m_term[1].length())
		return n - m_term[0].length() - 1;
	else if (n > m_term[0].length() + m_term[1].length() + 1)
		return n - m_term[0].length() - m_term[1].length() - 2;
}

int Exhaustive::get_term(int n)
{
	if (n < m_term[0].length())
		return 0;
	else if (n > m_term[0].length() && n <= m_term[0].length() + m_term[1].length())
		return 1;
	else if (n > m_term[0].length() + m_term[1].length() + 1)
		return 2;
}

bool Exhaustive::found_result(void)
{
	switch (m_task)
	{
	case '+':	return atoi(m_term[0].c_str()) + atoi(m_term[1].c_str()) == atoi(m_term[2].c_str());
	case '-':	return atoi(m_term[0].c_str()) - atoi(m_term[1].c_str()) == atoi(m_term[2].c_str());
	case '*':	return atoi(m_term[0].c_str()) * atoi(m_term[1].c_str()) == atoi(m_term[2].c_str());
	case '/':	if (atoi(m_term[1].c_str()) == 0) return false; return atoi(m_term[0].c_str()) / atoi(m_term[1].c_str()) == atoi(m_term[2].c_str());
	}
	cout << "��ʽ����" << endl;
	exit(EXIT_FAILURE);
}

void Exhaustive::split(string str)
{
	bool operation = false;
	bool equal_sign = false;
	for (string::iterator it = str.begin(); it != str.end(); it++)
	{
		if (!operation)
		{
			if (*it == '+' || *it == '-' || *it == '*' || *it == '/')
			{
				this->m_task = *it;
				operation = true;
				continue;
			}
			m_term[0] += *it;
		}
		else if (!equal_sign)
		{
			if (*it == '=')
			{
				equal_sign = true;
				continue;
			}
			m_term[1] += *it;
		}
		else
		{
			m_term[2] += *it;
		}
		if (isalpha(*it))
			m_unknown.push_back(it - str.begin());
	}
	return;
}

bool Exhaustive::check_duplicate(void)
{
	bool jump = false;
	for (int i = 0; i < m_unknown.size() - 1; i++)
	{
		if (jump)
			break;
		for (int j = i + 1; j < m_unknown.size(); j++)
		{
			if (!isdigit(m_term[get_term(m_unknown[i])][get_index(m_unknown[i])]))
			{
				jump = true;
				break;
			}
			if (m_term[get_term(m_unknown[i])][get_index(m_unknown[i])] == m_term[get_term(m_unknown[j])][get_index(m_unknown[j])])
			{
				return true;
			}
		}
	}
	return false;
}

void Exhaustive::process(void)
{
	string expression;
	char ch;
	cout << "������ʽ����ĸ��ʾδ֪����" << endl;
	getline(cin, expression);
	this->split(expression);
	cout << "����ȡֵ��" << endl;
	cin.get(ch);
	while (isdigit(ch))
	{
		m_range.push_back(ch - '0');
		cin.get(ch);
		while (ch == ' ')
			cin.get(ch);
	}
	cout << endl;
	cout << "��ȷ��������Ϣ�� " << endl;
	cout << "��һ� " << m_term[0] << endl;
	cout << "�ڶ�� " << m_term[1] << endl;
	cout << "����� " << m_term[2] << endl;
	cout << "���ţ� " << m_task << endl;
	cout << "δ֪���� ";
	for (auto it = this->m_unknown.begin(); it != this->m_unknown.end(); it++)
	{
		cout << "��" << get_term(*it) + 1 << "���" << get_index(*it) + 1 << "��" << " ";
	}
	cout << endl;
	cout << "ȡֵ��Χ: ";
	for (auto it = this->m_range.begin(); it != this->m_range.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	clock_t start_time, end_time;
	start_time = clock();
	crypt_auto(m_unknown.size() - 1);
	end_time = clock();
	cout << "�����ʱ�� " << (static_cast<double>(end_time) - static_cast<double>(start_time)) / CLOCKS_PER_SEC << " ��";
	cout << endl;

	return;
}