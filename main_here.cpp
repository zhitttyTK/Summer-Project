#include "powercalc.h"

using namespace std;


int main()
{
	char ch;
	cout << "'A' 穷举法破解填数题" << endl;
	cout << "'B' 解方程组" << endl;
	cout << "'C' 解行列式" << endl;
	cout << "'D' 普通计算器" << endl;
	cout << "'Q' 退出" << endl;
	cout << endl;
	cout << "需求：";
	cin >> ch;
	
	while (ch != 'Q')
	{
		if (ch == 'A')
		{
			cin.get(ch);
			Exhaustive obj;
			obj.process();
			cout << endl;
		}
		else if (ch == 'B')
		{
			cin.get(ch);
			Equation abc;
			abc.process();
			cout << endl;
		}
		else if (ch == 'C')
		{
			cin.get(ch);
			Determinant na;
			na.process();
			cout << endl;
		}
		else if (ch == 'D')
		{
			cin.get(ch);
			ordinary_calc lala;
			lala.process();
			cout << endl;
		}
		else
		{
			cout << "无此功能。" << endl;
		}
		cout << "'A' 穷举法破解填数题" << endl;
		cout << "'B' 解方程组" << endl;
		cout << "'C' 解行列式" << endl;
		cout << "'D' 普通计算器" << endl;
		cout << "'Q' 退出" << endl;
		cout << endl;
		cout << "需求：";

		cin >> ch;
	}

	system("PAUSE");
	return 0;
}