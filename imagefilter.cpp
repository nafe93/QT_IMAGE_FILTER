#include <QGraphicsScene>
#include <QFileDialog>
#include <QWidget>
#include <QDebug>
#include <iostream>
#include <cmath>
#include <string>


#include "mathematic.cpp"
#include "bits.h"

using namespace std;

/**
 * @brief imageLoad
 * @param path
 * @return
 */
QImage imageLoad(QString path)
{
    QImage image;

    image.load(path);

    return image;
}


/**
 * @brief imageToPix
 * @param img
 * @return
 */
QPixmap imageToPix(QImage img)
{
    QPixmap pix;

    pix = QPixmap::fromImage(img);

    return pix;
}


int chooseTypeOFGrayScale(int key, int red, int green, int blue)
{
   int gray = 0;

   if (key == 1)
   {
        gray = (red + green + blue) / 3;
        return gray;
   }
   if (key == 2)
   {
       gray = max({red, green, blue});
       return gray;
   }
   if (key == 3)
   {
       gray = ( max({red, green, blue}) + min({red, green, blue}) ) / 2;
       return gray;
   }
   if (key == 4)
   {
       gray = (red * (-1)) + (0.715 * green) - (0.72 * blue);
       return gray;
   }
   if (key == 5)
   {
       gray = sqrt((red * red) + (green * green) + (blue * blue));
       return gray;
   }

    return gray;
}

/**
 * @brief convertToGrayScale
 * @param img
 * @return
 */
QImage convertToGrayScale(QImage &img, int key = 5)
{
    QSize sizeImage = img.size();
    int width  = sizeImage.width();
    int height = sizeImage.height();

    QRgb color;
    int gray;

    for (int f1 = 0; f1<width; f1++)
    {
        for (int f2 = 0; f2<height; f2++)
        {
            color = img.pixel(f1, f2);

            gray = chooseTypeOFGrayScale(key, qRed(color), qGreen(color), qBlue(color));

            img.setPixel(f1, f2, qRgb(gray ,gray, gray) );
        }
    }
    return img;
}


/**
 * @brief convertToInverse
 * @param img
 * @return
 */
QImage convertToInverse(QImage &img, int key = 1)
{
    QSize sizeImage = img.size();
    int width  = sizeImage.width();
    int height = sizeImage.height();

    QRgb color;
    int iRed, iGreen, iBlue;
    int L = 255;

    for (int f1 = 0; f1<width; f1++)
    {
        for (int f2 = 0; f2<height; f2++)
        {
            color = img.pixel(f1, f2);

            iRed   = L - qRed(color);
            iGreen = L - qGreen(color);
            iBlue  = L - qBlue(color);

            img.setPixel(f1, f2, qRgb(iRed ,iGreen, iBlue) );
        }
    }
    return img;
}


/**
 * @brief logn
 * @param a
 * @param b
 * @return
 */
double logn(double a, double b)
{
    //logaB = logcB / logcA
    return log10(b) / log10(a);
}


/**
 * @brief chooseTypeOfLg
 * @param key
 * @param r
 * @return
 */
int chooseTypeOfLg(int key, int r, int value)
{

   if (key == 1)
   {
        int c = 255 / (log2(1 + 255));
        int log =  c * log2(r + 1);
        return log;
   }
   if (key == 2)
   {
       int c = 255 / (log10(1 + 255));
       int ln = c * log10(r + 1);
       return ln;
   }
   if (key == 3)
   {
       int c = 255 / (logn(value, (1 + 255)));
       int ln = c * logn(value, (r + 1));
       return ln;
   }

    return 0;
}


/**
 * @brief convertToLg
 * @param img
 * @param key
 * @return
 */
QImage convertToLg(QImage &img, int key = 3, int value = 5)
{
    QSize sizeImage = img.size();
    int width  = sizeImage.width();
    int height = sizeImage.height();

    QRgb color;
    int iRed, iGreen, iBlue;

    for (int f1 = 0; f1 < width; f1++)
    {
        for (int f2 = 0; f2 < height; f2++)
        {
            color = img.pixel(f1, f2);

            iRed   = chooseTypeOfLg(key ,qRed(color), value);
            iGreen = chooseTypeOfLg(key ,qGreen(color), value);
            iBlue  = chooseTypeOfLg(key ,qBlue(color), value);

            img.setPixel(f1, f2, qRgb(iRed ,iGreen, iBlue) );
        }
    }
    return img;
}


/**
 * @brief convertToStep
 * @param img
 * @param key
 * @return
 */
QImage convertToStep(QImage &img, int key = 10)
{
    QSize sizeImage = img.size();
    int width  = sizeImage.width();
    int height = sizeImage.height();

    QRgb color;
    int iRed, iGreen, iBlue;
    double c = 255 / pow(255, key);

    for (int f1 = 0; f1<width; f1++)
    {
        for (int f2 = 0; f2<height; f2++)
        {
            color = img.pixel(f1, f2);

            iRed   = c * pow(qRed(color), key);
            iGreen = c * pow(qGreen(color), key);
            iBlue  = c * pow(qBlue(color), key);

            img.setPixel(f1, f2, qRgb(iRed ,iGreen, iBlue) );
        }
    }
    return img;
}


/**
 * @brief computeOutput
 * @param x
 * @param r1
 * @param s1
 * @param r2
 * @param s2
 * @return
 */
int computeOutput(int x, int r1, int s1, int r2, int s2)
{
    float result;

    if(0 <= x && x <= r1)
    {
        result = s1/r1 * x;
    }
    else if (r1 < x && x <= r2)
    {
        result = ((s2 - s1)/(r2 - r1)) * (x - r1) + s1;
    }
    else if(r2 < x && x <= 255)
    {
        result = ((255 - s2)/(255 - r2)) * (x - r2) + s2;
    }

    return (int)result;
}


/**
 * @brief convertToConstarctStretching
 * @param img
 * @param key
 * @return
 */
QImage convertToConstarctStretching(QImage &img, int r1 = 255, int s1 = 150, int r2 = 132, int s2 = 175)
{
    QSize sizeImage = img.size();
    int width  = sizeImage.width();
    int height = sizeImage.height();

    QRgb color;
    int iRed, iGreen, iBlue;

    for (int f1 = 0; f1<width; f1++)
    {
        for (int f2 = 0; f2<height; f2++)
        {
            color = img.pixel(f1, f2);

            iRed   = computeOutput(qRed(color), s1, r1, s2, r2);
            iGreen = computeOutput(qGreen(color), s1 , r1, s2, r2);
            iBlue  = computeOutput(qBlue(color), s1, r1, s2, r2);

            img.setPixel( f1, f2, qRgb(iRed ,iGreen, iBlue) );
        }
    }
    return img;
}


/**
 * @brief convertToBinary
 * @param img
 * @return
 */
QImage convertToThresholdBinarization(QImage &img, int red = 200, int green = 130, int blue = 155)
{
    QSize sizeImage = img.size();
    int width  = sizeImage.width();
    int height = sizeImage.height();

    QRgb color;
    int iRed, iGreen, iBlue;


    for (int f1 = 0; f1<width; f1++)
    {
        for (int f2 = 0; f2<height; f2++)
        {
            color = img.pixel(f1, f2);

            iRed   = qRed(color);
            iGreen = qGreen(color);
            iBlue  = qBlue(color);
            if (iRed > red && iGreen > green && iBlue > blue)
            {
                img.setPixel( f1, f2, qRgb(iRed ,iGreen, iBlue) );
            }
            else
            {
                img.setPixel( f1, f2, qRgb(0, 0, 0) );
            }
        }
    }
    return img;
}


/**
 * @brief convertToThresholdConversion
 * @param img
 * @param red
 * @param green
 * @param blue
 * @param redTo
 * @param greenTo
 * @param blueTo
 * @return
 */
QImage convertToThresholdConversion(QImage &img, int red = 100, int green = 130, int blue = 55,
                                    int redTo = 210, int greenTo = 175, int blueTo = 233)
{
    QSize sizeImage = img.size();
    int width  = sizeImage.width();
    int height = sizeImage.height();

    QRgb color;
    int iRed, iGreen, iBlue;


    for (int f1 = 0; f1<width; f1++)
    {
        for (int f2 = 0; f2<height; f2++)
        {
            color = img.pixel(f1, f2);

            iRed   = qRed(color);
            iGreen = qGreen(color);
            iBlue  = qBlue(color);
            if ( (iRed > red && iRed < redTo) && (iGreen > green && iGreen < greenTo ) && (iBlue > blue && iBlue < blueTo) )
            {
                img.setPixel( f1, f2, qRgb(iRed ,iGreen, iBlue) );
            }
            else
            {
                img.setPixel( f1, f2, qRgb(0, 0, 0) );
            }
        }
    }
    return img;
}


/**
 * @brief convertToBits
 * @param img
 * @param step
 * @return
 */
QImage convertToBits(QImage &img, int step = 2)
{
    QSize sizeImage = img.size();
    int width  = sizeImage.width();
    int height = sizeImage.height();

    QRgb color;
    int iRed, iGreen, iBlue;
    int iiRed, iiGreen, iiBlue;


    for (int f1 = 0; f1<width; f1++)
    {
        for (int f2 = 0; f2<height; f2++)
        {
            color = img.pixel(f1, f2);

            iRed   = qRed(color);
            iGreen = qGreen(color);
            iBlue  = qBlue(color);

            string bRed   =  DecToBin2(iRed, step);
            string bGreen =  DecToBin2(iGreen, step);
            string bBlue  =  DecToBin2(iBlue, step);

            iiRed   = Bin2ToDec(bRed);
            iiGreen = Bin2ToDec(bGreen);
            iiBlue  = Bin2ToDec(bBlue);

            img.setPixel( f1, f2, qRgb(iiRed ,iiGreen, iiBlue) );
        }
    }
    return img;
}


