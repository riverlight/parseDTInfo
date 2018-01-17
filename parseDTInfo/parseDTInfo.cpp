#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "parseDTInfo.h"

using namespace std;

#define MAX_LINE_LEN 1000

CDTInfo::CDTInfo()
{
	_szFileName = NULL;
	_pDTFile = NULL;
	_nCurrentPos = 0;
}

CDTInfo::~CDTInfo()
{

}

int CDTInfo::Open(char *szFileName)
{
	_szFileName = szFileName;

	if (_szFileName == NULL)
		return 0;

	_pDTFile = new ifstream(_szFileName);
	if (_pDTFile == NULL)
		return 0;

	cout << "file name : " << _szFileName << endl;

	char *pLine = new char[MAX_LINE_LEN];
	memset(pLine, 0, MAX_LINE_LEN);
	while (_pDTFile->getline(pLine, MAX_LINE_LEN))
	{
		int nLineSize = strlen(pLine);
		if (nLineSize <= 0)
			break;

		char *pInfo = new char[nLineSize+1];
		pInfo[nLineSize] = 0;
		memcpy(pInfo, pLine, nLineSize);
		_vLine.push_back(pInfo);

		if (ParseDTInfo(pLine) == 0)
			cout << "**** error line ***** :" << pLine << endl;

		memset(pLine, 0, MAX_LINE_LEN);
	}

	_pDTFile->close();
	delete _pDTFile;

	return 1;
}

int CDTInfo::Close()
{
	int i;
	for (i = 0; i < _vLine.size(); i++)
	{
		char *p = _vLine[i];
		delete p;
	}
	_vLine.clear();

	return 1;
}

char *CDTInfo::GetInfo(int nTime_ms)
{
	if (_nCurrentPos >= _vpDTInfo.size())
		return NULL;
	if (nTime_ms >= _vpDTInfo[_nCurrentPos]->_nTime_ms)
	{
		char *pInfo = _vpDTInfo[_nCurrentPos]->_pInfo;
		_nCurrentPos++;
		return pInfo;
	}
	return NULL;
}

int CDTInfo::Print()
{
	int i;
	for (i = 0; i < _vLine.size(); i++)
		cout << _vLine[i] << endl;

	for (i = 0; i < _vpDTInfo.size(); i++)
		cout << "time : " << _vpDTInfo[i]->_nTime_ms << "  ; info = " << _vpDTInfo[i]->_pInfo << endl;

	return 1;
}

int CDTInfo::ParseDTInfo(char *pLine)
{
	int i;
	int bHaveSpace = 0;
	for (i = 0; i < strlen(pLine); i++)
	{
		if (pLine[i] == '\t')
		{
			bHaveSpace = 1;
			break;
		}
	}
	if (bHaveSpace == 0)
		return 0;

	DTInfo *pInfo = new DTInfo;
	pInfo->_nTime_ms = atoi(pLine);
	pInfo->_pInfo = new char[strlen(pLine) + 1];
	memset(pInfo->_pInfo, 0, strlen(pLine) + 1);
	memcpy(pInfo->_pInfo, pLine + i + 1, strlen(pLine) - i -1);

	_vpDTInfo.push_back(pInfo);

	return 1;
}
