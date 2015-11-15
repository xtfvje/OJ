#define _CRT_SECURE_NO_WARNINGS
/*
    通过键盘输入一串小写字母(a~z)组成的字符串。请编写一个字符串过滤程序，若字符串中出现多个相同的字符，
将非首次出现的字符过滤掉。比如字符串“abacacde”过滤结果为“abcde”。

要求实现函数：void stringFilter(const char *pInputStr, long lInputLen, char *pOutputStr);

【输入】 pInputStr：  输入字符串
         lInputLen：  输入字符串长度
【输出】 pOutputStr： 输出字符串，空间已经开辟好，与输入字符串等长；

【注意】只需要完成该函数功能算法，中间不需要有任何IO的输入输出

示例
输入：“deefd”        输出：“def”
输入：“afafafaf”     输出：“af”
输入：“pppppppp”     输出：“p”
*/

#include <iostream>
#include <cstdlib>

using namespace std;

#define MAXCHAR 256 

void stringFilter(const char* pInputStr, long lInputLen, char* pOutputStr);

void stringZip(const char* pInputStr, long lInputLen, char* pOutputStr);

void stringZip2(const char *pInputStr, long lInputLen, char *pOutputStr);

void arithmetic(const char* pInputStr, long lInputLen, char* pOutputStr);
//void arithmetic2(const char* pInputStr, long lInputLen, char* pOutputStr);

int main()
{
	char pInputStr1[] = { "adavfdabbbccucdde" };
	char pInputStr2[] = { "aaaaasaaaaaaabbcddddddddddddddddde" };
	char pInputStr3[] = { "3 + 4" };
	char pOutputStr1[MAXCHAR] = { 0 };
	char pOutputStr2[MAXCHAR] = { 0 };
	char pOutputStr3[MAXCHAR] = { 0 };
	stringFilter(pInputStr1, strlen(pInputStr1), pOutputStr1);
	stringZip(pInputStr2, strlen(pInputStr2), pOutputStr2);
	arithmetic(pInputStr3, strlen(pInputStr3), pOutputStr3);
	puts(pOutputStr1);
	puts(pOutputStr2);
	puts(pOutputStr3);

	return 0;
}

/*
通过键盘输入一串小写字母(a~z)组成的字符串。请编写一个字符串压缩程序，将字符串中连续出席的重复字母
进行压缩，并输出压缩后的字符串。
压缩规则：
1、仅压缩连续重复出现的字符。比如字符串"abcbc"由于无连续重复字符，压缩后的字符串还是"abcbc"。
2、压缩字段的格式为"字符重复的次数+字符"。例如：字符串"xxxyyyyyyz"压缩后就成为"3x6yz"。

要求实现函数：
void stringZip(const char *pInputStr, long lInputLen, char *pOutputStr);

【输入】 pInputStr：  输入字符串
         lInputLen：  输入字符串长度
【输出】 pOutputStr： 输出字符串，空间已经开辟好，与输入字符串等长；

【注意】只需要完成该函数功能算法，中间不需要有任何IO的输入输出

示例
输入：“cccddecc”   输出：“3c2de2c”
输入：“adef”     输出：“adef”
输入：“pppppppp” 输出：“8p”
*/

void stringZip(const char* pInputStr, long lInputLen, char* pOutputStr)
{
	int i, j, k, num;
	char buffer[20];
	for (i = 0, k = 0; i < lInputLen; )
	{
		num = 0;
		for (j = i + 1; j < lInputLen; ++j)
		{
			if (pInputStr[i] == pInputStr[j])     //统计字符串中每个字符后面连续出现的重复字母次数
				++num;
			else
				break;
		}//for
		if (0 != num)    //num可能是两位或三位或更多位的整数
		{
			memset(buffer, 0, sizeof(buffer));
			_itoa_s(num + 1, buffer, 10);      //将整数按10进制转换为字符串
			strcpy(pOutputStr + k, buffer);
			k += strlen(buffer);
		}
		pOutputStr[k++] = pInputStr[i];
		i = i + num + 1;
	}//for
	pOutputStr[k] = '\0';
}

void stringZip2(const char *pInputStr, long lInputLen, char *pOutputStr) {
	int cnt = 0;
	long j = 0;//输出字符串的下标
	for (long i = 0; i < lInputLen; i++) {
		if (pInputStr[i] == pInputStr[i + 1])
			cnt++;
		else {
			if (cnt > 0) {
				int pow = 1; //pow 表示 10^n, n为cnt的位数
				int tmp = cnt;
				while (tmp > 0) {
					tmp /= 10;
					pow *= 10;
				}
				pow /= 10;
				//从最高位开始
				while (pow > 0) {
					int c = cnt / pow;
					pOutputStr[j++] = '0' + c;
					cnt = cnt % pow;
					pow /= 10;
				}
			}
			pOutputStr[j++] = pInputStr[i];
			cnt = 0;
		}
	}
	pOutputStr[j] = 0;
}





void stringFilter(const char* pInputStr, long lInputLen, char* pOutputStr)
{
	bool hash[26] = { 0 };    //统计字符是否出现  
	int i, j;
	for (i = 0, j = 0; i < lInputLen; ++i)
	{
		if (false == hash[pInputStr[i] - 'a'])     //该字符还木有出现过  
		{
			hash[pInputStr[i] - 'a'] = true;
			pOutputStr[j++] = pInputStr[i];
		}
	}
	pOutputStr[j] = '\0';
}

/*
通过键盘输入100以内正整数的加、减运算式，请编写一个程序输出运算结果字符串。
输入字符串的格式为：“操作数1 运算符 操作数2”，“操作数”与“运算符”之间以一个空格隔开。

补充说明：
1、操作数为正整数，不需要考虑计算结果溢出的情况。
2、若输入算式格式错误，输出结果为“0”。

要求实现函数：
void arithmetic(const char *pInputStr, long lInputLen, char *pOutputStr);

【输入】 pInputStr：  输入字符串
lInputLen：  输入字符串长度
【输出】 pOutputStr： 输出字符串，空间已经开辟好，与输入字符串等长；

【注意】只需要完成该函数功能算法，中间不需要有任何IO的输入输出

示例
输入：“4 + 7”  输出：“11”
输入：“4 - 7”  输出：“-3”
输入：“9 ++ 7”  输出：“0” 注：格式错误
*/

void arithmetic(const char* pInputStr, long lInputLen, char* pOutputStr)
{
	int i, j, num1, num2, result, num_space;
	char buffer[4];
	bool add, sub;
	add = sub = false;
	for (i = 0, num_space = 0; i < lInputLen; ++i)
	{
		if (pInputStr[i] == ' ')
			++num_space;
	}
	if (2 != num_space)     //空格数非法
	{
		pOutputStr[0] = '0';
		pOutputStr[1] = '\0';
		return;
	}
	num1 = num2 = 0;
	for (i = 0; pInputStr[i] != ' '; ++i)
	{
		if (pInputStr[i] >= '0' && pInputStr[i] <= '9')
			num1 = num1 * 10 + pInputStr[i] - '0';
		else                 //第一个操作数中有非法字符
		{
			pOutputStr[0] = '0';
			pOutputStr[1] = '\0';
			return;
		}
	}
	for (j = i + 1; pInputStr[j] != ' '; ++j);
	if (1 != j - i - 1)     //运算符长度不合法
	{
		pOutputStr[0] = '0';
		pOutputStr[1] = '\0';
		return;
	}
	else    //操作符的长度为1
	{
		if ('+' != pInputStr[i + 1] && '-' != pInputStr[i + 1])    //操作符号非法
		{
			pOutputStr[0] = '0';
			pOutputStr[1] = '\0';
			return;
		}
		else
		{
			if ('+' == pInputStr[i + 1])
				add = true;
			if ('-' == pInputStr[i + 1])
				sub = true;
			for (i = j + 1; i < lInputLen; ++i)
			{
				if (pInputStr[i] >= '0' && pInputStr[i] <= '9')
					num2 = num2 * 10 + pInputStr[i] - '0';
				else          //第二个操作数中有非法字符
				{
					pOutputStr[0] = '0';
					pOutputStr[1] = '\0';
					return;
				}
			}//for
			if (add)
				result = num1 + num2;
			else if (sub)
				result = num1 - num2;
			memset(buffer, 0, sizeof(buffer));
			_itoa_s(result, buffer, 10);      //将整数按10进制转换为字符串
			strcpy(pOutputStr, buffer);
		}//esle
	}//else
}

#if 0
void arithmetic2(const char *pInputStr, long lInputLen, char *pOutputStr) {
	char buffer[200];
	int num1, num2;
	int i = 0;
	int j = 0;
	while (pInputStr[i] >= '0' && pInputStr[i] <= '9') {
		buffer[j++] = pInputStr[i];
		i++;
	}

	//检测输入格式是否合法, i应该指向第一个空格
	if (i == 0 || pInputStr[i] != ' ') {
		pOutputStr[0] = '0';
		pOutputStr[1] = 0;
		return;
	}
	i++;//i指向操作符
	char tmp;
	if (pInputStr[i] == '+' || pInputStr[i] == '-'
		|| pInputStr[i] == '*' || pInputStr[i] == '/') {
		tmp = pInputStr[i];
		i++; //i应该指向运算符之后的空格
	}
	else {
		pOutputStr[0] = '0';
		pOutputStr[1] = 0;
		return;
	}
	if (pInputStr[i] != ' ') {
		pOutputStr[0] = '0';
		pOutputStr[1] = 0;
		return;
	}
	i++;//i指向第二个操作数
	buffer[j] = 0;
	num1 = atoi(buffer);
	//开始获得第二个操作数
	j = 0;
	while (pInputStr[i] >= '0' && pInputStr[i] <= '9') {
		buffer[j++] = pInputStr[i];
		i++;
	}
	//判断结尾处，是否是合法的
	if (pInputStr[i] != 0) {
		pOutputStr[0] = '0';
		pOutputStr[1] = 0;
		return;
	}
	num2 = atoi(buffer);
	//计算结果
	if (tmp == '+') itoa(num1 + num2, pOutputStr, 10);
	else if (tmp == '-') itoa(num1 - num2, pOutputStr, 10);
	else if (tmp == '*') itoa(num1 * num2, pOutputStr, 10);
	else itoa(num1 / num2, pOutputStr, 10);
}

#endif