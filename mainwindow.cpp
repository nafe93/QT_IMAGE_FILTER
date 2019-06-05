#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "uploadfile.cpp"
#include "imagefilter.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->viewImage->setStyleSheet("background-color :grey");
    ui->viewImage_original->setStyleSheet("background-color :grey");

    if (ui->checkBox_LOG->isChecked())
    {
        connect(ui->checkBox_LOG, SIGNAL(clicked(bool)), ui->radioButton_log2, SLOT(setDisabled(bool)));
        connect(ui->checkBox_LOG, SIGNAL(clicked(bool)), ui->radioButton_log10, SLOT(setDisabled(bool)));
        connect(ui->checkBox_LOG, SIGNAL(clicked(bool)), ui->radioButton_logn, SLOT(setDisabled(bool)));
        connect(ui->checkBox_LOG, SIGNAL(clicked(bool)), ui->plainTextEdit, SLOT(setDisabled(bool)));
    }
    else
    {
        connect(ui->checkBox_LOG, SIGNAL(clicked(bool)), ui->radioButton_log2, SLOT(setEnabled(bool)));
        connect(ui->checkBox_LOG, SIGNAL(clicked(bool)), ui->radioButton_log10, SLOT(setEnabled(bool)));
        connect(ui->checkBox_LOG, SIGNAL(clicked(bool)), ui->radioButton_logn, SLOT(setEnabled(bool)));
        connect(ui->checkBox_LOG, SIGNAL(clicked(bool)), ui->plainTextEdit, SLOT(setEnabled(bool)));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makePlot(int maxPixel, std::vector<int> count)
{
    // generate some data:
    QVector<double> x(255), y(maxPixel); // initialize with entries 0..100
    for (int i = 0; i < 255; i++)
    {
      x[i] = i; // x goes from 0 to 255
      y[i] = count[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->plot->addGraph();
    ui->plot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->plot->xAxis->setRange(0, 255);
    ui->plot->yAxis->setRange(0, maxPixel * 0.025);
    ui->plot->replot();
}

void MainWindow::makePlot2(int maxPixel, std::vector<int> count)
{
    // generate some data:
    QVector<double> x(255), y(maxPixel); // initialize with entries 0..100
    for (int i = 0; i < 255; i++)
    {
      x[i] = i; // x goes from 0 to 255
      y[i] = count[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->plot_2->addGraph();
    ui->plot_2->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->plot_2->xAxis->setLabel("x");
    ui->plot_2->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->plot_2->xAxis->setRange(0, 255);
    ui->plot_2->yAxis->setRange(0, maxPixel * 0.025);
    ui->plot_2->replot();
}

void MainWindow::on_uploadImage_clicked()
{
    QString filePath = uploadFile(this);

    QImage image = imageLoad(filePath);

    QImage original = image;

    if (ui->radioButton->isChecked())
    {
        image = convertToGrayScale(image, 1);
    }
    if (ui->radioButton_2->isChecked())
    {
        image = convertToGrayScale(image, 2);
    }
    if (ui->radioButton_3->isChecked())
    {
        image = convertToGrayScale(image, 3);
    }
    if (ui->radioButton_4->isChecked())
    {
        image = convertToGrayScale(image, 4);
    }
    if (ui->radioButton_5->isChecked())
    {
        image = convertToGrayScale(image, 5);
    }

    //convertToInverse
    if (ui->checkBox->isChecked())
    {
        image = convertToInverse(image);
    }

    //convertToLOG
    if(ui->checkBox_LOG->isChecked())
    {
        if (ui->radioButton_log2->isChecked())
        {
            image = convertToLg(image, 1);
        }
        if (ui->radioButton_log10->isChecked())
        {
            image = convertToLg(image, 2);
        }
        if (ui->radioButton_logn->isChecked())
        {
            QRegExp re("\\d*");

            QString text = ui->plainTextEdit->toPlainText();
            if (text.length() > 0)
            {

                if (re.exactMatch(text))
                {
                    int number = text.toInt();
                    image = convertToLg(image, 3, number);
                }
                else
                {
                    QMessageBox::warning(this, "Attention", "Your insert is not number");
                    ui->plainTextEdit->setFocus();
                }
            }
            else
            {
                QMessageBox::warning(this, "Attention", "Please Insert number");
                ui->plainTextEdit->setFocus();
            }
        }
    }

    //convert to step
    if (ui->checkBox_STEP->isChecked())
    {
        QString text = ui->textEdit->toPlainText();

        if(text.length() > 0)
        {
            int number = text.toInt();
            image = convertToStep(image, number);
        }
        else
        {
            QMessageBox::warning(this, "Attention", "Please Insert number");
            ui->textEdit->setFocus();
        }
    }
    // ConstarctStretching
    if (ui->checkBox_ConstarctStretching->isChecked())
    {
        QString tR1 = ui->textEdit_2->toPlainText();
        QString tS1 = ui->textEdit_3->toPlainText();
        QString tR2 = ui->textEdit_4->toPlainText();
        QString tS2 = ui->textEdit_5->toPlainText();

        if (tR1.length() > 0 && tS1.length() > 0 && tR2.length() > 0 && tS2.length() > 0)
        {
            int r1 = tR1.toInt();
            int s1 = tS1.toInt();
            int r2 = tR2.toInt();
            int s2 = tS2.toInt();

            image = convertToConstarctStretching(image, r1, s1, r2, s2);
        }
        else
        {
            QMessageBox::warning(this, "Attention", "Please Insert number");
            ui->textEdit_2->setFocus();
        }
    }

    // ThresholdBinarization
    if (ui->checkBox_ThresholdBinarization->isChecked())
    {
        QString tR = ui->textEdit_6->toPlainText();
        QString tG = ui->textEdit_7->toPlainText();
        QString tB = ui->textEdit_8->toPlainText();

        if (tR.length() > 0 && tG.length() > 0 && tB.length() > 0)
        {
            int R = tR.toInt();
            int G = tG.toInt();
            int B = tB.toInt();

            image = convertToThresholdBinarization(image, R, G, B);
        }
        else
        {
            QMessageBox::warning(this, "Attention", "Please Insert number");
            ui->textEdit_6->setFocus();
        }
    }

    //convertToThresholdConversion
    if (ui->checkBox_ThresholdBinarization_2->isChecked())
    {
        QString tR = ui->textEdit_9->toPlainText();
        QString tG = ui->textEdit_10->toPlainText();
        QString tB = ui->textEdit_11->toPlainText();

        QString tRT = ui->textEdit_12->toPlainText();
        QString tGT = ui->textEdit_13->toPlainText();
        QString tBT = ui->textEdit_14->toPlainText();

        if (tR.length() > 0 && tG.length() > 0 && tB.length() > 0)
        {
            int R = tR.toInt();
            int G = tG.toInt();
            int B = tB.toInt();

            int RT = tRT.toInt();
            int GT = tGT.toInt();
            int BT = tBT.toInt();

            image = convertToThresholdConversion(image, R, G, B, RT, GT, BT);
        }
        else
        {
            QMessageBox::warning(this, "Attention", "Please Insert number");
            ui->textEdit_6->setFocus();
        }
    }

    //bits
    if (ui->checkBox_Bits->isChecked())
    {
        QString bits = ui->Bits->toPlainText();


        if (bits.length() > 0  && bits.length() < 8)
        {
            int bit = bits.toInt();

            image = convertToBits(image, bit);
        }
        else
        {
            QMessageBox::warning(this, "Attention", "Please Insert number");
            ui->Bits->setFocus();
        }
    }

    image = localPassFilter(image);
//    image = sharpenFilter(image);
    image = bluerFilter(image);

    /**
     * @brief sizeImage
     */
    QSize sizeImage = image.size();

    int width  = sizeImage.width();
    int height = sizeImage.height();

    int maxPixel = width * height * 3;

    uchar *bits = image.bits();

    vector<int> colorCounter;

     for (int i = 0; i < 255; i++)
     {
         int index = 0;

         for(int j = 0; j < maxPixel; j++)
         {
             if (i == (int)bits[j])
             {
                 index++;
             }
         }
         colorCounter.push_back(index);
     }

    makePlot(maxPixel, colorCounter);


    /**
     * @brief Original
     */
    int widthOriginal  = original.width();
    int heightOriginal = original.height();

    int maxPixelOriginal = widthOriginal * heightOriginal * 3;

    uchar *bitsOriginal = original.bits();

    vector<int> colorCounterOriginal;

     for (int i = 0; i < 255; i++)
     {
         int index = 0;

         for(int j = 0; j < maxPixelOriginal; j++)
         {
             if (i == (int)bitsOriginal[j])
             {
                 index++;
             }
         }
         colorCounterOriginal.push_back(index);
     }

    makePlot2(maxPixelOriginal, colorCounterOriginal);


    // view result
    QPixmap pix;
    QPixmap org;

    int w = ui->viewImage->width();
    int h = ui->viewImage->height();

    pix = imageToPix(image);

    org = imageToPix(original);

    ui->viewImage->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    ui->viewImage_original->setPixmap(org.scaled(w, h, Qt::KeepAspectRatio));
}
