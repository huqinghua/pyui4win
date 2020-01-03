#pragma  once

/*
------------------导出函数--------------
*/

BOOL  __stdcall XLInitDownloadEngine();

DWORD __stdcall XLURLDownloadToFile(LPCTSTR pszFileName, LPCTSTR pszUrl, LPCTSTR pszRefUrl, LONG & lTaskId);

DWORD __stdcall XLQueryTaskInfo(LONG lTaskId, LONG *plStatus, ULONGLONG *pullFileSize, ULONGLONG *pullRecvSize);

DWORD __stdcall XLPauseTask(LONG lTaskId, LONG & lNewTaskId);

DWORD __stdcall XLContinueTask(LONG lTaskId);

DWORD __stdcall XLContinueTaskFromTdFile(LPCTSTR pszTdFileFullPath, LONG & lTaskId);

VOID  __stdcall XLStopTask(LONG lTaskId);

BOOL  __stdcall XLUninitDownloadEngine();

DWORD __stdcall XLGetErrorMsg(DWORD dwErrorId, LPTSTR pszBuffer, DWORD & dwSize);


/*
----------------------类型定义-----------------
*/
enum enumTaskStatus{
	enumTaskStatus_Connect = 0,                 // 已经建立连接
	enumTaskStatus_Download = 2,                // 开始下载 
	enumTaskStatus_Pause = 10,                  // 暂停
	enumTaskStatus_Success = 11,                // 成功下载
	enumTaskStatus_Fail = 12,                   // 下载失败
};