#include "sharememory.h"


enum  enumErrorStatus
{
    NoErrorOccur = 1,
    CreateMemoryBlockFail = -1,
    MemoryBlockisAlreadyExist = -2,
    OpenMemoryBlockFail =-3,
    GetMappingDataMemoryFail = -4,
    EmtpyDataPointer =-5,
    DataBufferNotMatch = -6
};

ShareMemory::ShareMemory()
{
  this->m_pData=nullptr;
}

ShareMemory::ShareMemory(LPCWSTR memoryBlcokName, LPVOID data, int bufferSize)
{
    this->m_MemoryBlcokName = memoryBlcokName;
    this->m_pData = data;
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

int ShareMemory::ReadDataFromMemoryBlcok(BYTE* pData)
{
    if(m_pBuf == nullptr)
    {
        return EmtpyDataPointer;
    }

//    if(sizeof(m_pBuf) != m_iBufferSize)
//    {
//        return DataBufferNotMatch;
//    }
    //output,input
    memcpy(pData, m_pBuf, m_iBufferSize);

    return NoErrorOccur;
}

int ShareMemory::WriteDataIntoMemoryBlcok()
{
    if(m_pData == nullptr)
    {
        return EmtpyDataPointer;
    }
    if(sizeof(m_pData) != m_iBufferSize)
    {
        return DataBufferNotMatch;
    }

    memcpy(m_pBuf, (BYTE*)m_pData, m_iBufferSize);

    return NoErrorOccur;
}

int ShareMemory::ReleaseMemoryBlock()
{
    if(m_hFile != nullptr)
    {
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

void ShareMemory::SetData(LPVOID Data)
{
    this->m_pData = Data;
}

LPVOID ShareMemory::GetData()
{
    return this->m_pBuf;
}

void ShareMemory::SetDataBufferSize(int BufferSize)
{
    this->m_iBufferSize = BufferSize;
}

int ShareMemory::GetDataBufferSize()
{
    return this->m_iBufferSize;
}
