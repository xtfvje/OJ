#pragma once

// http://blog.csdn.net/ljp1919/article/details/46976697
// 华为OJ:输出单向链表中倒数第k个结点
/*
输入一个单向链表，输出该链表中倒数第k个结点，链表的倒数第0个结点为链表的尾指针。
链表结点定义如下：
struct ListNode
{
int       m_nKey;
ListNode* m_pNext;
};

详细描述：
接口说明
原型：   ListNode* FindKthToTail(ListNode* pListHead, unsignedint k);
输入参数：
ListNode* pListHead  单向链表
unsigned int k  倒数第k个结点
输出参数（指针指向的内存区域保证有效）：
无
返回值：
正常返回倒数第k个结点指针，异常返回空指针
*/

struct ListNode
{
	int        m_nKey;
	ListNode*  m_pNext;

};

ListNode* CreateList(const int num);

ListNode* FindKthToTail(ListNode* pListHead, unsigned int k);