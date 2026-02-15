#include "Functional.h"
#include "PhotoEditorQT.h"

Functional::Functional(PhotoEditorQT* mainWin) : QWidget(mainWin), m_mainWindow(mainWin)
{
    toolsContainer = new QWidget();
    toolsLayout = new QGridLayout(toolsContainer);

  
    InitializationOfVar(mainWin);

    toolsLayout->addWidget(sliderW, 0, 0);
    toolsLayout->addWidget(sliderH, 1, 0);
   
    connect(sliderW, &QSlider::valueChanged, this, &Functional::change_W);
    connect(sliderH, &QSlider::valueChanged, this, &Functional::change_H);
}

void Functional::InitializationOfVar(PhotoEditorQT* mainWin)
{
    sliderW = new QSlider(Qt::Horizontal, this);
    sliderW->setMinimum(10);  
    sliderW->setMaximum(200); 
    sliderW->setValue(100);

    sliderH = new QSlider(Qt::Horizontal, this);
    sliderH->setMinimum(10);
    sliderH->setMaximum(200);
    sliderH->setValue(100);
}

void Functional::resetSlideWH()
{
    sliderW->setValue(100);
    sliderH->setValue(100);
}

void Functional::change_W()
{
    if (resSliderH == 0)
    {
        resSliderH = m_mainWindow->getSecondImg().height();
    }
    resSliderW = m_mainWindow->getSecondImg().width() * sliderW->value() / 100;

    m_mainWindow->getImageLabel()->setPixmap(m_mainWindow->getSecondImg().scaled(resSliderW, resSliderH, Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation));
}

void Functional::change_H()
{
    if (resSliderW == 0)
    {
        resSliderW = m_mainWindow->getSecondImg().width();
    }
    resSliderH = m_mainWindow->getSecondImg().height() * sliderH->value() / 100;

    m_mainWindow->getImageLabel()->setPixmap(m_mainWindow->getSecondImg().scaled(resSliderW, resSliderH, Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation));
}

Functional::~Functional() {}


