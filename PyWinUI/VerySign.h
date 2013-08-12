#pragma once

typedef struct {
	LPWSTR lpszProgramName;
	LPWSTR lpszPublisherLink;
	LPWSTR lpszMoreInfoLink;

} SPROG_PUBLISHERINFO, *PSPROG_PUBLISHERINFO;

class CSignatureInfo
{
public:
	CSignatureInfo();
	~CSignatureInfo();

public:
	wstring m_strProgramName;
	wstring m_strPublisherLink;
	wstring m_strMoreInfoLink;
	wstring m_strSignCompany;
	wstring m_strTimestamp;
	wstring m_strSubjectName;
};

class CVerySign
{
public:
	CVerySign(void);
	~CVerySign(void);

public:
	static BOOL GetSignedStore(const wchar_t* szFileName, CSignatureInfo& info);
	static BOOL GetProgAndPublisherInfo(PCMSG_SIGNER_INFO pSignerInfo,PSPROG_PUBLISHERINFO Info);
	static BOOL GetDateOfTimeStamp(PCMSG_SIGNER_INFO pSignerInfo, SYSTEMTIME *st);
	static BOOL GetCertificateInfo(PCCERT_CONTEXT pCertContext,CSignatureInfo& info);
	static BOOL GetTimeStampSignerInfo(PCMSG_SIGNER_INFO pSignerInfo, PCMSG_SIGNER_INFO *pCounterSignerInfo);
	static LPWSTR AllocateAndCopyWideString(LPCWSTR inputString);
	static BOOL  GetProductInfo(LPCTSTR modulename, LPTSTR szCompanay, LPTSTR szSoftName, LPTSTR szVersion,
		LPTSTR szFileVersion, LPTSTR szFileDes,WORD &langID,WORD &charsetID);
};