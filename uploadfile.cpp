#include <QGraphicsScene>
#include <QFileDialog>
#include <QWidget>
#include <QDebug>

/**
 * @brief uploadFile
 * @param  QWidget id
 * @return QString
 */
QString uploadFile(QWidget *id)
{
    QString filePath = QFileDialog::getOpenFileName(
                    id,
                    id->tr("Upload Image"),
                    "/home/developer/Pictures/",
                    "Images (*.jpg *.png)"
                );

    return filePath;
}
