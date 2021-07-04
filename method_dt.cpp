#include "powercalc.h"

void Determinant::swap(vector<int>& idx, int i, int j)
{
	int temp = idx[i];
	idx[i] = idx[j];
	idx[j] = temp;
	return;
}

void Determinant::permutation(vector<int>& ini, vector<vector<int>>& result, int current)
{
	if (current == static_cast<int>(ini.size()) - 1)
		result.push_back(ini);
	else
	{
		for (int i = current; i < static_cast<int>(ini.size()); i++)
		{
			swap(ini, i, current);
			permutation(ini, result, current + 1);
			swap(ini, i, current);
		}
	}
}

vector<int> Determinant::inivec(int num)
{
	vector<int> initial;
	for (int i = 0; i < num; i++)
		initial.push_back(i);
	return initial;
}

bool Determinant::is_even(int num)
{
	return ((num & 1) == 0);	//位运算
}

bool Determinant::term_positive(vector<int>& seq)
{
	int count = 0;	//逆序数
	for (int i = 0; i < static_cast<int>(seq.size()); i++)
		for (int j = i + 1; j < static_cast<int>(seq.size()); j++)
			if (seq[i] > seq[j])
				count++;
	return is_even(count);
}

void Determinant::process(void)
{
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);
	
	int n;
	double ele;
	vector<vector<double>> determinant;
	cout << "输入行列式阶数：" << endl;
	cin >> n;
	cout << "输入行列式：" << endl;
	determinant.resize(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> ele;
			determinant[i].push_back(ele);
		}
	}

	cout << "检查输入：" << endl;

	for (int i = 0; i < (int)determinant.size(); i++)
	{
		cout << " | ";
		for (int j = 0; j < (int)determinant.size(); j++)
		{
			cout << setw(5) << determinant[i][j] << " ";
		}
		cout << "|" << endl;
	}
	cout << endl;
	cout << endl;

	cout << "运算结果为：" << calc(determinant, n) << endl;
	cout << endl;
}