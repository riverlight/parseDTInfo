#include <iostream>
#include "parseDTInfo.h"


using namespace std;


int main(int argc, char *argv[])
{
	cout << "Hi, this is parseDTInfo program!" << endl;
	if (argc != 2)
	{
		cout << "test dt-file\n";
		return 0;
	}

	CDTInfo *dt;
	dt = new CDTInfo();
	dt->Open("dt.txt");
	dt->Print();

	int i;
	for (i = 0; i < 100000; i++)
	{
		char *pInfo = dt->GetInfo(i);
		if (pInfo != NULL)
			cout << "get success : " << i << "  " << pInfo << endl;
	}

	dt->Close();

	delete dt;
	dt = NULL;

	return 1;
}
