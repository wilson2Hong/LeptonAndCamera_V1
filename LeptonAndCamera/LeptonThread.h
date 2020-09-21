#ifndef TEXTTHREAD
#define TEXTTHREAD

#include <ctime>
#include <stdint.h>

#include <QThread>
#include <QtCore>
#include <QPixmap>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/legacy/legacy.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <vector>
#include <QDebug>


using namespace cv;
using namespace std;

#define PACKET_SIZE 164
#define PACKET_SIZE_UINT16 (PACKET_SIZE/2)
#define PACKETS_PER_FRAME 60
#define FRAME_SIZE_UINT16 (PACKET_SIZE_UINT16*PACKETS_PER_FRAME)

class LeptonThread : public QThread
{
  Q_OBJECT

public:
  LeptonThread();
  ~LeptonThread();

  void run();

public slots:
  void performFFC();

signals:
  void updateText(QString);
  void updateImage(QImage);

private:

  QImage myImage;

  uint8_t result[PACKET_SIZE*PACKETS_PER_FRAME];
  uint16_t *frameBuffer;

  int serialPortfd;

  Mat QImage2cvMat(QImage image);
  QImage cvMat2QImage(const Mat& mat);
  void Identify(Mat& cvImage);
};

#endif
