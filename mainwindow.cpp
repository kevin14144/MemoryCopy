#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include<qdebug.h>
#define SHAREMEM_NAME   "shareMemory"
#define BULID_MESSAGE   "Hello! I am burn at " __DATE__ " " __TIME__
//http://pws.niu.edu.tw/~ttlee/os.101.1/night/sharedMemory/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::on_btnCopyData_clicked()
{

    LPVOID  pBuf;
    HANDLE hFile;
    int i;
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

    pBuf=MapViewOfFile(
    hFile,
    FILE_MAP_ALL_ACCESS,
    0,
    0,
    sizeof(writeBuffer)
    );

    strcat((char *)pBuf,BULID_MESSAGE"\n");


    while(1){
    memcpy((void*)pBuf, (BYTE*)BULID_MESSAGE, sizeof(BULID_MESSAGE));
    strcat((char *)pBuf, std::to_string(i).c_str());
    qDebug()<<(char*)pBuf;
    Sleep(1000);
    i++;
    }

    CloseHandle(hFile);
}

void MainWindow::on_pushButton_clicked()
{
    LPCTSTR pBuf;
    HANDLE hFile;
    int i;


    char szFileName[] = SHAREMEM_NAME;
    //char szFileName[] = "shareMemory1";
    char writeBuffer[128]={0};

    hFile = OpenFileMapping(
         FILE_MAP_ALL_ACCESS,
         FALSE,
         (LPCWSTR)szFileName
    );

    if(NULL == hFile){
       //it is new
       hFile = CreateFileMapping(
         INVALID_HANDLE_VALUE,
         NULL,
         PAGE_READWRITE,
         0,
         sizeof(writeBuffer),
         (LPCWSTR)szFileName
       );

       if(nullptr == hFile){
         qDebug()<<"Could not create file mapping object"<< GetLastError();

         return;
       }
    }else{
      //created
      qDebug()<<"Share memory ready!\n";

    }

    //get share memory mapping location (address)
    pBuf = (LPCTSTR)MapViewOfFile(
      hFile,
      FILE_MAP_ALL_ACCESS,
      0,
      0,
      sizeof(writeBuffer)
    );



    if(NULL == pBuf){
          qDebug()<<"Could not map view of file"<<GetLastError();

      CloseHandle(hFile);
      return;
    }


//create new line to say hello
    //strcat((char *)pBuf,BULID_MESSAGE"\n");

    while(1){
      //memcpy((void*)pBuf, (BYTE*)BULID_MESSAGE, sizeof(BULID_MESSAGE));
      //strcat((char *)pBuf, std::to_string(i).c_str());
      //show string on share memory
      qDebug()<<(char*)pBuf;
      Sleep(100);
      i++;
    }
    CloseHandle(hFile);
}


