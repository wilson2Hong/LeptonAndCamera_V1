#include "LeptonThread.h"


#include "leptonSDKEmb32PUB/LEPTON_SDK.h"
#include "leptonSDKEmb32PUB/LEPTON_SYS.h"
#include "leptonSDKEmb32PUB/LEPTON_AGC.h"
#include "leptonSDKEmb32PUB/LEPTON_Types.h"

#include "Palettes.h"
#include "SPI.h"
#include "Lepton_I2C.h"
#include <iostream>
#include <vector>
#include <QString>
#include <QDebug>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#define PACKET_SIZE 164
#define PACKET_SIZE_UINT16 (PACKET_SIZE/2)
#define PACKETS_PER_FRAME 60
#define FRAME_SIZE_UINT16 (PACKET_SIZE_UINT16*PACKETS_PER_FRAME)
#define FPS 27;



bool _AGCconnected;

LEP_CAMERA_PORT_DESC_T _AGCport;
LEP_AGC_ENABLE_E _AGCState;


LeptonThread::LeptonThread() : QThread()
{
}

LeptonThread::~LeptonThread() {
}

void LeptonThread::run()
{
    //create the initial image
    //myImage = QImage(80, 60, QImage::Format_RGB888);
    QImage myImage ;

    //open spi port
    SpiOpenPort(0);

    //串口初始化(ttyAMA0)
    if((serialPortfd = serialOpen("/dev/ttyAMA0",115200)) < 0)
    {
        fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
    }


    if(!_AGCconnected) {
        LEP_OpenPort(1, LEP_CCI_TWI, 400, &_AGCport);
        _AGCconnected = true;
    }
    LEP_SetAgcEnableState(&_AGCport,LEP_AGC_DISABLE);

    LEP_GetAgcEnableState(&_AGCport,&_AGCState);

    while(true) {

        //read data packets from lepton over SPI
        int resets = 0;
        for(int j=0;j<PACKETS_PER_FRAME;j++) {
            //if it's a drop packet, reset j to 0, set to -1 so he'll be at 0 again loop
            read(spi_cs0_fd, result+sizeof(uint8_t)*PACKET_SIZE*j, sizeof(uint8_t)*PACKET_SIZE);
            int packetNumber = result[j*PACKET_SIZE+1];
            //std::cout<<"packetNumber: "<<packetNumber<<std::endl;
            if(packetNumber != j) {
                j = -1;
                resets += 1;
                usleep(1000);
                //Note: we've selected 750 resets as an arbitrary limit, since there should never be 750 "null" packets between two valid transmissions at the current poll rate
                //By polling faster, developers may easily exceed this count, and the down period between frames may then be flagged as a loss of sync
                if(resets == 750) {
                    SpiClosePort(0);
                    usleep(750000);
                    SpiOpenPort(0);
                }
            }
        }
        if(resets >= 30) {
            qDebug() << "done reading, resets: " << resets;
        }

        frameBuffer = (uint16_t *)result;
        int row, column;
        uint16_t value;
        uint16_t minValue = 65535;
        uint16_t maxValue = 0;


        for(int i=0;i<FRAME_SIZE_UINT16;i++) {
            //skip the first 2 uint16_t's of every packet, they're 4 header bytes
            if(i % PACKET_SIZE_UINT16 < 2) {
                continue;
            }

            //flip the MSB and LSB at the last second
            int temp = result[i*2];
            result[i*2] = result[i*2+1];
            result[i*2+1] = temp;

            value = frameBuffer[i];
            if(value > maxValue) {
                maxValue = value;
            }
            if(value < minValue) {
                minValue = value;
            }
            column = i % PACKET_SIZE_UINT16 - 2;
            row = i / PACKET_SIZE_UINT16 ;
        }

        //std::cout<<maxValue<<std::endl;
        //std::cout<<minValue<<std::endl;
        //std::cout<<_AGCState<<std::endl;
        //maxValue = 8300;
        //minValue = 8000;
        float diff = maxValue - minValue;
        float scale = 255/diff;
        QRgb color;

        Mat cvImage(60, 80, CV_8UC3);

        for(int i=0;i<FRAME_SIZE_UINT16;i++)
        {
            if(i % PACKET_SIZE_UINT16 < 2)
            {
                continue;
            }
            value = (frameBuffer[i] - minValue) * scale;
            if(value > 255) value = 0;
            //if(value < 0) value = 0;
            const int *colormap = colormap_grayscale;
            color = qRgb(colormap[3*value], colormap[3*value+1], colormap[3*value+2]);
            column = (i % PACKET_SIZE_UINT16 ) - 2;
            row = i / PACKET_SIZE_UINT16;
            myImage.setPixel(column, row, color);
            cvImage.at<Vec3b>(row, column)[0] = colormap[3*value];
            cvImage.at<Vec3b>(row, column)[1] = colormap[3*value+1];
            cvImage.at<Vec3b>(row, column)[2] = colormap[3*value+2];
        }

        cvImage = QImage2cvMat(myImage);
        Identify(cvImage);
        myImage = cvMat2QImage(cvImage);

        //lets emit the signal for update
        emit updateImage(myImage);

    }

    //finally, close SPI port just bcuz
    SpiClosePort(0);
}

void LeptonThread::performFFC() {
    //perform FFC
    lepton_perform_ffc();
}

Mat LeptonThread::QImage2cvMat(QImage image)
{
    cv::Mat mat;
    //qDebug() << image.format();
    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    default:
        break;
    }
    return mat;
}


QImage LeptonThread::cvMat2QImage(const Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}

void LeptonThread::Identify(Mat& frame){

    Mat gray_image;
    Mat binary_image;
    Mat dilate_img;


    cvtColor(frame, gray_image, CV_BGR2GRAY);       //灰度处理
    threshold(gray_image, binary_image, 100, 255, CV_THRESH_BINARY);//二值化
    Mat de_noise = binary_image.clone();
    medianBlur(binary_image, de_noise, 5);
    //imshow("de_noise", de_noise);
    //imshow("binaryimage", binary_image);

    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));//膨胀
    dilate(de_noise, dilate_img,element);
    //imshow("dilate_img", dilate_img);

    //外部加框
    //检测连通域，每一个连通域以一系列的点表示，FindContours方法只能得到第一个域
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    //findContours(dilate_img, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);//CV_RETR_EXTERNAL只检测外部轮廓，可根据自身需求进行调整
    findContours(dilate_img, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    //qDebug() << "num: " << contours.size();
    //serialPutchar(serialPortfd, 0xFF);  //StartBit
    //serialPutchar(serialPortfd, contours.size());
    QString sendStr = "#";
    sendStr.append(QString::number(contours.size(), 10));
    QString space = " ";
    for (int index = 0; index < contours.size(); index = hierarchy[index][0])
    {
        cv::drawContours(frame, contours, index, Scalar(0, 255, 255), 1, 8, hierarchy);//描绘外轮廓
        Rect rect = boundingRect(contours[index]);//检测外轮廓
        rectangle(frame, rect, Scalar(0, 0, 255), 1);//对外轮廓加矩形框
        //qDebug() << "lefttop: " << rect.x << "," << rect.y;
        //qDebug() << "rightbottom: " << rect.x + rect.width << "," << rect.y + rect.height;
        //serialPutchar(serialPortfd, rect.x);
        //serialPutchar(serialPortfd, rect.y);
        //serialPutchar(serialPortfd, rect.x + rect.width);
        //serialPutchar(serialPortfd, rect.y + rect.height);

        sendStr.append(space);
        sendStr.append(QString::number(rect.x, 10));
        sendStr.append(space);
        sendStr.append(QString::number(rect.y, 10));
        sendStr.append(space);
        sendStr.append(QString::number(rect.x + rect.width, 10));
        sendStr.append(space);
        sendStr.append(QString::number(rect.y + rect.height, 10));
    }
    sendStr.append("*");
    sendStr.append("\r");
    serialPuts(serialPortfd, sendStr.toLatin1().data());

}
