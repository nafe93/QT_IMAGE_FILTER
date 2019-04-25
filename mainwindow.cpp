#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "uploadfile.cpp"
#include "imagefilter.cpp"

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

void MainWindow::on_uploadImage_clicked()
{
    QString filePath = uploadFile(this);

    QImage image = imageLoad(filePath);

    QImage original = image;

    image = convertToGrayScale(image);

    image = convertToThresholdConversion(image);

    QPixmap pix;
    QPixmap org;

    pix = imageToPix(image);

    org = imageToPix(original);

    ui->viewImage->setPixmap(pix);

    ui->viewImage_original->setPixmap(org);
}
