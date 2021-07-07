#include "powercalc.h"

using namespace std;

inline int ordinary_calc::precedence(const char op)
{
	if (op == '+' || op == '-')
		return 1;
	else if (op == '*' || op == '/')
		return 2;
	else if (op == '^')
		return 3;
	else if (op == '(')		//确保它后面的运算符不会触发运算
		return 0;
	throw runtime_error{ string{"Invalid operator: "} + op };
}

void ordinary_calc::process(void)
{
	string expression;
	cout << "输入完整表达式。" << endl;

	try
	{
		while (true)
		{
			cout << "空行结束。" << endl;
			getline(cin, expression, '\n');	//第三个参数显式声明截断字符

			if (expression.empty())	break;	//空行退出死循环

			expression.erase(remove(begin(expression), end(expression), ' '), end(expression));	//删除该string里面所有的空格
			
			size_t index = 0;
			size_t i = 0;
			while (expression[index] == '(')	//当前字符为'('则压入运算符栈，递增索引
			{
				index++;
				m_operator.push('(');
			}
			m_operand.push(stod(expression.substr(index), &i));	//第一个数值压入栈，索引i会被更改成数值后一位
			index += i;

			while (true)
			{
				m_operator.push(expression[index++]);	//压入一个运算符，索引自加1

				while (expression[index] == '(')
				{
					index++;
					m_operator.push('(');
				}
				 
				m_operand.push(stod(expression.substr(index), &i));	//压入下一个数值，substr取索引index后的子字符串，索引i会被改成子字符串取值后一位
				index += i;		//字符串索引 + 子字符串索引 = 目前位置

				while (expression[index] == ')')
				{
					index++;
					while (m_operator.top() != '(')	//结算所有'('之前的运算
					{
						execute(m_operator, m_operand);
					}
					m_operator.pop();	//删除'('
				}

				if (index == expression.length())	//字符串索引越过末尾
				{
					while (!m_operator.empty())	//只要运算符容器不为空，重复执行运算
					{
						execute(m_operator, m_operand);
					}
					break;	//跳出死循环
				}
				//只要运算符容器不为空，若当前运算符优先级不高于容器顶部，反复执行运算
				while (!m_operator.empty() && precedence(expression[index]) <= precedence(m_operator.top()))
					execute(m_operator, m_operand);
			}
			cout << "运算结果 = " << m_operand.top() << endl;
		}
	}
	catch (const exception& e)
	{
		cerr << e.what() << endl;
	}
	cout << "运算结束。" << endl;
}