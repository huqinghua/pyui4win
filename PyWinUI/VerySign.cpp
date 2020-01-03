#include "stdafx.h"

#include <string>
using namespace std;

#include <wincrypt.h>
#include <wintrust.h>
#include <tchar.h>
#include "VerySign.h"

#pragma comment(lib, "crypt32.lib")

#define ENCODING (X509_ASN_ENCODING | PKCS_7_ASN_ENCODING)

CSignatureInfo::CSignatureInfo()
{

}

CSignatureInfo::~CSignatureInfo()
{

}

CVerySign::CVerySign(void)
{
}

CVerySign::~CVerySign(void)
{
}

/*
#define CERT_NAME_EMAIL_TYPE            1
#define CERT_NAME_RDN_TYPE              2
#define CERT_NAME_ATTR_TYPE             3
#define CERT_NAME_SIMPLE_DISPLAY_TYPE   4
#define CERT_NAME_FRIENDLY_DISPLAY_TYPE 5
#define CERT_NAME_DNS_TYPE              6
#define CERT_NAME_URL_TYPE              7
#define CERT_NAME_UPN_TYPE              8

*/

BOOL CVerySign::GetCertificateInfo(PCCERT_CONTEXT pCertContext,CSignatureInfo& info)
{
	BOOL fReturn = FALSE;
	LPTSTR szName = NULL;
	DWORD dwData;

	__try
	{
		// Print Serial Number.

		dwData = pCertContext->pCertInfo->SerialNumber.cbData;
		for (DWORD n = 0; n < dwData; n++)
		{

		}

		// Get Issuer name size.
		if (!(dwData = CertGetNameString(pCertContext,
			CERT_NAME_SIMPLE_DISPLAY_TYPE,
			CERT_NAME_ISSUER_FLAG,
			NULL,
			NULL,
			0)))
		{
			__leave;
		}

		// Allocate memory for Issuer name.
		szName = (LPTSTR)LocalAlloc(LPTR, dwData * sizeof(TCHAR));
		if (!szName)
		{
			__leave;
		}

		// Get Issuer name.
		if (!(CertGetNameString(pCertContext,
			CERT_NAME_SIMPLE_DISPLAY_TYPE,
			CERT_NAME_ISSUER_FLAG,
			NULL,
			szName,
			dwData)))
		{
			__leave;
		}

		info.m_strSubjectName = szName;
		// print Issuer name.

		LocalFree(szName);
		szName = NULL;

		// Get Subject name size.
		if (!(dwData = CertGetNameString(pCertContext,
			CERT_NAME_ATTR_TYPE,
			0,
			NULL,
			NULL,
			0)))
		{
			__leave;
		}

		// Allocate memory for subject name.
		szName = (LPTSTR)LocalAlloc(LPTR, dwData * sizeof(TCHAR));
		if (!szName)
		{
			__leave;
		}

		// Get subject name.
		if (!(CertGetNameString(pCertContext,
			CERT_NAME_ATTR_TYPE,
			0,
			NULL,
			szName,
			dwData)))
		{
			__leave;
		}

		info.m_strSignCompany = szName;

		fReturn = TRUE;
	}
	__finally
	{
		if (szName != NULL) LocalFree(szName);
	}

	return fReturn;
}

LPWSTR CVerySign::AllocateAndCopyWideString(LPCWSTR inputString)
{
	LPWSTR outputString = NULL;

	outputString = (LPWSTR)LocalAlloc(LPTR,
		(wcslen(inputString) + 1) * sizeof(WCHAR));
	if (outputString != NULL)
	{
		lstrcpyW(outputString, inputString);
	}
	return outputString;
}

BOOL CVerySign::GetProgAndPublisherInfo(PCMSG_SIGNER_INFO pSignerInfo,
										PSPROG_PUBLISHERINFO Info)
{
	BOOL fReturn = FALSE;
	PSPC_SP_OPUS_INFO OpusInfo = NULL;  
	DWORD dwData;
	BOOL fResult;

	__try
	{
		// Loop through authenticated attributes and find
		// SPC_SP_OPUS_INFO_OBJID OID.
		for (DWORD n = 0; n < pSignerInfo->AuthAttrs.cAttr; n++)
		{          
			if (lstrcmpA(SPC_SP_OPUS_INFO_OBJID,
				pSignerInfo->AuthAttrs.rgAttr[n].pszObjId) == 0)
			{
				// Get Size of SPC_SP_OPUS_INFO structure.
				fResult = CryptDecodeObject(ENCODING,
					SPC_SP_OPUS_INFO_OBJID,
					pSignerInfo->AuthAttrs.rgAttr[n].rgValue[0].pbData,
					pSignerInfo->AuthAttrs.rgAttr[n].rgValue[0].cbData,
					0,
					NULL,
					&dwData);
				if (!fResult)
				{

					__leave;
				}

				// Allocate memory for SPC_SP_OPUS_INFO structure.
				OpusInfo = (PSPC_SP_OPUS_INFO)LocalAlloc(LPTR, dwData);
				if (!OpusInfo)
				{

					__leave;
				}

				// Decode and get SPC_SP_OPUS_INFO structure.
				fResult = CryptDecodeObject(ENCODING,
					SPC_SP_OPUS_INFO_OBJID,
					pSignerInfo->AuthAttrs.rgAttr[n].rgValue[0].pbData,
					pSignerInfo->AuthAttrs.rgAttr[n].rgValue[0].cbData,
					0,
					OpusInfo,
					&dwData);
				if (!fResult)
				{

					__leave;
				}

				int csz = 0;
				csz = CertNameToStr(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, &pSignerInfo->Issuer, CERT_X500_NAME_STR, NULL, csz);
				wchar_t* psz = new wchar_t[csz];
				CertNameToStr(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, &pSignerInfo->Issuer, CERT_X500_NAME_STR, psz, csz);

				// Fill in Program Name if present.
				if (OpusInfo->pwszProgramName)
				{
					Info->lpszProgramName =
						AllocateAndCopyWideString(OpusInfo->pwszProgramName);
				}
				else
					Info->lpszProgramName = NULL;

				// Fill in Publisher Information if present.
				if (OpusInfo->pPublisherInfo)
				{

					switch (OpusInfo->pPublisherInfo->dwLinkChoice)
					{
					case SPC_URL_LINK_CHOICE:
						Info->lpszPublisherLink =
							AllocateAndCopyWideString(OpusInfo->pPublisherInfo->pwszUrl);
						break;

					case SPC_FILE_LINK_CHOICE:
						Info->lpszPublisherLink =
							AllocateAndCopyWideString(OpusInfo->pPublisherInfo->pwszFile);
						break;

					default:
						Info->lpszPublisherLink = NULL;
						break;
					}
				}
				else
				{
					Info->lpszPublisherLink = NULL;
				}

				// Fill in More Info if present.
				if (OpusInfo->pMoreInfo)
				{
					switch (OpusInfo->pMoreInfo->dwLinkChoice)
					{
					case SPC_URL_LINK_CHOICE:
						Info->lpszMoreInfoLink =
							AllocateAndCopyWideString(OpusInfo->pMoreInfo->pwszUrl);
						break;

					case SPC_FILE_LINK_CHOICE:
						Info->lpszMoreInfoLink =
							AllocateAndCopyWideString(OpusInfo->pMoreInfo->pwszFile);
						break;

					default:
						Info->lpszMoreInfoLink = NULL;
						break;
					}
				}              
				else
				{
					Info->lpszMoreInfoLink = NULL;
				}

				fReturn = TRUE;

				break; // Break from for loop.
			} // lstrcmp SPC_SP_OPUS_INFO_OBJID                
		} // for
	}
	__finally
	{
		if (OpusInfo != NULL) LocalFree(OpusInfo);      
	}

	return fReturn;
}

BOOL CVerySign::GetDateOfTimeStamp(PCMSG_SIGNER_INFO pSignerInfo, SYSTEMTIME *st)
{  
	BOOL fResult;
	FILETIME lft, ft;  
	DWORD dwData;
	BOOL fReturn = FALSE;

	// Loop through authenticated attributes and find
	// szOID_RSA_signingTime OID.
	for (DWORD n = 0; n < pSignerInfo->AuthAttrs.cAttr; n++)
	{          
		if (lstrcmpA(szOID_RSA_signingTime,
			pSignerInfo->AuthAttrs.rgAttr[n].pszObjId) == 0)
		{              
			// Decode and get FILETIME structure.
			dwData = sizeof(ft);
			fResult = CryptDecodeObject(ENCODING,
				szOID_RSA_signingTime,
				pSignerInfo->AuthAttrs.rgAttr[n].rgValue[0].pbData,
				pSignerInfo->AuthAttrs.rgAttr[n].rgValue[0].cbData,
				0,
				(PVOID)&ft,
				&dwData);
			if (!fResult)
			{

				break;
			}

			// Convert to local time.
			FileTimeToLocalFileTime(&ft, &lft);
			FileTimeToSystemTime(&lft, st);

			fReturn = TRUE;

			break; // Break from for loop.

		} //lstrcmp szOID_RSA_signingTime
	} // for

	return fReturn;
}

BOOL CVerySign::GetTimeStampSignerInfo(PCMSG_SIGNER_INFO pSignerInfo, PCMSG_SIGNER_INFO *pCounterSignerInfo)
{  
	PCCERT_CONTEXT pCertContext = NULL;
	BOOL fReturn = FALSE;
	BOOL fResult;      
	DWORD dwSize;  

	__try
	{
		*pCounterSignerInfo = NULL;

		// Loop through unathenticated attributes for
		// szOID_RSA_counterSign OID.
		for (DWORD n = 0; n < pSignerInfo->UnauthAttrs.cAttr; n++)
		{
			if (lstrcmpA(pSignerInfo->UnauthAttrs.rgAttr[n].pszObjId,
				szOID_RSA_counterSign) == 0)
			{
				// Get size of CMSG_SIGNER_INFO structure.
				fResult = CryptDecodeObject(ENCODING,
					PKCS7_SIGNER_INFO,
					pSignerInfo->UnauthAttrs.rgAttr[n].rgValue[0].pbData,
					pSignerInfo->UnauthAttrs.rgAttr[n].rgValue[0].cbData,
					0,
					NULL,
					&dwSize);
				if (!fResult)
				{

					__leave;
				}

				// Allocate memory for CMSG_SIGNER_INFO.
				*pCounterSignerInfo = (PCMSG_SIGNER_INFO)LocalAlloc(LPTR, dwSize);
				if (!*pCounterSignerInfo)
				{

					__leave;
				}

				// Decode and get CMSG_SIGNER_INFO structure
				// for timestamp certificate.
				fResult = CryptDecodeObject(ENCODING,
					PKCS7_SIGNER_INFO,
					pSignerInfo->UnauthAttrs.rgAttr[n].rgValue[0].pbData,
					pSignerInfo->UnauthAttrs.rgAttr[n].rgValue[0].cbData,
					0,
					(PVOID)*pCounterSignerInfo,
					&dwSize);
				if (!fResult)
				{

					__leave;
				}

				fReturn = TRUE;

				break; // Break from for loop.
			}          
		}
	}
	__finally
	{
		// Clean up.
		if (pCertContext != NULL) CertFreeCertificateContext(pCertContext);
	}

	return fReturn;
}

int CVerySign::GetSignedStore(const wchar_t* szFileName, CSignatureInfo& info)
{
	//WCHAR szFileName[MAX_PATH];
	HCERTSTORE hStore = NULL;
	HCRYPTMSG hMsg = NULL;
	PCCERT_CONTEXT pCertContext = NULL;
	BOOL fResult;  
	DWORD dwEncoding, dwContentType, dwFormatType;
	PCMSG_SIGNER_INFO pSignerInfo = NULL;
	PCERT_INFO        pCertInfo = NULL;
	DWORD             dwCertInfo = 0;
	PCMSG_SIGNER_INFO pCounterSignerInfo = NULL;
	DWORD dwSignerInfo;
	CERT_INFO CertInfo;    
	SPROG_PUBLISHERINFO ProgPubInfo;
	SYSTEMTIME st;

	BOOL bRet = FALSE;

	ZeroMemory(&ProgPubInfo, sizeof(ProgPubInfo));
	__try
	{
		// Get message handle and store handle from the signed file.
		fResult = CryptQueryObject(CERT_QUERY_OBJECT_FILE,
			(const void *)szFileName,
			CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED,
			CERT_QUERY_FORMAT_FLAG_BINARY,
			0,
			&dwEncoding,
			&dwContentType,
			&dwFormatType,
			&hStore,
			&hMsg,
			NULL);
		if (!fResult)
		{

			__leave;
		}

		// Get signer information size.
		fResult = CryptMsgGetParam(hMsg,
			CMSG_SIGNER_INFO_PARAM,
			0,
			NULL,
			&dwSignerInfo);
		if (!fResult)
		{

			__leave;
		}

		// Allocate memory for signer information.
		pSignerInfo = (PCMSG_SIGNER_INFO)LocalAlloc(LPTR, dwSignerInfo);
		if (!pSignerInfo)
		{

			__leave;
		}

		// Get Signer Information.
		fResult = CryptMsgGetParam(hMsg,
			CMSG_SIGNER_INFO_PARAM,
			0,
			(PVOID)pSignerInfo,
			&dwSignerInfo);
		if (!fResult)
		{

			__leave;
		}

		// Get signer information size.
		fResult = CryptMsgGetParam(hMsg,
			CMSG_SIGNER_CERT_INFO_PARAM,
			0,
			NULL,
			&dwCertInfo);
		if (!fResult)
		{

			__leave;
		}

		// Allocate memory for signer information.
		pCertInfo = (PCERT_INFO)LocalAlloc(LPTR, dwCertInfo);
		if (!pCertInfo)
		{

			__leave;
		}

		// Get Signer Information.
		fResult = CryptMsgGetParam(hMsg,
			CMSG_SIGNER_CERT_INFO_PARAM,
			0,
			(PVOID)pCertInfo,
			&dwCertInfo);
		if (!fResult)
		{

			__leave;
		}

		// Get program name and publisher information from
		// signer info structure.
		if (GetProgAndPublisherInfo(pSignerInfo, &ProgPubInfo))
		{
			if (ProgPubInfo.lpszProgramName != NULL)
			{
				info.m_strProgramName = ProgPubInfo.lpszProgramName;
			}

			if (ProgPubInfo.lpszPublisherLink != NULL)
			{
				info.m_strPublisherLink = ProgPubInfo.lpszPublisherLink;
			}

			if (ProgPubInfo.lpszMoreInfoLink != NULL)
			{
				info.m_strMoreInfoLink = ProgPubInfo.lpszMoreInfoLink;
			}  
		}


		// Search for the signer certificate in the temporary
		// certificate store.
		CertInfo.Issuer = pSignerInfo->Issuer;
		CertInfo.SerialNumber = pSignerInfo->SerialNumber;

		pCertContext = CertFindCertificateInStore(hStore,
			ENCODING,
			0,
			CERT_FIND_SUBJECT_CERT,
			(PVOID)&CertInfo,
			NULL);
		if (!pCertContext)
		{

			__leave;
		}

		// Print Signer certificate information.
		GetCertificateInfo(pCertContext, info);

		// Get the timestamp certificate signerinfo structure.
		if (GetTimeStampSignerInfo(pSignerInfo, &pCounterSignerInfo))
		{
			// Search for Timestamp certificate in the temporary
			// certificate store.
			CertInfo.Issuer = pCounterSignerInfo->Issuer;
			CertInfo.SerialNumber = pCounterSignerInfo->SerialNumber;

			pCertContext = CertFindCertificateInStore(hStore,
				ENCODING,
				0,
				CERT_FIND_SUBJECT_CERT,
				(PVOID)&CertInfo,
				NULL);
			if (!pCertContext)
			{

				__leave;
			}

			// Find Date of timestamp.
			if (GetDateOfTimeStamp(pCounterSignerInfo, &st))
			{
				wchar_t szTimeStamp[128] = {0};

				swprintf_s(szTimeStamp,_countof(szTimeStamp), L"%02d/%02d/%04d %02d:%02d",
					st.wMonth,
					st.wDay,
					st.wYear,
					st.wHour,
					st.wMinute);

				info.m_strTimestamp = szTimeStamp;

			}

		}

		bRet = TRUE;
	}
	__finally
	{              
		if (ProgPubInfo.lpszProgramName != NULL)
			LocalFree(ProgPubInfo.lpszProgramName);
		if (ProgPubInfo.lpszPublisherLink != NULL)
			LocalFree(ProgPubInfo.lpszPublisherLink);
		if (ProgPubInfo.lpszMoreInfoLink != NULL)
			LocalFree(ProgPubInfo.lpszMoreInfoLink);

		if (pSignerInfo != NULL) LocalFree(pSignerInfo);
		if (pCounterSignerInfo != NULL) LocalFree(pCounterSignerInfo);
		if (pCertContext != NULL) CertFreeCertificateContext(pCertContext);
		if (hStore != NULL) CertCloseStore(hStore, 0);
		if (hMsg != NULL) CryptMsgClose(hMsg);
	}

	return bRet;
}
