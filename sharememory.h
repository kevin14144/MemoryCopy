#ifndef SHAREMEMORY_H
#define SHAREMEMORY_H

#include "windows.h"

class ShareMemory
{
public:
    ShareMemory();
private:
    HANDLE m_hFile =0;
    LPVOID m_pBuf =0;
    LPVOID m_pData =0;
    int m_iBufferSize =0;
    LPCWSTR m_cMemoryBlcokName =0;

};

#endif // SHAREMEMORY_H
