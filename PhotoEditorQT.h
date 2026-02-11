#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QString>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QListWidget>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include "ImageItem.h"
#include "Bar.h"
#include <QScrollArea>


class PhotoEditorQT : public QMainWindow
{
    Q_OBJECT

public:
    PhotoEditorQT(QWidget *parent = nullptr);
	void setImage(QString& filename);
    ~PhotoEditorQT();

private:

	QListWidget* listImg;
	QGridLayout* layout;
	QFileInfo* infoFile;
	QScrollArea* scrollArea;
	QLabel* imageLabel;
	QWidget* container;
	QGridLayout* mainLayout;
	QDir* dir;
	QFileInfoList* list;
	QListWidgetItem* item;
	

	void WindowSet();
};

