#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stdio.h"
#include "stdlib.h"
#include "windows.h"

#define SHAREMEM_NAME "c:shareMemory"
#define BULID_MESSAGE "Today is"_DATE_" "_TIME_
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

void MainWindow::on_btnCopyData_clicked()
{

    LPCTSTR pBuf;
    HANDLE hFile;
    int i;
    char szFileName[]=SHAREMEM_NAME;
    char writeBuffer[128]={0};

    hFile=CreateFileMapping(
                (HANDLE)0xFFFFFFFF,
                NULL,
                PAGE_READWRITE,
                0,
                sizeof(writeBuffer),
                (LPCWSTR)szFileName
                );

    pBuf=(LPCTSTR)MapViewOfFile(
    hFile,
    FILE_MAP_ALL_ACCESS,
    0,
    0,
    sizeof(writeBuffer)
    );

    //strcat((char*)pBuf,"asd");

    while(1){
    //printf("%s\n",pBuf);
    Sleep(1000);
    }

    CloseHandle(hFile);
}

void MainWindow::on_pushButton_clicked()
{
    LPCTSTR pBuf;
    HANDLE hFile;
    int i;
    char szFileName[]=SHAREMEM_NAME;
    char writeBuffer[128]={0};

    //建立共用記憶體
    //宣告變數
    hFile = OpenFileMapping(
                FILE_MAP_ALL_ACCESS,
                FALSE,
                (LPCWSTR)szFileName
                );

    //開啟分享記憶體
    pBuf=(LPCTSTR)MapViewOfFile(
                hFile,
                FILE_MAP_ALL_ACCESS,
                0,
                0,
                sizeof(writeBuffer)
                );

    //放入自己的位址空間
    while(1){
        printf("%s\n",pBuf);
        Sleep(1000);
    }
    CloseHandle(hFile);
}
