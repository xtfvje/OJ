#include "FindKthToTail.h"
#include <iostream>
#include <cstdlib>

using namespace std;

ListNode* CreateList(const int num)
{
	ListNode* pHead = (ListNode*)malloc(sizeof(ListNode));
	if (NULL == pHead)
	{
		return NULL;
	}

	pHead->m_nKey = num;  // ��һ����Žڵ����
	pHead->m_pNext = NULL;

	ListNode* pList = pHead;
	if (NULL != pHead)
	{
		for (int i = 0; i < num; ++i)
		{
			ListNode* pNode = (ListNode*)malloc(sizeof(ListNode));
			if (NULL == pNode)
			{
				return NULL;
			}
			cin >> pNode->m_nKey;
			pNode->m_pNext = NULL;
			pHead->m_pNext = pNode;
			pHead = pNode;
		}
	}

	return pList;
}

/* �㷨˼·��
       Ϊ�˵õ�������k�����,����Ȼ���뷨�����ߵ������β�ˣ��ٴ�β�˻���k����
   ����������ǵ�������ֻ�д�ǰ�����ָ���û�дӺ���ǰ��ָ�롣����������£�
       �ڱ���ʱά������ָ�룬��һ��ָ��������ͷָ�뿪ʼ�������ڵ�k-1��֮ǰ���ڶ���ָ�뱣�ֲ�����
   �ڵ�k-1����ʼ���ڶ���ָ��Ҳ��ʼ�������ͷָ�뿪ʼ��������������ָ��ľ��뱣����k-1������һ��
   ������ǰ��ģ�ָ�뵽�������β���ʱ���ڶ���ָ�루���ں���ģ�ָ�������ǵ�����k����㡣
*/
ListNode* FindKthToTail(ListNode* pListHead, unsigned int k)
{
	if (NULL == pListHead)
	{
		return NULL;
	}

	ListNode* pFirst = pListHead;  // ��һ��ָ��
	
	for (unsigned int i = 0; i < k; ++i)
	{
		if (NULL != pFirst->m_pNext)
		{
			pFirst = pFirst->m_pNext;
		}
		else
		{
			return NULL;  // ����ڵ�������k��
		}
	}

	ListNode* pSecond = pListHead;  // �ڶ���ָ�뿪ʼҲָ��pListHead
	// pFisrt �� pSecond�ľ�����k, ��pFirstָ�뵽������βʱ, pSecond�����ô�������ڵ�����k���ڵ��λ��
	while (NULL != pFirst->m_pNext)
	{
		pFirst = pFirst->m_pNext;
		pSecond = pSecond->m_pNext;
	}

	return pSecond;								
}