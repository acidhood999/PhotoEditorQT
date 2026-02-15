#pragma once

#include <QSlider>
#include <QWidget>
#include <QGridLayout>

class PhotoEditorQT;

class Functional : public QWidget
{
	Q_OBJECT
public:
	Functional(PhotoEditorQT* mainWin);

	void resetSlideWH();
	QWidget* getToolsContainer() { return toolsContainer; }
	~Functional();

private slots:
	void change_W();
	void change_H();
private:

	PhotoEditorQT* m_mainWindow = nullptr;

	QWidget* toolsContainer;
	QGridLayout* toolsLayout;

	QSlider* sliderW = nullptr;
	QSlider* sliderH = nullptr;

	int resSliderW{ 0 };
	int resSliderH{ 0 };

	void InitializationOfVar(PhotoEditorQT* mainWin);
};
