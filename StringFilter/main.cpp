#define _CRT_SECURE_NO_WARNINGS
/*
    ͨ����������һ��Сд��ĸ(a~z)��ɵ��ַ��������дһ���ַ������˳������ַ����г��ֶ����ͬ���ַ���
�����״γ��ֵ��ַ����˵��������ַ�����abacacde�����˽��Ϊ��abcde����

Ҫ��ʵ�ֺ�����void stringFilter(const char *pInputStr, long lInputLen, char *pOutputStr);

�����롿 pInputStr��  �����ַ���
         lInputLen��  �����ַ�������
������� pOutputStr�� ����ַ������ռ��Ѿ����ٺã��������ַ����ȳ���

��ע�⡿ֻ��Ҫ��ɸú��������㷨���м䲻��Ҫ���κ�IO���������

ʾ��
���룺��deefd��        �������def��
���룺��afafafaf��     �������af��
���룺��pppppppp��     �������p��
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
ͨ����������һ��Сд��ĸ(a~z)��ɵ��ַ��������дһ���ַ���ѹ�����򣬽��ַ�����������ϯ���ظ���ĸ
����ѹ���������ѹ������ַ�����
ѹ������
1����ѹ�������ظ����ֵ��ַ��������ַ���"abcbc"�����������ظ��ַ���ѹ������ַ�������"abcbc"��
2��ѹ���ֶεĸ�ʽΪ"�ַ��ظ��Ĵ���+�ַ�"�����磺�ַ���"xxxyyyyyyz"ѹ����ͳ�Ϊ"3x6yz"��

Ҫ��ʵ�ֺ�����
void stringZip(const char *pInputStr, long lInputLen, char *pOutputStr);

�����롿 pInputStr��  �����ַ���
         lInputLen��  �����ַ�������
������� pOutputStr�� ����ַ������ռ��Ѿ����ٺã��������ַ����ȳ���

��ע�⡿ֻ��Ҫ��ɸú��������㷨���м䲻��Ҫ���κ�IO���������

ʾ��
���룺��cccddecc��   �������3c2de2c��
���룺��adef��     �������adef��
���룺��pppppppp�� �������8p��
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
			if (pInputStr[i] == pInputStr[j])     //ͳ���ַ�����ÿ���ַ������������ֵ��ظ���ĸ����
				++num;
			else
				break;
		}//for
		if (0 != num)    //num��������λ����λ�����λ������
		{
			memset(buffer, 0, sizeof(buffer));
			_itoa_s(num + 1, buffer, 10);      //��������10����ת��Ϊ�ַ���
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
	long j = 0;//����ַ������±�
	for (long i = 0; i < lInputLen; i++) {
		if (pInputStr[i] == pInputStr[i + 1])
			cnt++;
		else {
			if (cnt > 0) {
				int pow = 1; //pow ��ʾ 10^n, nΪcnt��λ��
				int tmp = cnt;
				while (tmp > 0) {
					tmp /= 10;
					pow *= 10;
				}
				pow /= 10;
				//�����λ��ʼ
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
	bool hash[26] = { 0 };    //ͳ���ַ��Ƿ����  
	int i, j;
	for (i = 0, j = 0; i < lInputLen; ++i)
	{
		if (false == hash[pInputStr[i] - 'a'])     //���ַ���ľ�г��ֹ�  
		{
			hash[pInputStr[i] - 'a'] = true;
			pOutputStr[j++] = pInputStr[i];
		}
	}
	pOutputStr[j] = '\0';
}

/*
ͨ����������100�����������ļӡ�������ʽ�����дһ����������������ַ�����
�����ַ����ĸ�ʽΪ����������1 ����� ������2���������������롰�������֮����һ���ո������

����˵����
1��������Ϊ������������Ҫ���Ǽ���������������
2����������ʽ��ʽ����������Ϊ��0����

Ҫ��ʵ�ֺ�����
void arithmetic(const char *pInputStr, long lInputLen, char *pOutputStr);

�����롿 pInputStr��  �����ַ���
lInputLen��  �����ַ�������
������� pOutputStr�� ����ַ������ռ��Ѿ����ٺã��������ַ����ȳ���

��ע�⡿ֻ��Ҫ��ɸú��������㷨���м䲻��Ҫ���κ�IO���������

ʾ��
���룺��4 + 7��  �������11��
���룺��4 - 7��  �������-3��
���룺��9 ++ 7��  �������0�� ע����ʽ����
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
	if (2 != num_space)     //�ո����Ƿ�
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
		else                 //��һ�����������зǷ��ַ�
		{
			pOutputStr[0] = '0';
			pOutputStr[1] = '\0';
			return;
		}
	}
	for (j = i + 1; pInputStr[j] != ' '; ++j);
	if (1 != j - i - 1)     //��������Ȳ��Ϸ�
	{
		pOutputStr[0] = '0';
		pOutputStr[1] = '\0';
		return;
	}
	else    //�������ĳ���Ϊ1
	{
		if ('+' != pInputStr[i + 1] && '-' != pInputStr[i + 1])    //�������ŷǷ�
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
				else          //�ڶ������������зǷ��ַ�
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
			_itoa_s(result, buffer, 10);      //��������10����ת��Ϊ�ַ���
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

	//��������ʽ�Ƿ�Ϸ�, iӦ��ָ���һ���ո�
	if (i == 0 || pInputStr[i] != ' ') {
		pOutputStr[0] = '0';
		pOutputStr[1] = 0;
		return;
	}
	i++;//iָ�������
	char tmp;
	if (pInputStr[i] == '+' || pInputStr[i] == '-'
		|| pInputStr[i] == '*' || pInputStr[i] == '/') {
		tmp = pInputStr[i];
		i++; //iӦ��ָ�������֮��Ŀո�
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
	i++;//iָ��ڶ���������
	buffer[j] = 0;
	num1 = atoi(buffer);
	//��ʼ��õڶ���������
	j = 0;
	while (pInputStr[i] >= '0' && pInputStr[i] <= '9') {
		buffer[j++] = pInputStr[i];
		i++;
	}
	//�жϽ�β�����Ƿ��ǺϷ���
	if (pInputStr[i] != 0) {
		pOutputStr[0] = '0';
		pOutputStr[1] = 0;
		return;
	}
	num2 = atoi(buffer);
	//������
	if (tmp == '+') itoa(num1 + num2, pOutputStr, 10);
	else if (tmp == '-') itoa(num1 - num2, pOutputStr, 10);
	else if (tmp == '*') itoa(num1 * num2, pOutputStr, 10);
	else itoa(num1 / num2, pOutputStr, 10);
}

#endif