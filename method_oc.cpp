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
	else if (op == '(')		//ȷ�����������������ᴥ������
		return 0;
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
			
			size_t index = 0;
			size_t i = 0;
			while (expression[index] == '(')	//��ǰ�ַ�Ϊ'('��ѹ�������ջ����������
			{
				index++;
				m_operator.push('(');
			}
			m_operand.push(stod(expression.substr(index), &i));	//��һ����ֵѹ��ջ������i�ᱻ���ĳ���ֵ��һλ
			index += i;

			while (true)
			{
				m_operator.push(expression[index++]);	//ѹ��һ��������������Լ�1

				while (expression[index] == '(')
				{
					index++;
					m_operator.push('(');
				}
				 
				m_operand.push(stod(expression.substr(index), &i));	//ѹ����һ����ֵ��substrȡ����index������ַ���������i�ᱻ�ĳ����ַ���ȡֵ��һλ
				index += i;		//�ַ������� + ���ַ������� = Ŀǰλ��

				while (expression[index] == ')')
				{
					index++;
					while (m_operator.top() != '(')	//��������'('֮ǰ������
					{
						execute(m_operator, m_operand);
					}
					m_operator.pop();	//ɾ��'('
				}

				if (index == expression.length())	//�ַ�������Խ��ĩβ
				{
					while (!m_operator.empty())	//ֻҪ�����������Ϊ�գ��ظ�ִ������
					{
						execute(m_operator, m_operand);
					}
					break;	//������ѭ��
				}
				//ֻҪ�����������Ϊ�գ�����ǰ��������ȼ���������������������ִ������
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