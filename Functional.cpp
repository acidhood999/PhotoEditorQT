#include "Functional.h"
#include "PhotoEditorQT.h"

Functional::Functional(PhotoEditorQT* mainWin) : QWidget(mainWin), m_mainWindow(mainWin)
{
    QGridLayout* mainToolsLayout = new QGridLayout(this);
    InitializationOfVar(mainWin);

    QGroupBox* resolutionGroup = new QGroupBox("Image resolution", this);
    QGridLayout* resolutionLayout = new QGridLayout(resolutionGroup);
    resolutionLayout->addWidget(new QLabel("Width:"), 0, 0);
    resolutionLayout->addWidget(sliderW, 0, 1);
    resolutionLayout->addWidget(new QLabel("Height:"), 1, 0);
    resolutionLayout->addWidget(sliderH, 1, 1);
    applyGroupStyle(resolutionGroup);

    QGroupBox* colorGroup = new QGroupBox("Сontrast and Brightness", this);
    QGridLayout* colorLayout = new QGridLayout(colorGroup);
    colorLayout->addWidget(new QLabel("Сontrast:"), 0, 0);
    colorLayout->addWidget(sliderСontrast, 0, 1);
    colorLayout->addWidget(new QLabel("Brightness:"), 1, 0);
    colorLayout->addWidget(slider2, 1, 1);
    applyGroupStyle(colorGroup);

    QGroupBox* Group = new QGroupBox("Image resolution", this);
    QGridLayout* GroupLayout = new QGridLayout(Group);
    GroupLayout->addWidget(new QLabel("color1:"), 0, 0);
    GroupLayout->addWidget(new QSlider(Qt::Horizontal, this), 0, 1);
    GroupLayout->addWidget(new QLabel("color2:"), 1, 0);
    GroupLayout->addWidget(new QSlider(Qt::Horizontal, this), 1, 1);
    applyGroupStyle(Group);


    mainToolsLayout->addWidget(resolutionGroup,0,0);
    mainToolsLayout->addWidget(colorGroup,0,1);
    mainToolsLayout->addWidget(Group, 0, 2);

    toolsContainer = new QWidget();
    toolsContainer->setLayout(mainToolsLayout);

    connect(sliderW, &QSlider::valueChanged, this, &Functional::change_W);
    connect(sliderH, &QSlider::valueChanged, this, &Functional::change_H);

    //connect(sliderСontrast, &QSlider::valueChanged, this, &Functional::change_Сontrast);
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

    sliderСontrast = new QSlider(Qt::Horizontal, this);
    slider2 = new QSlider(Qt::Horizontal, this);
    //slider3 = new QSlider(Qt::Horizontal, this);
    //slider4 = new QSlider(Qt::Horizontal, this);
}

void Functional::applyGroupStyle(QGroupBox* group)
{
    group->setStyleSheet(
        "QGroupBox {"
        "   border: 2px solid #C2C2C2;" 
        "   border-radius: 8px;"       
        "   margin-top: 10px;"         
        "   background-color: #F0F0F0;"
        "}"
        "QGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   subcontrol-position: top center;"          
        "   padding: 0 3px 0 3px;"
        "}"
    );
}

void Functional::resetSlideWH()
{
    sliderW->setValue(100);
    sliderH->setValue(100);
}

void Functional::change_W()
{
    resW = m_mainWindow->getQImageO().width() * sliderW->value() / 100;
    resH = m_mainWindow->getQImageO().height() * sliderH->value() / 100;

    m_mainWindow->setQImageR(m_mainWindow->getQImageO().scaled(
        resW, resH, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    baseSize = m_mainWindow->getQImageO().scaled(m_mainWindow->getImageLabel()->size(),
        Qt::KeepAspectRatio).size();

    int displayW = baseSize.width() * sliderW->value() / 100;
    int displayH = baseSize.height() * sliderH->value() / 100;

    m_mainWindow->setQImageD(m_mainWindow->getQImageR().scaled(
        displayW, displayH,
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
    ));

    m_mainWindow->getImageLabel()->setPixmap(QPixmap::fromImage(m_mainWindow->getQImageD()));
}

void Functional::change_H()
{
    resW = m_mainWindow->getQImageO().width() * sliderW->value() / 100;
    resH = m_mainWindow->getQImageO().height() * sliderH->value() / 100;

    m_mainWindow->setQImageR(m_mainWindow->getQImageO().scaled(
        resW, resH, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    baseSize = m_mainWindow->getQImageO().scaled(m_mainWindow->getImageLabel()->size(),
        Qt::KeepAspectRatio).size();

    int displayW = baseSize.width() * sliderW->value() / 100;
    int displayH = baseSize.height() * sliderH->value() / 100;

    m_mainWindow->setQImageD(m_mainWindow->getQImageR().scaled(
        displayW, displayH,
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
    ));

    m_mainWindow->getImageLabel()->setPixmap(QPixmap::fromImage(m_mainWindow->getQImageD()));
}

//void Functional::change_Сontrast()
//{
//}

Functional::~Functional() {}


