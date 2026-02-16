#pragma once

#include <QSlider>
#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
class PhotoEditorQT;

class Functional : public QWidget
{
	Q_OBJECT
public:
	Functional(PhotoEditorQT* mainWin);

	void resetSlideWH();
	//void updateImage();
	QWidget* getToolsContainer() { return toolsContainer; }
	~Functional();

private slots:
	void change_W();
	void change_H(); 
	//void change_Сontrast();
private:

	PhotoEditorQT* m_mainWindow = nullptr;

	QWidget* toolsContainer = nullptr;
	QGridLayout* toolsLayout = nullptr;

	QSlider* sliderW = nullptr;
	QSlider* sliderH = nullptr;

	QSlider* sliderСontrast = nullptr;
	QSlider* slider2 = nullptr;

	QSlider* slider3 = nullptr;
	QSlider* slider4 = nullptr;

	int resW{};
	int resH{};
	QSize baseSize;

	void InitializationOfVar(PhotoEditorQT* mainWin);
	void applyGroupStyle(QGroupBox* group);
};
