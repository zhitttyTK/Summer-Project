#include "brute.h"

using namespace std;

bool done = false;

void Exhaustive::crypt_auto(int n)
{
	if (done == true)
		return;
	if (n == 0)
	{
		for (int i = 0; i < m_range.size(); i++)
		{
			m_term[get_term(m_unknown[m_unknown.size()-1])][get_index(m_unknown[m_unknown.size()-1])] = m_range[i] + '0';
			if (check_duplicate())	continue;
			if (found_result())
			{
				cout << "´ð°¸Îª£º " << m_term[0] << m_task << m_term[1] << "=" << m_term[2];
				cout << endl;
				done = true;
				return;
			}
		}
		return;
	}
	for (int i = 0; i < m_range.size(); i++)
	{
		m_term[get_term(m_unknown[m_unknown.size()- 1 - n])][get_index(m_unknown[m_unknown.size() - 1 - n])] = m_range[i] + '0';
		crypt_auto(n - 1);
	}
}