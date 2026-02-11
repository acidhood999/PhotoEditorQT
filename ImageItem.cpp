#include "ImageItem.h"

ImageItem::ImageItem(QWidget* parent)
{
	img = new QLabel(this);
	layout = new QGridLayout(this);
	img->setAlignment(Qt::AlignCenter);
	layout->addWidget(img, 0, 0);
}

void ImageItem::setData(const QPixmap& pixmap)
{
	img->setPixmap(pixmap);
	img->setFixedWidth(pixmap.width());

}

ImageItem::~ImageItem()
{
}

