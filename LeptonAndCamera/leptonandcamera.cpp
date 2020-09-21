#include "leptonandcamera.h"
#include "ui_leptonandcamera.h"
#include <stddef.h>

LeptonAndCamera::LeptonAndCamera(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LeptonAndCamera)
{
    ui->setupUi(this);
    cam = NULL;

    timer   = new QTimer(this);
    imag    = new QImage();   // 初始化

    this->setFixedSize(this->size());

    /*信号和槽*/
    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  // 时间到，读取当前摄像头信息
    connect(ui->open, SIGNAL(clicked()), this, SLOT(openCamara()));
    connect(ui->pic, SIGNAL(clicked()), this, SLOT(takingPictures()));
    connect(ui->closeCam, SIGNAL(clicked()), this, SLOT(closeCamara()));

    //进入循环前，等待一段时间摄像头初始化，否则初始化未完成，会直接闪退出程序
    closeCamara();
    cvWaitKey(2000);

}

LeptonAndCamera::~LeptonAndCamera()
{
    delete ui;
}

/******************************
********* 打开摄像头 ***********
*******************************/
void LeptonAndCamera::openCamara()
{
    cam = cvCreateCameraCapture(0);//打开摄像头，从摄像头中获取视频
    timer->start(33);              // 开始计时，超时则发出timeout()信号
}

/*********************************
********* 读取摄像头信息 ***********
**********************************/
void LeptonAndCamera::readFarme()
{
    frame = cvQueryFrame(cam);// 从摄像头中抓取并返回每一帧
    // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。
    QImage image =  QImage ((const uchar*)frame->imageData, frame->width, frame->height, QImage::Format_RGB888).rgbSwapped();

    int a = ui->CameraView->width();
    int b = ui->CameraView->height();
    QImage img = image.scaled(a, b);    //自定义缩放
    ui->CameraView->setPixmap(QPixmap::fromImage(img));  // 将图片显示到label上
    qDebug() << "readFarme.";
}

/*************************
********* 拍照 ***********
**************************/
void LeptonAndCamera::takingPictures()
{
    frame = cvQueryFrame(cam);// 从摄像头中抓取并返回每一帧

    // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。
    QImage image((const uchar*)frame->imageData, frame->width, frame->height, QImage::Format_RGB888);

    ui->leptonView->setPixmap(QPixmap::fromImage(image));  // 将图片显示到label上
}

/*******************************
***关闭摄像头，释放资源，必须释放***
********************************/
void LeptonAndCamera::closeCamara()
{
    timer->stop();           // 停止读取数据。
    cvReleaseCapture(&cam);  // 释放内存；
}

