#include "brute.h"

using namespace std;

int Exhaustive::get_index(int n)
{
	if (n < term[0].length())
		return n;
	else if (n > term[0].length() && n <= term[0].length() + term[1].length())
		return n - term[0].length() - 1;
	else if (n > term[0].length() + term[1].length() + 1)
		return n - term[0].length() - term[1].length() - 2;
}

int Exhaustive::get_term(int n)
{
	if (n < term[0].length())
		return 0;
	else if (n > term[0].length() && n <= term[0].length() + term[1].length())
		return 1;
	else if (n > term[0].length() + term[1].length() + 1)
		return 2;
}

bool Exhaustive::found_result(void)
{
	switch (task)
	{
	case '+':	return atoi(term[0].c_str()) + atoi(term[1].c_str()) == atoi(term[2].c_str());
	case '-':	return atoi(term[0].c_str()) - atoi(term[1].c_str()) == atoi(term[2].c_str());
	case '*':	return atoi(term[0].c_str()) * atoi(term[1].c_str()) == atoi(term[2].c_str());
	case '/':	if (atoi(term[1].c_str()) == 0) return false; return atoi(term[0].c_str()) / atoi(term[1].c_str()) == atoi(term[2].c_str());
	}
	cout << "格式错误。" << endl;
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
				this->task = *it;
				operation = true;
				continue;
			}
			term[0] += *it;
		}
		else if (!equal_sign)
		{
			if (*it == '=')
			{
				equal_sign = true;
				continue;
			}
			term[1] += *it;
		}
		else
		{
			term[2] += *it;
		}
		if (isalpha(*it))
			unknown.push_back(it - str.begin());
	}
	return;
}

bool Exhaustive::check_duplicate(void)
{
	bool jump = false;
	for (int i = 0; i < unknown.size() - 1; i++)
	{
		if (jump)
			break;
		for (int j = i + 1; j < unknown.size(); j++)
		{
			if (!isdigit(term[get_term(unknown[i])][get_index(unknown[i])]))
			{
				jump = true;
				break;
			}
			if (term[get_term(unknown[i])][get_index(unknown[i])] == term[get_term(unknown[j])][get_index(unknown[j])])
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
	cout << "输入表达式，字母表示未知数。" << endl;
	getline(cin, expression);
	this->split(expression);
	cout << "输入取值表。" << endl;
	cin.get(ch);
	while (isdigit(ch))
	{
		range.push_back(ch - '0');
		cin.get(ch);
		while (ch == ' ')
			cin.get(ch);
	}
	cout << endl;
	cout << "请确认输入信息： " << endl;
	cout << "第一项： " << term[0] << endl;
	cout << "第二项： " << term[1] << endl;
	cout << "第三项： " << term[2] << endl;
	cout << "符号： " << task << endl;
	cout << "未知数： ";
	for (auto it = this->unknown.begin(); it != this->unknown.end(); it++)
	{
		cout << "第" << get_term(*it) + 1 << "项第" << get_index(*it) + 1 << "个" << " ";
	}
	cout << endl;
	cout << "取值范围: ";
	for (auto it = this->range.begin(); it != this->range.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	clock_t start_time, end_time;
	start_time = clock();
	crypt_auto(unknown.size() - 1);
	end_time = clock();
	cout << "穷举用时： " << (static_cast<double>(end_time) - static_cast<double>(start_time)) / CLOCKS_PER_SEC << " 秒";
	cout << endl;

	return;
}