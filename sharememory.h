#ifndef SHAREMEMORY_H
#define SHAREMEMORY_H

#include "windows.h"

class ShareMemory
{
public:
    ShareMemory();
    ShareMemory(LPCWSTR memoryBlcokName, LPVOID data, int bufferSize);
    ~ShareMemory();
    int CreateMemoryBlock();
    int OpenMemoryBlock();
    int GetMappingDataMemory();
    int ReadDataFromMemoryBlcok(BYTE *pData);
    int WriteDataIntoMemoryBlcok();
    int ReleaseMemoryBlock();
    DWORD GetErrorMessage();

///
///Property
///

    void SetMemoryBlockName(LPCWSTR memoryBlcokName);
    LPCWSTR GetMemoryBlockName();

    void SetData(LPVOID Data);
    LPVOID GetData();

    void SetDataBufferSize(int BufferSize);
    int GetDataBufferSize();

private:
    HANDLE m_hFile = 0;//Share memory Handle
    LPCWSTR m_MemoryBlcokName = 0;//Memory Block Name
    LPVOID m_pData = 0;//Data in memory
    int m_iBufferSize = 0;//Memory(Data) Size
    BYTE* m_pBuf = 0;//Temp Data




};

#endif // SHAREMEMORY_H
