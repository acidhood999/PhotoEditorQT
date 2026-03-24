#include "ImageItem.h"
#include <QLabel>
#include <QGridLayout>

ImageItem::ImageItem(QWidget* parent) : QWidget(parent)
{
    img = new QLabel(this);
    img->setObjectName("itemPreview");
    img->setFixedSize(120, 90);       
    img->setAlignment(Qt::AlignCenter);
    img->setScaledContents(true);

    layout = new QGridLayout(this);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(img, 0, 0);

    setLayout(layout);
}

void ImageItem::setData(const QPixmap& pixmap, const QString& name, const QString& resolution, const QString& size_img, const QString& path_img)
{
    this->path = path_img;
    if (img)
    {
        img->setPixmap(pixmap);

        QString info = QString("<b>Name:</b> %1<br><b>Res:</b> %2<br><b>Size:</b> %3").arg(name).arg(resolution).arg(size_img);

       
        img->setToolTip(info);
        this->setToolTip(info);
    }
}

ImageItem::~ImageItem() {}