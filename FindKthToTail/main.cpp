#include <iostream>
#include "FindKthToTail.h"

using namespace std;

int main()
{
	int nodenum;
	cout << "input nodenum = ";
	cin >> nodenum;

	ListNode *p;
	p = CreateList(nodenum);

	int k;
	cout << "input k = ";
	cin >> k;
	ListNode *resu = FindKthToTail(p->m_pNext, k);
	cout << "result = "<<resu->m_nKey << endl;

	return 1;
}