#include "brute.h"

using namespace std;

bool done = false;

void Exhaustive::crypt_auto(int n)
{
	if (done == true)
		return;
	if (n == 0)
	{
		for (int i = 0; i < range.size(); i++)
		{
			term[get_term(unknown[unknown.size()-1])][get_index(unknown[unknown.size()-1])] = range[i] + '0';
			if (check_duplicate())	continue;
			if (found_result())
			{
				cout << "´ð°¸Îª£º " << term[0] << task << term[1] << "=" << term[2];
				cout << endl;
				done = true;
				return;
			}
		}
		return;
	}
	for (int i = 0; i < range.size(); i++)
	{
		term[get_term(unknown[unknown.size()- 1 - n])][get_index(unknown[unknown.size() - 1 - n])] = range[i] + '0';
		crypt_auto(n - 1);
	}
}