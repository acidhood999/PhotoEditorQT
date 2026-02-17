#pragma once

#include <QSlider>
#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QTimer>
#include <QPushButton>

class PhotoEditorQT;

class Functional : public QWidget
{
	Q_OBJECT
public:
	Functional(PhotoEditorQT* mainWin);

	void resetSlideWH();

	void getUpdate() { updateAll(); }

	QWidget* getToolsContainer() { return toolsContainer; }
	~Functional();

private slots:

	void updateAll();
	void updateResult();
	void resetBtn();
	void saveBtn();
	void onSliderValueChanged();

private:

	PhotoEditorQT* m_mainWindow = nullptr;

	QWidget* toolsContainer = nullptr;
	QGridLayout* toolsLayout = nullptr;

	QSlider* sliderW = nullptr;
	QSlider* sliderH = nullptr;

	QSlider* sliderСontrast = nullptr;
	QSlider* sliderBrightness = nullptr;

	QSlider* sliderSharpness = nullptr;
	QSlider* sliderBlur = nullptr;
	
	QPushButton* btnSave = nullptr;
	QPushButton* btnReset = nullptr;
	QPushButton* btnExit = nullptr;

	QColor color;

	QTimer* m_debounceTimer = nullptr;

	int resW{};
	int resH{};
	QSize baseSize;

	int lut[256] = { 0 };

	float factor{0.0f};
	float amount{ 0.0f };

	void InitializationOfVar(PhotoEditorQT* mainWin);
	void applyGroupStyle(QGroupBox* group);

	void lutToImage(QImage& img, const int lut[256]);
	void contrastAndBrightness(int lut[256], int cV, int bV);

	void sharpness(QImage& img, int value);
	
};
