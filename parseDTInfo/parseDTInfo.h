#ifndef PARSEDTINFO_H
#define PARSEDTINFO_H

#include <vector>
#include <fstream>

using namespace std;

typedef struct DTInfo_s
{
	int _nTime_ms;
	char *_pInfo;
} DTInfo;

class CDTInfo
{
public:
	CDTInfo();
	virtual ~CDTInfo();

public:
	int Open(char *szFileName);
	int Close();
	char *GetInfo(int nTime_ms);

	int Print();

private:
	int ParseDTInfo(char *pLine);

private:
	char *_szFileName;
	ifstream *_pDTFile;

	vector<char *> _vLine;
	vector<DTInfo *> _vpDTInfo;
	int _nCurrentPos;
};


#endif // PARSEDTINFO_H

