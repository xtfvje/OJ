#include <cppunit/config/SourcePrefix.h>
#include "CExampleTest.h"
#include <cstdlib>
#include <string>

using namespace std;

// ע������׵�CppUnit
CPPUNIT_TEST_SUITE_REGISTRATION(CExampleTest);

// ��������ʵ��ʾ��
// SetUp: ��ÿ������ǰִ��һ��
void CExampleTest::setUp()
{
	// g_strFilePath = "..\\testcase\\";
}

// tearDown: ��ÿ��������ִ��һ��
void CExampleTest::tearDown()
{

}

void CExampleTest::TestCase01()
{
	vector<int> nums{ 2, 11, 7, 15 };
	int target = 9;
	vector<int> ret = twoSum(nums, target);
	CPPUNIT_ASSERT(2 == ret.size() && 0 == ret[0] && 2 == ret[1]);
//	CPPUNIT_ASSERT(gcd((char*)string(g_strFilePath + "testcase01.txt").c_str()) == 485);
}