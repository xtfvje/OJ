#pragma once

// http://blog.csdn.net/ljp1919/article/details/46976697
// ��ΪOJ:������������е�����k�����
/*
����һ��������������������е�����k����㣬����ĵ�����0�����Ϊ�����βָ�롣
�����㶨�����£�
struct ListNode
{
int       m_nKey;
ListNode* m_pNext;
};

��ϸ������
�ӿ�˵��
ԭ�ͣ�   ListNode* FindKthToTail(ListNode* pListHead, unsignedint k);
���������
ListNode* pListHead  ��������
unsigned int k  ������k�����
���������ָ��ָ����ڴ�����֤��Ч����
��
����ֵ��
�������ص�����k�����ָ�룬�쳣���ؿ�ָ��
*/

struct ListNode
{
	int        m_nKey;
	ListNode*  m_pNext;

};

ListNode* CreateList(const int num);

ListNode* FindKthToTail(ListNode* pListHead, unsigned int k);