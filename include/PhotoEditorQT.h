#pragma once

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
#include <QScrollArea>
#include <QImage>
#include <QColor>
#include <QPointer> 
#include <memory>
#include "Functional.h"

class Functional;
class ImageItem;
class Bar;

class PhotoEditorQT : public QMainWindow
{
    Q_OBJECT

public:
	explicit PhotoEditorQT(QWidget *parent = nullptr);
	~PhotoEditorQT() override;

	QLabel* getImageLabel() const { return imageLabel; }
	Functional* getFunctional() const { return functional; }
	void setImage(QString& filename);

	QImage getQImageO() const { return imgO; }
	void setQImageO(const QImage& img) { imgO = img; }
	void setQImageO(const QString& path) { QImage file(path); imgO = file; }

	QImage getQImageR() const { return imgR; }
	void setQImageR(const QImage& img) { imgR = img; }
	void setQImageR(const QString& path) { QImage file(path); imgR = file; }

	QImage getQImageD() const { return imgD; }
	void setQImageD(const QImage& img) { imgD = img; }
	void setQImageD(const QString& path) { QImage file(path); imgD = file; }



    

private slots:

	void on_listWidget_itemDoubleClicked(QListWidgetItem* item);

private:

	QPointer<QListWidget> listImg;

	QPointer<QLabel> imageLabel;
	QPointer<QWidget> leftContent;
	
	QPointer<QListWidgetItem> item;

	QPointer<QWidget> topWidget;
	QPointer<QHBoxLayout> topLayout;

	QPointer<QVBoxLayout> mainLayout;
	QPointer<QWidget> container;

	QImage imgO;
	QImage imgR;
	QImage imgD;

	QFileInfo infoFile;
	QDir dir;
	QStringList filter;
	QFileInfoList list;

	QPointer<ImageItem> imgItem;
	
	QPointer<Functional> functional;
	QPointer<Bar> bar;

	void WindowSet();
};

