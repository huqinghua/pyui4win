
#pragma once
#include <shlwapi.h>
#pragma comment (lib, "shlwapi.lib")

//-------------------------------------------------------------------------------------
/**
    File helper.
*/
class FCFileEx
{
public:
    /**
        Get folder that module locate, with backslash('\') append \n
        hModule - NULL to get current process folder.
    */
    static CString GetModuleFolder (HMODULE hModule=NULL)
    {
        TCHAR   s[MAX_PATH] = {0} ;
        GetModuleFileName (hModule, s, MAX_PATH) ;
        PathRemoveFileSpec (s) ;
        PathAddBackslash (s) ;
        return s ;
    }

    /// Get folder that file locate, with backslash('\') append.
    static CString GetFileFolder (LPCTSTR strFilename)
    {
        TCHAR   s[MAX_PATH] = {0} ;
		_tcscpy_s(s, MAX_PATH, strFilename) ;
        PathRemoveFileSpec (s) ;
        PathAddBackslash (s) ;
        return s ;
    }

    /// Get file's size.
    static INT64 GetSize (LPCTSTR strFilename)
    {
        WIN32_FILE_ATTRIBUTE_DATA   fd ;
        if (GetFileAttributesEx (strFilename, GetFileExInfoStandard, &fd))
        {
            LARGE_INTEGER   n ;
            n.LowPart = fd.nFileSizeLow ;
            n.HighPart = (LONG)fd.nFileSizeHigh ;
            return n.QuadPart ;
        }
        return 0 ;
    }

    /// Get file's extension name, not including leading period.
    static CString GetExtName (LPCTSTR strFilename)
    {
        LPCTSTR   p = PathFindExtension(strFilename) ;
        if (p && (*p == '.'))
            return (p+1) ;
        return _T("") ;
    }

    /**
        Read file to memory, must use <B>delete[]</B> to free received buffer, \n
        the received buffer with 2-byte 0 followed, so you can convert to string directly.
    */
    static void Read (LPCTSTR strFilename, void*& pBuffer, int& nLength)
    {
        pBuffer = NULL ;
        nLength = 0 ;

        BOOL     b = FALSE ;
        HANDLE   f = CreateFile (strFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL) ;
        if (f != INVALID_HANDLE_VALUE)
        {
            nLength = ::GetFileSize(f, NULL) ;
            if (nLength)
            {
                pBuffer = new BYTE[nLength + 2] ;
                ZeroMemory (pBuffer, nLength + 2) ;

                DWORD   dwRead ;
                ::ReadFile (f, pBuffer, nLength, &dwRead, NULL) ;
                b = ((int)dwRead == nLength) ;
            }
            CloseHandle (f) ;
        }
       // assert(b && nLength) ;
    }

    /// Write buffer to file, if file already exist, it will be delete before write.
    static BOOL Write (LPCTSTR strFilename, const void* p, int nLength)
    {
        SetFileAttributes (strFilename, FILE_ATTRIBUTE_NORMAL) ;

        BOOL     b = FALSE ;
        HANDLE   f = CreateFile (strFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL) ;
        if (f != INVALID_HANDLE_VALUE)
        {
            DWORD   nWrite ;
            ::WriteFile (f, p, nLength, &nWrite, NULL) ;
            b = ((int)nWrite == nLength) ;
            CloseHandle (f) ;
        }
       // assert(b) ;
        return b ;
    }

    /// Get a temp file path.
    static CString QueryTempFilePath()
    {
        TCHAR   szTmpPath[MAX_PATH],
                szFilename[MAX_PATH] ;
        ::GetTempPath (MAX_PATH, szTmpPath) ;
        ::GetTempFileName (szTmpPath, _T("t"), 0, szFilename) ;
        return szFilename ;
    }

    /**
        @name Read/Write INI file.
    */
    //@{
    /// Read string key from ini file, return FALSE if key doesn't exist.
    static BOOL INIRead (LPCTSTR strFilename, LPCTSTR strKey, CString& s, LPCTSTR strSection=_T("app"))
    {
        TCHAR   b[512] ;
        DWORD   dwWrite = GetPrivateProfileString (strSection, strKey, _T("\n"), b, 512, strFilename) ;
        if ((b[0] == '\n') && (b[1] == 0))
            return FALSE ;

        if (dwWrite > (512 - 8))
        {
            TCHAR   * p = new TCHAR[4096] ;
            GetPrivateProfileString (strSection, strKey, _T("\n"), p, 4096, strFilename) ;
            s = p ;
            delete[] p ;
        }
        else
        {
            s = b ;
        }
        return TRUE ;
    }

    /// Read int key from ini file, return FALSE if key doesn't exist.
    static BOOL INIRead (LPCTSTR strFilename, LPCTSTR strKey, INT64& n, LPCTSTR strSection=_T("app"))
    {
        TCHAR   b[32] ;
        GetPrivateProfileString (strSection, strKey, _T("\n"), b, 32, strFilename) ;
        if ((b[0] == '\n') && (b[1] == 0))
            return FALSE ;

        n = _ttoi64(b) ;
        return TRUE ;
    }

    /// Write a int key to ini file.
    static BOOL INIWrite (LPCTSTR strFilename, LPCTSTR strKey, INT64 n, LPCTSTR strSection=_T("app"))
    {
        CString   s ;
        s.Format(_T("%I64d"), n) ;
        return INIWrite (strFilename, strKey, s, strSection) ;
    }

    /// Write a string key to ini file.
    static BOOL INIWrite (LPCTSTR strFilename, LPCTSTR strKey, LPCTSTR strValue, LPCTSTR strSection=_T("app"))
    {
        return WritePrivateProfileString (strSection, strKey, strValue, strFilename) ;
    }
    //@}
};
