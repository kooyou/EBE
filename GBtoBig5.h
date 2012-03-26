#pragma once

class CGBtoBig5
{
public:
	CGBtoBig5(void);
	~CGBtoBig5(void);

public:
	CString GBtoBig5(CString GBString);
	CString Big5toGB(CString GBString);
};
