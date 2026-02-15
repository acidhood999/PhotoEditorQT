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

class Functional;
class ImageItem;
class Bar;

class PhotoEditorQT : public QMainWindow
{
    Q_OBJECT

public:
    PhotoEditorQT(QWidget *parent = nullptr);
	void setImage(QString& filename);

	QPixmap getFirstImg() const { return firstImg; }
	void setFirstImg(const QPixmap& firstImg) { this->firstImg = firstImg; }
	void setFirstImg(const QString& fileName) { this->firstImg = fileName; }

	QPixmap getSecondImg() const { return secondImg; }
	void setSecondImg(const QPixmap& secondImg) { this->secondImg = secondImg; }
	void setSecondImg(const QString& fileName) { this->secondImg = fileName; }

	QLabel* getImageLabel() const { return imageLabel; }

    ~PhotoEditorQT();

private slots:

	void on_listWidget_itemDoubleClicked(QListWidgetItem* item);

private:

	QListWidget* listImg = nullptr;

	QLabel* imageLabel = nullptr;
	QWidget* leftContent = nullptr;
	
	QListWidgetItem* item = nullptr;

	QVBoxLayout* leftLayout = nullptr;
	QHBoxLayout* hLayout = nullptr;

	QWidget* container = nullptr;

	QPixmap firstImg;
	QPixmap secondImg;

	ImageItem* imgItem = nullptr;
	
	Functional* functional = nullptr;
	Bar* bar = nullptr;

	void WindowSet();
};

