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

	pHead->m_nKey = num;  // 第一个存放节点个数
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

/* 算法思路：
       为了得到倒数第k个结点,很自然的想法是先走到链表的尾端，再从尾端回溯k步。
   可是输入的是单向链表，只有从前往后的指针而没有从后往前的指针。解决方法如下：
       在遍历时维持两个指针，第一个指针从链表的头指针开始遍历，在第k-1步之前，第二个指针保持不动；
   在第k-1步开始，第二个指针也开始从链表的头指针开始遍历。由于两个指针的距离保持在k-1，当第一个
   （走在前面的）指针到达链表的尾结点时，第二个指针（走在后面的）指针正好是倒数第k个结点。
*/
ListNode* FindKthToTail(ListNode* pListHead, unsigned int k)
{
	if (NULL == pListHead)
	{
		return NULL;
	}

	ListNode* pFirst = pListHead;  // 第一个指针
	
	for (unsigned int i = 0; i < k; ++i)
	{
		if (NULL != pFirst->m_pNext)
		{
			pFirst = pFirst->m_pNext;
		}
		else
		{
			return NULL;  // 链表节点数不够k个
		}
	}

	ListNode* pSecond = pListHead;  // 第二个指针开始也指向pListHead
	// pFisrt 与 pSecond的距离是k, 当pFirst指针到达链表尾时, pSecond就正好处于链表第倒数第k个节点的位置
	while (NULL != pFirst->m_pNext)
	{
		pFirst = pFirst->m_pNext;
		pSecond = pSecond->m_pNext;
	}

	return pSecond;								
}