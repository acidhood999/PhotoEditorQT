#pragma once

#include "PhotoEditorQT.h"

class ImageItem : public QWidget
{
	Q_OBJECT

public:

	ImageItem(QWidget* parent = nullptr);

	~ImageItem();

private slots:



private:
	QLabel* img;
	QLabel* title;
	QLabel* info;
	QGridLayout* layout;

};

