#include "powercalc.h"

using namespace std;

int ordinary_calc::precedence(const char op)
{
	if (op == '+' || op == '-')
		return 1;
	else if (op == '*' || op == '/')
		return 2;
	else if (op == '^')
		return 3;
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
			
			size_t index;
			m_operand.push(stod(expression, &index));	//第一个数值压入栈，索引index会被更改成数值后一位

			while (true)
			{
				m_operator.push(expression[index++]);	//压入一个运算符，索引自加1
				 
				size_t i;
				m_operand.push(stod(expression.substr(index), &i));	//压入下一个数值，substr取索引index后的子字符串，索引i会被改成子字符串取值后一位
				index += i;		//字符串索引 + 子字符串索引 = 目前位置

				if (index == expression.length())	//字符串索引到达末尾
				{
					while (!m_operator.empty())	//只要运算符容器不为空，重复执行execute
					{
						execute(m_operator, m_operand);
					}
					break;	//跳出死循环
				}
				//只要运算符容器不为空，并且当前运算符优先级不高于容器顶部，反复执行execute
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