#include "sharememory.h"


enum  enumErrorStatus
{
    NoErrorOccur = 1,
    CreateMemoryBlockFail = -1,
    MemoryBlockisAlreadyExist = -2,
    OpenMemoryBlockFail =-3,
    GetMappingDataMemoryFail = -4,
    EmtpyDataPointer =-5,
    DataBufferNotMatch = -6,
    UnmapViewOfFileFail =-7
};

ShareMemory::ShareMemory()
{

}

ShareMemory::ShareMemory(LPCWSTR memoryBlcokName, int bufferSize)
{
    this->m_MemoryBlcokName = memoryBlcokName;
    this->m_iBufferSize = bufferSize;
}

ShareMemory::~ShareMemory()
{
    ShareMemory::ReleaseMemoryBlock();
}

int ShareMemory::CreateMemoryBlock()
{
    //Is the memory block exist ?
    m_hFile = OpenFileMapping(
                FILE_MAP_ALL_ACCESS,
                FALSE,
                m_MemoryBlcokName
                );

    if(m_hFile != nullptr)
    {
        return MemoryBlockisAlreadyExist;
    }
    else//Create the memory blcok.
    {
        m_hFile = CreateFileMapping(
                    INVALID_HANDLE_VALUE,
                    NULL,
                    PAGE_READWRITE,
                    0,
                    m_iBufferSize,
                    m_MemoryBlcokName
                    );

        if(m_hFile == nullptr)
        {
            return CreateMemoryBlockFail;
        }

    }
    return NoErrorOccur;
}

int ShareMemory::OpenMemoryBlock()
{
    m_hFile = OpenFileMapping(
                FILE_MAP_ALL_ACCESS,
                FALSE,
                m_MemoryBlcokName
                );
    if(m_hFile != nullptr)
    {
        return NoErrorOccur;
    }
    else
    {
        return OpenMemoryBlockFail;
    }
}

int ShareMemory::GetMappingDataMemory()
{
    if(m_hFile == nullptr)
    {
        return OpenMemoryBlockFail;
    }

    m_pBuf = (BYTE*)MapViewOfFile(
                m_hFile,
                FILE_MAP_ALL_ACCESS,
                0,
                0,
                m_iBufferSize
                );

    if(m_pBuf != nullptr)
    {
        return NoErrorOccur;
    }
    else
    {
        return GetMappingDataMemoryFail;
    }
}

int ShareMemory::ReleaseMemoryBlock()
{
    if(m_hFile != nullptr)
    {
        if(m_pBuf !=nullptr)
        {
            if (!UnmapViewOfFile(m_pBuf))
            {
                m_pBuf = nullptr;
            }
        }
        if(CloseHandle(m_hFile))
        {
            m_hFile = nullptr;
        }
    }
    return NoErrorOccur;
}

DWORD ShareMemory::GetErrorMessage()
{
    return GetLastError();
}

void ShareMemory::SetMemoryBlockName(LPCWSTR memoryBlcokName)
{
    this->m_MemoryBlcokName = memoryBlcokName;
}

LPCWSTR ShareMemory::GetMemoryBlockName()
{
    return this->m_MemoryBlcokName;
}

int ShareMemory::WriteData(LPVOID Data)
{
    if(Data == nullptr)
    {
        return EmtpyDataPointer;
    }

    memcpy(m_pBuf, (BYTE*)Data, m_iBufferSize);

    if (!UnmapViewOfFile(m_pBuf))
    {
        return UnmapViewOfFileFail;
    }

    m_pBuf = nullptr;

    return NoErrorOccur;

}

int ShareMemory::ReadData(LPVOID Data)
{
    if(m_pBuf == nullptr)
    {
        return EmtpyDataPointer;
    }

    //記憶體區域複製
    memcpy((BYTE*)Data, m_pBuf, m_iBufferSize);

    //字元複製
    //strcpy(Data,m_pBuf);

    if (!UnmapViewOfFile(m_pBuf))
    {
        return UnmapViewOfFileFail;
    }

    m_pBuf = nullptr;

    return NoErrorOccur;
}

void ShareMemory::SetDataBufferSize(int BufferSize)
{
    this->m_iBufferSize = BufferSize;
}

int ShareMemory::GetDataBufferSize()
{
    return this->m_iBufferSize;
}
