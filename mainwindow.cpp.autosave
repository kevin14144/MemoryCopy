#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include "sharememory.h"
#include<qdebug.h>
#define SHAREMEM_NAME   "shareMemory"
#define BULID_MESSAGE   "Hello! I am burn at " __DATE__ " " __TIME__
//http://pws.niu.edu.tw/~ttlee/os.101.1/night/sharedMemory/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnReadData,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_clicked()));
    connect(ui->btnWriteData,SIGNAL(clicked(bool)),this,SLOT(on_btnCopyData_clicked()));
    connect(ui->btnCreateMemory,SIGNAL(clicked(bool)),this,SLOT(on_btnCreateMemory_clicked()));


}

MainWindow::~MainWindow()
{
    delete ui;
}


int CreateMemoryBlock(HANDLE& hFile, int iBufferSize, char* cMemoryBlcokName)
{
    LPCWSTR lMemoryBlcokName = (LPCWSTR)cMemoryBlcokName;
    //Is the memory block  exist ?
    hFile = OpenFileMapping(
                FILE_MAP_ALL_ACCESS,
                FALSE,
                (LPCWSTR)lMemoryBlcokName
                );

    if(hFile == nullptr)//Create the memory blcok.
    {
        hFile=CreateFileMapping(
                    INVALID_HANDLE_VALUE,
                    NULL,
                    PAGE_READWRITE,
                    0,
                    iBufferSize,
                    lMemoryBlcokName
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

void OpenMemoryBlock(HANDLE hFile, char* cMemoryBlcokName)
{
    LPCWSTR lMemoryBlcokName = (LPCWSTR)cMemoryBlcokName;
    hFile = OpenFileMapping(
                FILE_MAP_ALL_ACCESS,
                FALSE,
                (LPCWSTR)lMemoryBlcokName
                );
}

void GetMemoryData(HANDLE hFile, LPVOID& pBuf, int iBufferSize)
{
    pBuf=MapViewOfFile(
                hFile,
                FILE_MAP_ALL_ACCESS,
                0,
                0,
                iBufferSize
                );
}

void WriteDataIntoMemoryBlcok(LPVOID&  pBuf,LPVOID pData,int iBufferSize)
{
   memcpy((void*)pBuf, (BYTE*)pData, iBufferSize);
}




void MainWindow::on_btnCreateMemory_clicked()
{
    LPVOID  pBuf;
    HANDLE hFile;

    //Dose memory block is exist ?

    if(hFile == nullptr)//
    {
        char szFileName[]=SHAREMEM_NAME;
        char writeBuffer[128]={0};
        hFile=CreateFileMapping(
                    INVALID_HANDLE_VALUE,
                    NULL,
                    PAGE_READWRITE,
                    0,
                    sizeof(writeBuffer),
                    (LPCWSTR)szFileName
                    );

        if(hFile == nullptr)
        {
            qDebug()<<"Could not create file mapping object. Error Codes:"<< GetLastError();
            return;
        }

    }
    else
    {
        qDebug()<<"Share memory ready!\n";
    }

}

int dataLength =0;
void MainWindow::on_btnCopyData_clicked()
{
    ShareMemory* sharememory = new ShareMemory();

    LPVOID temp  = (LPVOID)"asdsssss";
    LPCWSTR memoryBLockName = (LPCWSTR)"UDE_SMer";
    int BufferSize =sizeof(temp);
    dataLength =sizeof(temp);
    sharememory->SetData(temp);
    sharememory->SetMemoryBlockName(memoryBLockName);
    sharememory->SetDataBufferSize(BufferSize);

    sharememory->CreateMemoryBlock();
    sharememory->OpenMemoryBlock();
    sharememory->GetMappingDataMemory();

    sharememory->WriteDataIntoMemoryBlcok();
}

void MainWindow::on_pushButton_clicked()
{

    ShareMemory* sharememory = new ShareMemory();
    LPCWSTR MemoryBlcokName = (LPCWSTR)"UDE_SMer";
    int iBufferSize = dataLength;
    sharememory->SetMemoryBlockName(MemoryBlcokName);
    sharememory->SetDataBufferSize(iBufferSize);
    sharememory->OpenMemoryBlock();
    sharememory->GetMappingDataMemory();

    BYTE* pData = new BYTE;

    sharememory->ReadDataFromMemoryBlcok(pData);


    char* dataGets =  (char*)pData;


   // QString qstrings = (QString)dataGets;

    char* dataGet =  (char*)sharememory->GetData();

    QString qstring = (QString)dataGet;

}



