#include <iostream>
#include <string>
#include <vector> 
#include <stack> 
#include <algorithm> 

using namespace std;  

int arr[7][7] = { {1, 0, 1, 0, 1, 0, 0},
{0, 1, 0, 1, 0, 1, 0},
{0, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 1 },
};

#include<iostream>
using namespace std;

const int Mon = 1;
const int Tues = 2;
const int Wed = 3;
const int Thus = 4;
const int Fri = 5;
const int Sat = 6;
const int Sun = 7;
void change(int a)
{
	switch (a)
	{
	case 1: cout << "一" << endl; break;
	case 2: cout << "二" << endl; break;
	case 3: cout << "三" << endl; break;
	case 4: cout << "四" << endl; break;
	case 5: cout << "五" << endl; break;
	case 6: cout << "六" << endl; break;
	case 7: cout << "日" << endl; break;
	}
}
int main()
{
	int o1[3] = { Mon, Wed, Fri };
	int o2[2] = { Mon, Sat };
	int o3[2] = { Wed, Sun };
	int o4[1] = { Fri }, o5[3] = { Mon, Thus, Sat }, o6[2] = { Tues, Fri };
	int o7[3] = { Wed, Sat, Sun };
	int i, j, k, x, a, b, c, n[7], flag, lag;
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			if (o1[i] == o2[j])
				continue;
			for (k = 0; k < 2; k++)
			{
				if (o2[j] == o3[k])
					continue;
				for (x = 0; x < 1; x++)
				{
					if (o3[k] == o4[x])
						continue;
					for (a = 0; a < 3; a++)
					{
						if (o4[x] == o5[a])
							continue;
						for (b = 0; b < 2; b++)
						{
							if (o5[a] == o6[b])
								continue;
							for (c = 0; c < 3; c++)
							{
								if (o6[b] == o7[c])
									continue;
								if (o1[i] + o2[j] + o3[k] + o4[x] + o5[a] + o6[b] + o7[c] == 28)
								{
									n[0] = o1[i];
									n[1] = o2[j];
									n[2] = o3[k];
									n[3] = o4[x];
									n[4] = o5[a];
									n[5] = o6[b];
									n[6] = o7[c];
									for (flag = 0; flag < 7; flag++)
									{
										for (lag = 0; lag < flag; lag++)
										{
											if (n[flag] == n[lag])
												break;
										}
										if (lag != flag)
											break;
									}
									if (lag != flag && flag != 7)
										continue;
									cout << "和尚1 星期";   change(o1[i]);
									cout << "和尚2 星期";   change(o2[j]);
									cout << "和尚3 星期";   change(o3[k]);
									cout << "和尚4 星期";   change(o4[x]);
									cout << "和尚5 星期";   change(o5[a]);
									cout << "和尚6 星期";   change(o6[b]);
									cout << "和尚7 星期";   change(o7[c]);
									cout << endl;
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