#include "leptonandcamera.h"
#include <QApplication>

#include <QThread>
#include <QMutex>
#include <QMessageBox>

#include <QColor>
#include <QLabel>
#include <QtDebug>
#include <QString>
#include <QPushButton>

#include "LeptonThread.h"
#include "MyLabel.h"

#include"cv.h"
#include"highgui.h"
#include"iostream"
#include <QTimer>


using namespace std;

int main(int argc, char *argv[])
{

    //create the app
    QApplication a(argc, argv);
    LeptonAndCamera w;
    //w.show();

    QWidget *myWidget = new QWidget;
    myWidget->setGeometry(10, 10, 760, 290);
    myWidget->setFixedSize(760,290);

    //create an image placeholder for myLabel
    //fill the top left corner with red, just bcuz
    QImage myImage;
    myImage = QImage(320, 240, QImage::Format_RGB888);
    QRgb red = qRgb(255,0,0);
    for(int i=0;i<80;i++)
    {
        for(int j=0;j<60;j++)
        {
            myImage.setPixel(i, j, red);
        }
    }

    //**********2018  12 05 lixicai *********
    //cvNamedWindow("img",1);
    CvCapture* cap;
    cap=cvCaptureFromCAM(0);
    if(!cap)
    {
        cout<<"create camera capture error"<<endl;
        system("pause");
        exit(-1);
    }
    IplImage* img;
    //进入循环前，等待一段时间摄像头初始化，否则初始化未完成，会直接闪退出程序
    cvWaitKey(2000);


    LeptonAndCamera lptime;
    //create a label, and set it's image to the placeholder
    MyLabel myLabel(myWidget);
    myLabel.setGeometry(10, 10, 320, 240);
    myLabel.setPixmap(QPixmap::fromImage(myImage));

    MyLabel myLabelcamera(myWidget);
    myLabelcamera.setGeometry(350, 10, 400, 270);
    myLabelcamera.setPixmap(QPixmap::fromImage(myImage));

    //create a FFC button
    QPushButton *button1 = new QPushButton("Perform FFC", myWidget);
    button1->setGeometry(320/2-50, 290-35, 100, 30);

    //create a thread to gather SPI data
    //when the thread emits updateImage, the label should update its image accordingly
    LeptonThread *thread = new LeptonThread();
    QObject::connect(thread, SIGNAL(updateImage(QImage)), &myLabel, SLOT(setImage(QImage)));

    //connect ffc button to the thread's ffc action
    QObject::connect(button1, SIGNAL(clicked()), thread, SLOT(performFFC()));
    thread->start();

    myWidget->show();

    //*************while***********
    while(1)
    {
     img=cvQueryFrame(cap);//读入视频解码
     if(!img)
     break;
     cvWaitKey(3);

     img = cvQueryFrame(cap);// 从摄像头中抓取并返回每一帧
     //cvShowImage("img",img);
     // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。
     QImage image =  QImage ((const uchar*)img->imageData, img->width, img->height, QImage::Format_RGB888).rgbSwapped();

     int a = myLabelcamera.width();
     int b = myLabelcamera.height();
     qDebug("a=%d ",a);
     qDebug("b=%d ",b);
     QImage img = image.scaled(a, b);    //自定义缩放
     myLabelcamera.setPixmap(QPixmap::fromImage(img));   // 将图片显示到label上
    }

    cvReleaseCapture(&cap);
    cvDestroyAllWindows();
    cvReleaseImage(&img);

    return a.exec();
}

