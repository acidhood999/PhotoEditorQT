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
#include <QScrollArea>
#include <QImage>
#include <QColor>

class Functional;
class ImageItem;
class Bar;

class PhotoEditorQT : public QMainWindow
{
    Q_OBJECT

public:
    PhotoEditorQT(QWidget *parent = nullptr);

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

    ~PhotoEditorQT();

private slots:

	void on_listWidget_itemDoubleClicked(QListWidgetItem* item);

private:

	QListWidget* listImg = nullptr;

	QLabel* imageLabel = nullptr;
	QWidget* leftContent = nullptr;
	
	QListWidgetItem* item = nullptr;

	QWidget* topWidget = nullptr;
	QHBoxLayout* topLayout = nullptr;

	QVBoxLayout* mainLayout = nullptr;
	QWidget* container = nullptr;

	QImage imgO;
	QImage imgR;
	QImage imgD;

	qreal saturatuion{};

	ImageItem* imgItem = nullptr;
	
	Functional* functional = nullptr;
	Bar* bar = nullptr;


	void WindowSet();
	

	//void updateImg();
};

