#include "powercalc.h"

using namespace std;


void Equation::process(void)
{
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);
	char ch;
	vector<char> temp;
	string temp1;
	int term_idx;
	cout << "输入方程组，空行'#'结束。" << endl;
	cin.get(ch);
	while (ch != '#')
	{
		if (ch == '\n')
		{
			temp1.assign(temp.begin(), temp.end());
			temp.clear();
			m_equation.push_back(temp1);
		}
		else if (ch == ' ')
		{
			cin.get(ch);
			continue;
		}
		else
		{
			temp.push_back(ch);
		}
		cin.get(ch);
	}
	format();
	cout << endl;
	cout << "整理完成，请确认：" << endl;
	for (int i = 0; i < m_term.size(); i++)
	{
		cout << "  |";
		for (term_idx = 0; term_idx < m_term[i].size() - 1; term_idx++)
		{
			cout << m_term[i][term_idx].op << m_term[i][term_idx].coefficient << m_term[i][term_idx].variable << " ";
		}
		cout << "= " << decode(&m_term[i][term_idx]) << endl;
	}
	cout << endl;
	mk_det();
	cout << "系数行列式为：" << endl;
	for (int i = 0; i < m_determinant.size(); i++)
	{
		cout << " | ";
		for (int j = 0; j < m_determinant.size(); j++)
		{
			cout << setw(5) << m_determinant[i][j] << " ";
		}
		cout << "|" << endl;
	}
	cramer_rule();

	cout << endl;
	cout << endl;

	return;
}

void Equation::mk_det(void)
{
	m_determinant.resize(m_term.size());
	for (int i = 0; i < m_determinant.size(); i++)	//遍历每一行
	{
		for (auto it = m_term[i].begin(); it != m_term[i].end() - 1; it++)	//遍历所有非常数项
		{
			m_determinant[i].push_back(decode(&(*it)));
		}
	}

	return;
}

void Equation::format(void)
{
	Term temp;
	temp.op = '+';	temp.coefficient = 0.0;	temp.variable = '#';
	Term constant;
	constant.op = '+';	constant.coefficient = 0.0;		temp.variable = '#';
	Term* pt = nullptr;
	bool pass_equal = false;
	bool lead_char = true;
	bool deci = false;
	
	double digit = 10.0;
	m_term.resize(m_equation.size());
	for (int i = 0; i < m_equation.size(); i++)	//遍历每一行
	{
		for (int j = 0; j < m_equation[i].size(); j++)	//遍历每一个字符
		{
			if (m_equation[i][j] == ' ')
				continue;
			if (m_equation[i][j] == '+' || m_equation[i][j] == '-')
			{
				if (!lead_char)
				{
					if (pass_equal && temp.op == '+')
						temp.op = '-';
					else if (pass_equal && temp.op == '-')
						temp.op = '+';
					if (temp.variable != '#')
						temp.coefficient = temp.coefficient == 0.0 ? 1.0 : temp.coefficient;
					pt = dup_variable(i, temp.variable);
					if (pt)
						sum_liked_term(pt, &temp);
					else
						if (temp.variable != '#')
							m_term[i].push_back(temp);
					if (temp.variable == '#')
						sum_liked_term(&constant, &temp);
					temp.op = m_equation[i][j];	temp.coefficient = 0.0;	temp.variable = '#';
					digit = 10.0;	deci = false;
				}
				else
				{
					temp.op = m_equation[i][j];
					lead_char = false;
				}
			}
			else if (isdigit(m_equation[i][j]))
			{
				lead_char = false;
				if (!deci)
					temp.coefficient = temp.coefficient * 10 + (static_cast<double>(m_equation[i][j]) - '0');
				else
				{
					temp.coefficient = temp.coefficient + (static_cast<double>(m_equation[i][j]) - '0') / digit;
					digit *= 10;
				}
			}
			else if (m_equation[i][j] == '.')
				deci = true;
			else if (isalpha(m_equation[i][j]))
			{
				lead_char = false;
				temp.variable = m_equation[i][j];
			}
			else if (m_equation[i][j] == '=')
			{
				pass_equal = true;
				if (temp.variable != '#')
					temp.coefficient = temp.coefficient == 0.0 ? 1.0 : temp.coefficient;
				pt = dup_variable(i, temp.variable);
				if (pt)
					sum_liked_term(pt, &temp);
				else
					if (temp.variable != '#')
						m_term[i].push_back(temp);
				if (temp.variable == '#')
					sum_liked_term(&constant, &temp);
				temp.op = '+';	temp.coefficient = 0.0;	temp.variable = '#';
				digit = 10.0;	deci = false;	lead_char = true;
			}
		}
		if (pass_equal && temp.op == '+')
			temp.op = '-';
		else if (pass_equal && temp.op == '-')
			temp.op = '+';
		if (temp.variable != '#')
			temp.coefficient = temp.coefficient == 0.0 ? 1.0 : temp.coefficient;
		pt = dup_variable(i, temp.variable);
		if (pt)
			sum_liked_term(pt, &temp);
		else
			if (temp.variable != '#')
				m_term[i].push_back(temp);
		if (temp.variable == '#')
			sum_liked_term(&constant, &temp);
		constant.op = constant.op == '+' ? '-' : '+';
		m_term[i].push_back(constant);
		const_term.push_back(decode(&constant));
		//复位
		temp.op = '+';	temp.coefficient = 0.0;	temp.variable = '#';
		constant.op = '+';	constant.coefficient = 0.0; constant.variable = '#';
		digit = 10.0;	deci = false;	lead_char = true;
		lead_char = true;	pass_equal = false;
	}
	
	//排序
	Term media;
	for (int i = 0; i < m_term[0].size() - 1; i++)	//遍历第一行等号左边的项，取顺序表
	{
		order.push_back(m_term[0][i].variable);
	}
	for (int i = 1; i < m_term.size(); i++)	//从第二行遍历所有行
	{
		for (auto it = order.rbegin(); it != order.rend(); it++)	//倒序遍历顺序表
		{
			for (int j = 0; j < m_term[i].size() - 1; j++)	//遍历每一项(不包括常数项)
			{
				if (m_term[i][j].variable == *it)
				{
					media = m_term[i][j];
					auto itr = m_term[i].begin() + j;
					m_term[i].erase(itr);
					m_term[i].insert(m_term[i].begin(), media);
				}
			}
		}
	}

	return;
}

Term* Equation::dup_variable(int n, char ch)
{
	for (auto it = m_term[n].begin(); it != m_term[n].end(); it++)
	{
		if (it->variable == ch)
			return &(*it);
	}
	return nullptr;
}

double Equation::decode(const Term* c)
{
	if (c->op == '+')
		return c->coefficient;
	if (c->op == '-')
		return 0 - c->coefficient;
	return 0.0;
}

void Equation::sum_liked_term(Term* target, Term* b)
{
	if (target->op == b->op)	//同号，系数相加
	{
		target->coefficient += b->coefficient;
	}
	else if (target->coefficient > b->coefficient)	//异号，且目标项系数更大，符号不变，系数相减
	{
		target->coefficient = target->coefficient - b->coefficient;
	}
	else	//异号，且目标项系数更小，变号，系数相减
	{
		target->op = b->op;
		target->coefficient = b->coefficient - target->coefficient;
	}

	return;
}

Equation::Equation(void)
{
	return;
}

void Equation::convert(int j)
{
	int idx = 0;
	m_temp_deter = m_determinant;
	for (int i = 0; i < m_determinant.size(); i++)	//遍历每一行
	{
		m_temp_deter[i][j] = const_term[idx];
		idx++;
	}

	return;
}

bool Equation::is_linear(void)
{

	return true;
}

bool Equation::check(void)
{

	return true;
}

void Equation::cramer_rule(void)
{
	Determinant* temp_obj = new Determinant;
	double temp_res;
	m_denominator = temp_obj->calc(m_determinant, m_determinant.size());
	cout << "D = " << m_denominator << endl;
	cout << endl;
	if (m_denominator == 0)
	{
		cout << "不适用。" << endl;
		return;
	}
	int msg;
	for (msg = 0; msg < order.size(); msg++)
	{
		convert(msg);
		temp_res = temp_obj->calc(m_temp_deter, m_temp_deter.size());
		cout << "D" << msg + 1 << " = " << temp_res << "  ";
		cout << order[msg] << " = " << "D" << msg + 1 << " / D = " << temp_res / m_denominator << endl;
	}


	return;
}