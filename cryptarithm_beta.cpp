#include <iostream>

int a[9] = { 0 };

bool dup(void)
{
	bool jump = false;
	for (int i = 0; i < 8; i++)
	{
		if (jump)
			break;
		for (int j = i + 1; j < 9; j++)
		{
			if (a[i] == 0)
			{
				jump = true;
				break;
			}
			if (a[i] == a[j])
				return true;
		}
	}
	return false;
}

int main()
{
	using namespace std;

	for (a[0] = 1; a[0] <= 9; a[0]++)
	{
		for (a[1] = 1; a[1] <= 9; a[1]++)
		{
			
			for (a[2] = 1; a[2] <= 9; a[2]++)
			{
				
				for (a[3] = 1; a[3] <= 9; a[3]++)
				{
				
					for (a[4] = 1; a[4] <= 9; a[4]++)
					{
					
						for (a[5] = 1; a[5] <= 9; a[5]++)
						{
						
							for (a[6] = 1; a[6] <= 9; a[6]++)
							{
							
								for (a[7] = 1; a[7] <= 9; a[7]++)
								{
								
									for (a[8] = 1; a[8] <= 9; a[8]++)
									{
										if (dup()) continue;
										if ((a[0] * 10000 + a[1] * 1000 + a[2] * 100 + a[3] * 10 + a[4] * 1) - (a[5] * 1000 + a[6] * 100 + a[7] * 10 + a[8] * 1) == 33333)
										{
											cout << a[0] << a[1] << a[2] << a[3] << a[4] << endl;
											cout << '-' << a[5] << a[6] << a[7] << a[8] << endl;
											cout << "-----" << endl;
											cout << "33333" << endl;

											return 0;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return 0;
}