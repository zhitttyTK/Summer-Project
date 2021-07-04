#include "powercalc.h"

using namespace std;


void Exhaustive::crypt_auto(int n)
{
	if (solved == true)
		return;
	if (n == 0)
	{
		for (int i = 0; i < m_range.size(); i++)
		{
			for (int j = 0; j < m_variable.find(m_key[m_variable.size() - 1])->second.size(); j++)	//����map�ĵ� ��������-1-�ݹ�� ��key��Ӧ��vector
			{
				//�滻��vector��ÿһ���±��Ӧ��δ֪��Ϊȡֵ����ֵ�ֵ
				m_term[get_term(m_variable.find(m_key[m_variable.size() - 1])->second[j])][get_index(m_variable.find(m_key[m_variable.size() - 1])->second[j])] = m_range[i] + '0';
			}
			if (check_duplicate(m_variable.size() - 1))
				continue;
			if (lead_zero())
				continue;
			if (found_result())
			{
				cout << "��Ϊ�� " << m_term[0] << m_task << m_term[1] << "=" << m_term[2];
				cout << endl;
				for (int i = 0; i < m_key.size(); i++)
				{
					cout << m_key[i] << " = " << m_term[get_term(m_variable.find(m_key[i])->second[0])][get_index(m_variable.find(m_key[i])->second[0])] << "   ";
				} 
				cout << endl;
				solved = true;
				return;
			}
		}
		return;
	}
	for (int i = 0; i < m_range.size(); i++)	//����ȡֵ���ÿһ��ֵ
	{
		for (int j = 0; j < m_variable.find(m_key[m_variable.size()- 1 - n])->second.size(); j++)	//����map�ĵ� ��������-1-�ݹ�� ��key��Ӧ��vector
		{
			//�滻��vector��ÿһ���±��Ӧ��δ֪��Ϊȡֵ����ֵ�ֵ
			m_term[get_term(m_variable.find(m_key[m_variable.size() - 1 - n])->second[j])][get_index(m_variable.find(m_key[m_variable.size() - 1 - n])->second[j])] = m_range[i] + '0';
		}
		if (check_duplicate(m_variable.size() - 1 - n))
			continue;
		crypt_auto(n - 1);
	}
}

double Determinant::calc(vector<vector<double>> deter, int n)
{
	vector<vector<int>> idx_permutation;
	vector<int> idx_init = inivec(n);
	vector<int> idx_temp;
	permutation(idx_init, idx_permutation, 0);
	int row;	//�б�
	int col;	//�б�
	double term;

	double result = 0;

	for (int i = 0; i < static_cast<int>(idx_permutation.size()); i++)	//����ÿһ��
	{
		idx_temp = idx_permutation[i];	//�б�ȡ���п��ܵ�����
		term = term_positive(idx_temp) ? 1.0 : -1.0;
		row = 0;	//�б�ȡ1 2 3 4 ... n
		for (int j = 0; j < static_cast<int>(idx_temp.size()); j++)	//����ÿһ��Ԫ��
		{
			col = idx_temp[j];
			term *= deter[row++][col];
		}
		result += term;
	}
	return result;
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
		cout << "�����á�" << endl;
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
	delete temp_obj;


	return;
}