#include "powercalc.h"

using namespace std;


int main()
{
	char ch;
	cout << "'A' ��ٷ��ƽ�������" << endl;
	cout << "'B' �ⷽ����" << endl;
	cout << "'C' ������ʽ" << endl;
	cout << "'Q' �˳�" << endl;
	cout << endl;
	cout << "����";
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
		else
		{
			cout << "�޴˹��ܡ�" << endl;
		}
		cout << "'A' ��ٷ��ƽ�������" << endl;
		cout << "'B' �ⷽ����" << endl;
		cout << "'C' ������ʽ" << endl;
		cout << "'Q' �˳�" << endl;
		cout << endl;
		cout << "����";

		cin >> ch;
	}

	system("PAUSE");
	return 0;
}