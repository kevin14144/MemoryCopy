#include "sharememory.h"

ShareMemory::ShareMemory()
{

}

struct ShareCluster
{


};

int CreateMemoryBlock()//HANDLE& hFile, int iBufferSize, char* cMemoryBlcokName
{
    //Is the memory block  exist ?
    hFile = OpenFileMapping(
                FILE_MAP_ALL_ACCESS,
                FALSE,
                m_cMemoryBlcokName
                );

    if(hFile == nullptr)//Create the memory blcok.
    {
        hFile=CreateFileMapping(
                    INVALID_HANDLE_VALUE,
                    NULL,
                    PAGE_READWRITE,
                    0,
                    iBufferSize,
                    m_cMemoryBlcokName
                    );

        if(hFile == nullptr)
        {
            qDebug()<<"Could not create file mapping object. Error Codes:"<< GetLastError();
            return 0;
        }

    }
    else
    {
        qDebug()<<"Share memory ready!\n";
    }

    return 1;

}

void OpenMemoryBlock()//HANDLE hFile, char* cMemoryBlcokName
{
    hFile = OpenFileMapping(
                FILE_MAP_ALL_ACCESS,
                FALSE,
                m_cMemoryBlcokName
                );
}

void GetMemoryData()//HANDLE hFile, LPVOID& pBuf, int iBufferSize
{
    pBuf = MapViewOfFile(
                hFile,
                FILE_MAP_ALL_ACCESS,
                0,
                0,
                iBufferSize
                );
}

void WriteDataIntoMemoryBlcok()//LPVOID&  pBuf,LPVOID pData,int iBufferSize
{
   memcpy((void*)pBuf, (BYTE*)pData, iBufferSize);
}


