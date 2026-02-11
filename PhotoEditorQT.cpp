#include "PhotoEditorQT.h"

PhotoEditorQT::PhotoEditorQT(QWidget *parent) : QMainWindow(parent)
{
	imageLabel = new QLabel();
	scrollArea = new QScrollArea(this);
	scrollArea->setWidget(imageLabel);
	scrollArea->setWidgetResizable(true);

	listImg = new QListWidget(this);
	listImg->setMaximumWidth(150);


	container = new QWidget(this);
	mainLayout = new QGridLayout(container);


	mainLayout->addWidget(scrollArea, 0, 0);
	mainLayout->addWidget(listImg, 0, 1);


	setCentralWidget(container);
	WindowSet();
	Bar* bar = new Bar(this);
}

void PhotoEditorQT::setImage(QString& filename)
{
	QPixmap pix(filename);
	imageLabel->setPixmap(pix);
	imageLabel->setFixedSize(pix.width(), pix.height());

	listImg->clear();
	infoFile = new QFileInfo(filename);
	dir = new QDir(infoFile->absolutePath());
	QStringList filter;
	filter << "*.jpg" << "*.png";
	list = new QFileInfoList(dir->entryInfoList(filter));
	for (int i = 0; i < list->count(); i++)
	{
		item = new QListWidgetItem(listImg);
		ImageItem* imgItem = new ImageItem;
		item->setSizeHint(imgItem->sizeHint());
		listImg->setItemWidget(item, imgItem);

	}
}

void PhotoEditorQT::WindowSet()
{
	this->setWindowTitle("Photo editor");
	this->setMinimumHeight(500);
	this->setMinimumWidth(500);
}
PhotoEditorQT::~PhotoEditorQT()
{

}



