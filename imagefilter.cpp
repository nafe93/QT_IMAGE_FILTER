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
QImage convertToInverse(QImage &img)
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
        result = ((255 - s2)/(256 - r2)) * (x - r2) + s2;
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

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief localSharpenFilter
 * @param img
 * @return
 */
 vector<int> equalizationImage(QImage &img)
{
    QSize sizeImage = img.size();

    int width  = sizeImage.width();
    int height = sizeImage.height();

    int maxPixel = width * height;

    uchar *bits = img.bits();

    vector<int> colorCounter;

    for (int i = 0; i < 256; i++)
    {
        int index = 0;

        for(int j = 0; j < maxPixel; j++)
        {
            if (i == (int)bits[j])
            {
                index++;
            }
        }

        float buffer = (index * 255) /  float(width * height);
        buffer = round(buffer);

         colorCounter.push_back(buffer);
     }

     return  colorCounter;
}

 /**
  * @brief equalizationImageFilter
  * @param img
  * @return
  */
 QImage equalizationImageFilter(QImage &img)
 {
    QSize sizeImage = img.size();
    int width  = sizeImage.width();
    int height = sizeImage.height();
    int size   = width * height;
    // constants
    float constant = 255 / (float)size;
    //
    QRgb pixel;
    float ipixel = 0;

    vector<float> colorCounter;

    for(int i =0; i < 256; i++)
    {
        int index = 0;

        for (int f1 = 0; f1<width; f1++)
        {
            for (int f2 = 0; f2<height; f2++)
            {
                pixel = img.pixel(f1, f2);

                if (i == qRed(pixel))
                {
                    index++; //count of color pixel from 0 - 255
                }
            }
        }

        colorCounter.push_back(index);
    }

    for (int f1 = 0; f1<width; f1++)
    {
        for (int f2 = 0; f2<height; f2++)
        {

            pixel = img.pixel(f1, f2);

            ipixel = 0;

            for (int k = 0; k <= qRed(pixel); k++)
            {
               ipixel += colorCounter[k];
            }

            ipixel = round(ipixel * constant);

            img.setPixel( f1, f2, qRgb(ipixel ,ipixel ,ipixel) );
        }
    }

     return img;
 }

///////////////////////////////////////////////////////////////////////////////

 /**
 * @brief localEqualizationImageFilter
 * @param img
 * @return
 */
QImage localEqualizationImageFilter(QImage &img)
{
   QSize sizeImage = img.size();
   int width  = sizeImage.width();
   int height = sizeImage.height();
   // constants
   float constant = 255 / 9;
   // pixel
   QRgb pixel;
   float ipixel = 0;

   vector<float> colorCounter;

   for (int f1 = 0; f1 < width; f1++)
   {
       for (int f2 = 0; f2 < height; f2++)
       {

           colorCounter.clear();

           for(int i =0; i < 256; i++)
           {
               int index = 0;

               for (int rows = -1; rows < 2; rows++)
               {
                   for (int cows = -1; cows < 2; cows++)
                   {
                       pixel = img.pixel(f1 + rows,f2 + cows);

                       if (i == qRed(pixel))
                       {
                           index++;
                       }
                   }
                }

                colorCounter.push_back(index);
           }

           pixel = img.pixel(f1, f2);

           ipixel = 0;

           for (int k = 0; k <= qRed(pixel); k++)
           {
              ipixel += colorCounter[k];
           }

           ipixel = round(ipixel * constant);


           img.setPixel( f1, f2, qRgb(ipixel ,ipixel ,ipixel) );
       }
   }

   return img;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief equalizationImageFilter
 * @param img
 * @return
 */
//QImage localStaticEqualizationImageFilter(QImage &img,float E= 4.0, float k0 = 0.4, float k1 = 0.02, float k2 = 0.4)
//{
//    QSize sizeImage = img.size();
//    int width  = sizeImage.width();
//    int height = sizeImage.height();
//    int size   = width * height;
//    // constants
//    float constant = 255 / 9;
//    // pixel
//    QRgb pixel;
//    float ipixel = 0;
//    // avarages
//    float lightAvarage = 0;
//    //delta
//    float globalDelta = 0;

//    vector<float> colorCounter;
//    vector<float> colorCounterAvarage;

//    for(int i =0; i < 256; i++)
//    {
//        int index = 0;

//        for (int f1 = 0; f1<width; f1++)
//        {
//            for (int f2 = 0; f2<height; f2++)
//            {
//                pixel = img.pixel(f1, f2);

//                if (i == qRed(pixel))
//                {
//                    index++; //count of color pixel from 0 - 255
//                }
//            }
//        }


//        colorCounterAvarage.push_back(index/size);
//    }

//    for (int i = 0; i < colorCounterAvarage.size(); i++)
//    {
//        lightAvarage += (i * colorCounterAvarage[i]);
//    }



//    for (int i = 0; i < colorCounterAvarage.size(); i++)
//    {
//        globalDelta += pow((i - lightAvarage),2) * colorCounterAvarage[i] ;
//    }



//    for (int f1 = 0; f1 < width; f1++)
//    {
//        for (int f2 = 0; f2 < height; f2++)
//        {

//            colorCounter.clear();

//            for(int i =0; i < 256; i++)
//            {
//                int index = 0;

//                for (int rows = -1; rows < 2; rows++)
//                {
//                    for (int cows = -1; cows < 2; cows++)
//                    {
//                        pixel = img.pixel(f1 + rows,f2 + cows);

//                        if (i == qRed(pixel))
//                        {
//                            index++;
//                        }
//                    }
//                 }

//                 colorCounter.push_back(index/9);
//            }

//            pixel = img.pixel(f1, f2);

//            ipixel = 0;

//            for (int k = 0; k < colorCounter.size(); k++)
//            {
//               ipixel += k * colorCounter[k];
//            }


//            if (ipixel <= k0 * lightAvarage)
//            {

//                float localDelta  = 0;

//                for (int i = 0; i < colorCounter.size(); i++)
//                {
//                   localDelta += pow((i - ipixel),2) * colorCounter[i];
//                }


//                if (k1 * sqrt(globalDelta) <= sqrt(localDelta) && k2 * sqrt(globalDelta) >= sqrt(localDelta) )
//                {

//                    if (qRed(pixel)* E < 256)
//                    {
//                         img.setPixel( f1, f2, qRgb(qRed(pixel)*E, qRed(pixel)*E, qRed(pixel)*E) );
//                    }


//                }

//            }
//        }
//    }

//    return img;

//}
QImage localStaticEqualizationImageFilter(QImage &img, float E = 3.0, float k0 = 0.5, float k1 = 0.04, float k2 = 0.4)
{

    QImage original = img;

    QSize sizeImage = img.size();

    int width  = sizeImage.width();
    int height = sizeImage.height();
    int sq     = width * height;

    // global
    float expectedGlobal = 0;
    float varianceGlobal = 0;

    //local
    float expectedlocal;
    float variancelocal;


    for (int f1 = 0; f1 < width; f1++)
    {
        for (int f2 = 0; f2 < height; f2++)
        {
            QRgb pixel =  img.pixel(f1, f2);

            int red = qRed(pixel);

            expectedGlobal += red;
        }
    }

    expectedGlobal = expectedGlobal / (float)sq;


    for (int f1 = 0; f1 < width; f1++)
    {
        for (int f2 = 0; f2 < height; f2++)
        {
            QRgb pixel =  img.pixel(f1, f2);

            int red = qRed(pixel);

            varianceGlobal += pow(float(red) - expectedGlobal, 2);
        }
    }

    varianceGlobal = sqrt(varianceGlobal / (float)sq);

    for (int f1 = 0; f1 < width; f1++)
    {
        for (int f2 = 0; f2 < height; f2++)
        {

            expectedlocal = 0;
            variancelocal = 0;

            for (int rows = -1; rows < 2; rows++)
            {
                for (int cows = -1; cows < 2; cows++)
                {
                    QRgb pixel =  img.pixel(f1 + rows, f2 + cows);

                    int red = qRed(pixel);

                    expectedlocal += (float)red;

                }
            }

            expectedlocal = expectedlocal / 9;

            for (int rows = -1; rows < 2; rows++)
            {
                for (int cows = -1; cows < 2; cows++)
                {
                    QRgb pixel =  img.pixel(f1 + rows, f2 + cows);

                    int red = qRed(pixel);

                    variancelocal += pow(float(red) - expectedlocal, 2);
                }
            }

            variancelocal = sqrt(variancelocal / 9);

            qDebug() << "local" << expectedlocal << "====" << variancelocal << "global" << expectedGlobal << "======" << varianceGlobal;


            if (expectedlocal <= (k0 * expectedGlobal) && variancelocal >= (k1 * varianceGlobal) && variancelocal <= (k2 * varianceGlobal))
            {
                QRgb pixel = img.pixel(f1, f2);
                int  ipixel= qRed(pixel) * E;

                if (ipixel < 256)
                {
                    original.setPixel( f1, f2, qRgb(ipixel ,ipixel , ipixel) );
                }


            }

        }
    }

    return original;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief localSharpenFilter
 * @param img
 * @return
 */
QImage localSharpenFilter(QImage &img)
{
    QSize sizeImage = img.size();
    int width  = sizeImage.width();
    int height = sizeImage.height();
    int size   = width * height;

    QRgb pixel;
    int ipixel;
    //sum of all pixel
    float index = 0;

    uchar *bits = img.bits();

    for(int j = 0; j < size ; j++)
    {
        index++;
    }

    index = index / size;

    for (int f1 = 0; f1<width; f1++)
    {
        for (int f2 = 0; f2<height; f2++)
        {

            ipixel   = 0.0;

            img.setPixel( f1, f2, qRgb(ipixel ,ipixel , ipixel) );
        }
    }

    return img;
}

/**
 * @brief localPassFilter
 * @param img
 * @return
 */
QImage localPassFilter(QImage &img)
{
    QSize sizeImage = img.size();
    int width  = sizeImage.width();
    int height = sizeImage.height();

    QRgb pixel;
    int ipixel;

    int kernel[3][3];

    for (int f1 = 0; f1<width; f1+=3)
    {
        for (int f2 = 0; f2<height; f2+=3)
        {

            ipixel   = 0.0;

            int localRows = f1 + 3;
            int localCows = f2 + 3;

            for (int rows = f1; rows < localRows; rows++)
            {
                for (int cows = f2; cows < localCows; cows++)
                {
                    pixel = img.pixel(rows, cows);

                    kernel[localRows - rows - 1][localCows - cows - 1] = qRed(pixel);

                }
            }

            for (int k = -1; k <= 1; k++)
            {
                for (int j = -1; j <= 1; j++)
                {

                    pixel = img.pixel(f1 + k, f2 +j);

                    ipixel = kernel[1][1];

                }
            }

            img.setPixel( f1, f2, qRgb(ipixel ,ipixel , ipixel) );
        }
    }

    return img;
}

/**
 * @brief sharpenFilter
 * @param img
 * @return
 */
QImage sharpenFilter(QImage &img, int z= 1)
{
    QSize sizeImage = img.size();
    int width  = sizeImage.width();
    int height = sizeImage.height();

    QRgb pixel;

    int sharpen[]= {
        0,   -z  ,   0,
        -z,  1+4*z,  -z,
        0,   -z  ,   0
    }; // The sharpen filter

    for (int f1 = 0; f1<width; f1++)
    {
        for (int f2 = 0; f2<height; f2++)
        {
            double linc_r=0, linc_g=0,linc_b=0;

            for(int k=0; k<=2; k++)
            {

                for(int l=0; l<=2; l++)
                {

                    pixel = img.pixel(f2 + l -1 , f1 + k -1);

                    linc_r +=( qRed(pixel)   * sharpen[ k*3 + l] );

                }
            }

            img.setPixel( f1, f2, qRgb(linc_r ,linc_g , linc_b) );
        }
    }

    return img;
}



/**
 * @brief bluerFilter
 * @param img
 * @return
 */
QImage bluerFilter(QImage &img)
{
    QSize sizeImage = img.size();
    int width  = sizeImage.width();
    int height = sizeImage.height();

    QRgb pixel;
    int ipixel;


    double kernel[3][3] = {
            {1/9.0, 1/9.0, 1/9.0},
            {1/9.0, 1/9.0, 1/9.0},
            {1/9.0, 1/9.0, 1/9.0}
    };

    for (int f1 = 0; f1<width; f1++)
    {
        for (int f2 = 0; f2<height; f2++)
        {

            ipixel   = 0.0;


            for (int k = -1; k <= 1; k++)
            {
                for (int j = -1; j <= 1; j++)
                {

                    pixel = img.pixel(f1 - k, f2 - j);

                    ipixel   += kernel[j+1][k+1]*qRed(pixel);

                }
            }


            img.setPixel( f1, f2, qRgb(ipixel ,ipixel , ipixel) );

        }
    }

    return img;
}
