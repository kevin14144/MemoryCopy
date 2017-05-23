#ifndef SHAREMEMORY_H
#define SHAREMEMORY_H

#include "windows.h"

class ShareMemory
{
public:
    ShareMemory();


    ShareMemory(LPCWSTR memoryBlcokName, int bufferSize);
    ~ShareMemory();
    ///
    /// \brief CreateMemoryBlockaasdasdasd
    /// \return imageasd
    ///
    int CreateMemoryBlock();
    int OpenMemoryBlock();
    int GetMappingDataMemory();
    int ReleaseMemoryBlock();
    DWORD GetErrorMessage();

    void SetMemoryBlockName(LPCWSTR memoryBlcokName);
    LPCWSTR GetMemoryBlockName();

    int WriteData(LPVOID Data);
    int ReadData(LPVOID Data);

    void SetDataBufferSize(int BufferSize);
    int GetDataBufferSize();

private:
    HANDLE m_hFile = 0;//Share memory Handle
    LPCWSTR m_MemoryBlcokName = 0;//Memory Block Name
    BYTE* m_pBuf = 0;//Temp Data
    int m_iBufferSize = 0;//Memory(Data) Size





};

#endif // SHAREMEMORY_H
