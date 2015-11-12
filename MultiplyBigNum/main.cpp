#if 0
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <assert.h>

using namespace std;

struct bigcheng2
{
	string a;
	string b;
	string result_str;
};

void reverse_data(string &data);        //字符串反转
void multiply2(bigcheng2 &tempcheng2);  //字符串模拟相乘

int main()
{
	bigcheng2 tempcheng2;
	string a, b;
	cin >> a >> b;
	tempcheng2.a = a;
	tempcheng2.b = b;
	multiply2(tempcheng2);
	cout << tempcheng2.result_str << endl;
	system("pause");

	return 0;
}

void reverse_data(string &data)
{
	char temp = '0';
	int start = 0;
	int end = data.size() - 1;
	assert(data.size() && start <= end);
	while (start < end)
	{
		temp = data[start];
		data[start++] = data[end];
		data[end--] = temp;
	}
}


void multiply2(bigcheng2 &tempcheng2)
{
	reverse_data(tempcheng2.a);//字符串反转
	reverse_data(tempcheng2.b);
	int c = 0;
	string temp(tempcheng2.a.size() + tempcheng2.b.size(), '0');//将temp全部初始化为0字符
	for (unsigned int i = 0; i<tempcheng2.a.size(); i++)
	{
		unsigned int j;
		for (j = 0; j<tempcheng2.b.size(); j++)
		{
			c += temp[i + j] - '0' + (tempcheng2.a[i] - '0')*(tempcheng2.b[j] - '0');//注意temp[i+j]可能保存有上一次计算的结果
			temp[i + j] = (c % 10) + '0';//将结果转换为字符
			c = c / 10;
		}
		while (c)
		{
			temp[i + j++] += c % 10;//temp里已存字符
			c = c / 10;
		}
	}
	for (int i = temp.size() - 1; i >= 0; i--)
	{
		if (temp[i] != '0')
			break;
		else
			temp.pop_back();
	}
	reverse_data(temp);//结果?字??符¤?串??反¤??转?a
	tempcheng2.result_str = temp;
}

#endif 


#if 1

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <assert.h>
using namespace std;
void reverse_data(string &data);//字符串反转
void compute_value(string lhs, string rhs, string &result);
void reverse_data(string &data)
{
	char temp = '0';
	int start = 0;
	int end = data.size() - 1;
	assert(data.size() && start <= end);
	while (start < end)
	{
		temp = data[start];
		data[start++] = data[end];
		data[end--] = temp;
	}
}
void compute_value(string lhs, string rhs, string &result)
{
	reverse_data(lhs);
	reverse_data(rhs);
	int i = 0, j = 0, res_i = 0;
	int tmp_i = 0;
	int carry = 0;

	for (i = 0; i != lhs.size(); ++i, ++tmp_i)
	{
		res_i = tmp_i;  //在每次计算时，结果存储的位需要增加
		for (j = 0; j != rhs.size(); ++j)
		{
			carry += (result[res_i] - '0') + (lhs[i] - '0') * (rhs[j] - '0');//此处注意，每次计算并不能保证以前计算结果的进位都消除， 并且以前的计算结果也需考虑。
			result[res_i++] = (carry % 10 + '0');
			carry /= 10;
		}
		while (carry)//乘数的一次计算完成，可能存在有的进位没有处理
		{
			result[res_i++] = (carry % 10 + '0');
			carry /= 10;
		}
	}
	for (int i = result.size() - 1; i >= 0; i--)
	{
		if (result[i] != '0')
			break;
		else
			result.pop_back();
	}
	reverse_data(result);
}

int main()
{
	string a, b;
	cin >> a >> b;
	string result(a.size() + b.size(), '0');
	compute_value(a, b, result);
	cout << result << endl;
	system("pause");
	return 0;
}


#endif