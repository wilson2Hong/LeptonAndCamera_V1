#ifndef LEPTONANDCAMERA_H
#define LEPTONANDCAMERA_H

#include <QMainWindow>

#include "leptonandcamera.h"


#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <QTimer>
#include <QString>
#include <QDebug>

namespace Ui {
class LeptonAndCamera;
}

class LeptonAndCamera : public QMainWindow
{
    Q_OBJECT

public:
    explicit LeptonAndCamera(QWidget *parent = 0);
    ~LeptonAndCamera();


private slots:
    void openCamara();      // 打开摄像头
    void readFarme();       // 读取当前帧信息
    void closeCamara();     // 关闭摄像头。
    void takingPictures();  // 拍照

private:
    Ui::LeptonAndCamera *ui;
    QTimer    *timer;
    QImage    *imag;
    CvCapture *cam;  // 视频获取结构， 用来作为视频获取函数的一个参数
    IplImage  *frame;//申请IplImage类型指针，就是申请内存空间来存放每一帧图像
};

#endif // LEPTONANDCAMERA_H
