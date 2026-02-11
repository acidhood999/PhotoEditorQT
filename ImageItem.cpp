#include "ImageItem.h"

ImageItem::ImageItem(QWidget* parent)
{
	img = new QLabel(this);
	title = new QLabel(this);
	info = new QLabel(this);
	layout = new QGridLayout(this);
	img->setText("pix");
	title->setText("title");
	info->setText("info");
	layout->addWidget(img, 0, 0);
	layout->addWidget(title, 0, 1);
	layout->addWidget(info, 1, 1);
}

ImageItem::~ImageItem()
{
}

