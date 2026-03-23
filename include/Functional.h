#pragma once

#include <QSlider>
#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QTimer>
#include <QPushButton>
#include <QPointer>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>

class PhotoEditorQT;

class Functional : public QWidget
{
	Q_OBJECT
public:
	Functional(PhotoEditorQT* mainWin);

	void resetSlideWH();
	QWidget* getToolsContainer() { return toolsContainer; }
	~Functional();

public slots:
	void updateResult();

private slots:

	void updateAll();
	void resetBtn();
	void saveBtn();
	void onSliderValueChanged();

private:

	QPointer<PhotoEditorQT> m_mainWindow;

	QPointer<QWidget> toolsContainer;
	QPointer<QSlider> sliderW, sliderH;
	QPointer<QSlider> sliderСontrast, sliderBrightness;
	QPointer<QSlider> sliderSharpness, sliderBlur;
	QPointer<QPushButton> btnSave, btnReset, btnExit;

	QTimer* m_debounceTimer = nullptr;

	void InitializationOfVar();
	void applyGroupStyle(QGroupBox* group);


	static QImage processImageStatic(QImage img, int sharp, int blur, int cV, int bV);
	static void applySharpness(QImage& img, int value);
};
