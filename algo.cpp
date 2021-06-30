#include "brute.h"

using namespace std;


void Exhaustive::crypt_auto(int n)
{
	if (solved == true)
		return;
	if (n == 0)
	{
		for (int i = 0; i < m_range.size(); i++)
		{
			for (int j = 0; j < m_variable.find(m_key[m_variable.size() - 1])->second.size(); j++)	//遍历map的第 变量个数-1-递归层 个key对应的vector
			{
				//替换该vector的每一个下标对应的未知数为取值表该轮的值
				m_term[get_term(m_variable.find(m_key[m_variable.size() - 1])->second[j])][get_index(m_variable.find(m_key[m_variable.size() - 1])->second[j])] = m_range[i] + '0';
			}
			if (check_duplicate(m_variable.size() - 1))
				continue;
			if (found_result())
			{
				cout << "答案为： " << m_term[0] << m_task << m_term[1] << "=" << m_term[2];
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
	for (int i = 0; i < m_range.size(); i++)	//遍历取值表的每一个值
	{
		for (int j = 0; j < m_variable.find(m_key[m_variable.size()- 1 - n])->second.size(); j++)	//遍历map的第 变量个数-1-递归层 个key对应的vector
		{
			//替换该vector的每一个下标对应的未知数为取值表该轮的值
			m_term[get_term(m_variable.find(m_key[m_variable.size() - 1 - n])->second[j])][get_index(m_variable.find(m_key[m_variable.size() - 1 - n])->second[j])] = m_range[i] + '0';
		}
		if (check_duplicate(m_variable.size() - 1 - n))
			continue;
		crypt_auto(n - 1);
	}
}