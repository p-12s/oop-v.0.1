#include "stdafx.h"
#include "MyArray.h"

using namespace std;

int main()
{
	CMyArray<float> floatArr;
	for (float i = 0; i < 10; ++i)
		floatArr.Append(i);

	cout << "Array of float:" << endl;	
	for_each(floatArr.rbegin(), floatArr.rend(), [&](auto &it) {
		cout << it << " ";
	});
	cout << endl;
	floatArr.Clear();


	CMyArray<string> stringArray;
	stringArray.Append("one");
	stringArray.Append("two");
	stringArray.Append("three");

	cout << "Array of string:" << endl;
	for_each(stringArray.rbegin(), stringArray.rend(), [&](auto &it) {
		cout << it << " ";
	});
	cout << endl;
	stringArray.Clear();

	return 0;
}

