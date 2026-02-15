#include "ImageItem.h"
#include <QLabel>
#include <QGridLayout>

ImageItem::ImageItem(QWidget* parent) : QWidget(parent)
{
    img = new QLabel(this);
    title = new QLabel(this);
    layout = new QGridLayout(this);

    layout->addWidget(img, 0, 0);
    layout->addWidget(title, 1, 0);
}

void ImageItem::setData(const QPixmap& pixmap, const QString& name, const QString& resolution, const QString& size_img, const QString& path_img)
{
    this->path = path_img;
    img->setPixmap(pixmap);
    title->setText(name);
    this->setToolTip(QString("Name: %1\nRes: %2\nSize: %3").arg(name).arg(resolution).arg(size_img));
}

ImageItem::~ImageItem() {}