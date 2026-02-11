#pragma once

#include "PhotoEditorQT.h"

class ImageItem : public QWidget
{
	Q_OBJECT

public:

	ImageItem(QWidget* parent = nullptr);
	void setData(const QPixmap& pixmap);
	~ImageItem();

private slots:



private:
	QLabel* img;
	QLabel* title;
	QGridLayout* layout;

};

