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
	cout << "�����������ʽ��" << endl;

	try
	{
		while (true)
		{
			cout << "���н�����" << endl;
			getline(cin, expression, '\n');	//������������ʽ�����ض��ַ�

			if (expression.empty())	break;	//�����˳���ѭ��

			expression.erase(remove(begin(expression), end(expression), ' '), end(expression));	//ɾ����string�������еĿո�
			
			size_t index;
			m_operand.push(stod(expression, &index));	//��һ����ֵѹ��ջ������index�ᱻ���ĳ���ֵ��һλ

			while (true)
			{
				m_operator.push(expression[index++]);	//ѹ��һ��������������Լ�1
				 
				size_t i;
				m_operand.push(stod(expression.substr(index), &i));	//ѹ����һ����ֵ��substrȡ����index������ַ���������i�ᱻ�ĳ����ַ���ȡֵ��һλ
				index += i;		//�ַ������� + ���ַ������� = Ŀǰλ��

				if (index == expression.length())	//�ַ�����������ĩβ
				{
					while (!m_operator.empty())	//ֻҪ�����������Ϊ�գ��ظ�ִ��execute
					{
						execute(m_operator, m_operand);
					}
					break;	//������ѭ��
				}
				//ֻҪ�����������Ϊ�գ����ҵ�ǰ��������ȼ���������������������ִ��execute
				while (!m_operator.empty() && precedence(expression[index]) <= precedence(m_operator.top()))
					execute(m_operator, m_operand);
			}
			cout << "������ = " << m_operand.top() << endl;
		}
	}
	catch (const exception& e)
	{
		cerr << e.what() << endl;
	}
	cout << "���������" << endl;
}