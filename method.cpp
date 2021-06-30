#include "brute.h"

using namespace std;

Exhaustive::Exhaustive()
{
	m_task = '#';
	solved = false;
}

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
	cout << "未知错误。" << endl;
	exit(EXIT_FAILURE);
}

void Exhaustive::split(string str)
{
	bool operation = false;
	bool equal_sign = false;
	bool key_dup = false;
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
		{
			key_dup = false;
			m_variable[*it].push_back(it - str.begin());
			for (auto itr = m_key.begin(); itr != m_key.end(); itr++)
			{
				if (*itr == *it)
				{
					key_dup = true;
					break;
				}
			}
			if (key_dup == false)
				m_key.push_back(*it);
		}
	}
	return;
}

bool Exhaustive::check_duplicate(int n)	//递归最外层直接返回false，下一层比较0 1，再下一层比较0 2和1 2，以此类推直至最内层比较全部
{
	if (n == 0)
		return false;

	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			if (m_term[get_term(m_variable.find(m_key[i])->second[0])][get_index(m_variable.find(m_key[i])->second[0])] == m_term[get_term(m_variable.find(m_key[j])->second[0])][get_index(m_variable.find(m_key[j])->second[0])])
				return true;
		}
	}
	return false;
}

bool Exhaustive::lead_zero(void)
{
	if (m_term[0][0] == '0' || m_term[1][0] == '0' || m_term[2][0] == '0')
		return true;
	return false;
}

void Exhaustive::process(void)
{
	string expression;
	char ch;
	cout << "输入表达式，字母表示未知数。" << endl;
	getline(cin, expression);
	this->split(expression);
	cout << "输入取值表。" << endl;
	cin.get(ch);
	while (isdigit(ch))
	{
		m_range.push_back(ch - '0');
		cin.get(ch);
		while (ch == ' ')
			cin.get(ch);
	}
	cout << endl;
	cout << "请确认输入信息： " << endl;
	cout << "第一项： " << m_term[0] << endl;
	cout << "第二项： " << m_term[1] << endl;
	cout << "第三项： " << m_term[2] << endl;
	cout << "符号： " << m_task << endl;
	cout << endl;
	cout << "未知数：" << endl;
	for (auto it = m_variable.begin(); it != m_variable.end(); it++)
	{
		cout << "变量 " << it->first << " 位于：";
		for (auto itr = it->second.begin(); itr != it->second.end(); itr++)
		{
			cout << "第" << get_term(*itr) + 1 << "项 " << "第" << get_index(*itr) + 1 << "位  ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "取值范围: ";
	for (auto it = this->m_range.begin(); it != this->m_range.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	cout << endl;
	clock_t start_time, end_time;
	start_time = clock();
	crypt_auto(m_variable.size() - 1);
	end_time = clock();
	cout << "穷举用时： " << (static_cast<double>(end_time) - static_cast<double>(start_time)) / CLOCKS_PER_SEC << " 秒";
	cout << endl;

	return;
}