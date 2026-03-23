#include "ImageItem.h"
#include <QLabel>
#include <QGridLayout>

ImageItem::ImageItem(QWidget* parent) : QWidget(parent)
{
    img = new QLabel(this);
    layout = new QGridLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(img, 0, 0);
    setLayout(layout);
}
void ImageItem::setData(const QPixmap& pixmap, const QString& name, const QString& resolution, const QString& size_img, const QString& path_img)
{
    this->path = path_img;
    if (img) img->setPixmap(pixmap);
    this->setToolTip(QString("Name: %1\nRes: %2\nSize: %3").arg(name).arg(resolution).arg(size_img));
}

ImageItem::~ImageItem() {}

