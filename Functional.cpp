#include "Functional.h"
#include "PhotoEditorQT.h"

Functional::Functional(PhotoEditorQT* mainWin) : QWidget(mainWin), m_mainWindow(mainWin)
{
    QGridLayout* mainToolsLayout = new QGridLayout(this);
    InitializationOfVar(mainWin);

    m_debounceTimer = new QTimer(this);
    m_debounceTimer->setSingleShot(true);

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
    colorLayout->addWidget(sliderBrightness, 1, 1);
    applyGroupStyle(colorGroup);

    QGroupBox* Group = new QGroupBox("Effects", this);
    QGridLayout* GroupLayout = new QGridLayout(Group);
    GroupLayout->addWidget(new QLabel("Sharpness:"), 0, 0);
    GroupLayout->addWidget(sliderSharpness, 0, 1);
    GroupLayout->addWidget(new QLabel("Blur:"), 1, 0);
    GroupLayout->addWidget(sliderBlur, 1, 1);
    applyGroupStyle(Group);

    mainToolsLayout->addWidget(resolutionGroup, 0, 0);
    mainToolsLayout->addWidget(colorGroup, 0, 1);
    mainToolsLayout->addWidget(Group, 0, 2);
    mainToolsLayout->addWidget(btnSave, 1, 0);
    mainToolsLayout->addWidget(btnReset, 1, 1);
    mainToolsLayout->addWidget(btnExit, 1, 2);

    toolsContainer = new QWidget();
    toolsContainer->setLayout(mainToolsLayout);

    //fix
    connect(m_debounceTimer, &QTimer::timeout, this, &Functional::updateAll);
    //table
    connect(sliderW, &QSlider::valueChanged, this, &Functional::onSliderValueChanged);
    connect(sliderH, &QSlider::valueChanged, this, &Functional::onSliderValueChanged);
    connect(sliderСontrast, &QSlider::valueChanged, this, &Functional::onSliderValueChanged);
    connect(sliderBrightness, &QSlider::valueChanged, this, &Functional::onSliderValueChanged);
    connect(sliderSharpness, &QSlider::valueChanged, this, &Functional::onSliderValueChanged);
    connect(sliderBlur, &QSlider::valueChanged, this, &Functional::onSliderValueChanged);
    //save
    connect(sliderW, &QSlider::sliderReleased, this, &Functional::updateResult);
    connect(sliderH, &QSlider::sliderReleased, this, &Functional::updateResult);
    connect(sliderСontrast, &QSlider::sliderReleased, this, &Functional::updateResult);
    connect(sliderBrightness, &QSlider::sliderReleased, this, &Functional::updateResult);
    connect(sliderBlur, &QSlider::sliderReleased, this, &Functional::updateResult);
    //btn
    connect(btnSave, &QPushButton::clicked, this, &Functional::saveBtn);
    connect(btnReset, &QPushButton::clicked, this, &Functional::resetBtn);
    connect(btnExit, &QPushButton::clicked, mainWin, &QWidget::close);
}
void Functional::onSliderValueChanged()
{
    m_debounceTimer->start(150);
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
    sliderСontrast->setRange(-100, 100);
    sliderСontrast->setValue(0);

    sliderBrightness = new QSlider(Qt::Horizontal, this);
    sliderBrightness->setRange(-100, 100);
    sliderBrightness->setValue(0);

    sliderSharpness = new QSlider(Qt::Horizontal, this);
    sliderSharpness->setRange(0, 100);
    sliderSharpness->setValue(0);

    sliderBlur = new QSlider(Qt::Horizontal, this);
    sliderBlur->setRange(0, 100);
    sliderBlur->setValue(0);

    btnSave = new QPushButton("Save",this);
    btnReset = new QPushButton("Reset",this);
    btnExit = new QPushButton("Exit",this);
   
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

void Functional::lutToImage(QImage& img, const int lut[256])
{
    for (int y = 0; y < img.height(); y++)
    {
        QRgb* line = reinterpret_cast<QRgb*>(img.scanLine(y));

        for (int x = 0; x < img.width(); x++)
        {
            QRgb pixel = line[x];
            line[x] = qRgba(lut[qRed(pixel)],
                lut[qGreen(pixel)],
                lut[qBlue(pixel)],
                qAlpha(pixel));
        }
    }
}

void Functional::contrastAndBrightness(int lut[256], int cV, int bV)
{
    factor = (259.0 * (cV + 255.0)) / (255.0 * (259.0 - cV));

    for (int i = 0; i < 256; i++)
    {
        int result = qRound(factor * (i - 128) + 128) + bV;
        lut[i] = qBound(0, result, 255);
    }
}

void Functional::sharpness(QImage& img, int value)
{

    QImage source = img;
    int width = img.width();
    int height = img.height();
    float amt = value / 100.0f;

    for (int y = 1; y < height - 1; y++)
    {
        const QRgb* prevLine = reinterpret_cast<const QRgb*>(source.constScanLine(y - 1));
        const QRgb* currLine = reinterpret_cast<const QRgb*>(source.constScanLine(y));
        const QRgb* nextLine = reinterpret_cast<const QRgb*>(source.constScanLine(y + 1));
        QRgb* destLine = reinterpret_cast<QRgb*>(img.scanLine(y));

        for (int x = 1; x < width - 1; x++)
        {
            QRgb c = currLine[x];
            QRgb t = prevLine[x];
            QRgb b = nextLine[x];
            QRgb l = currLine[x - 1];
            QRgb r = currLine[x + 1];

            int red = qRed(c) * 5 - (qRed(t) + qRed(b) + qRed(l) + qRed(r));
            int green = qGreen(c) * 5 - (qGreen(t) + qGreen(b) + qGreen(l) + qGreen(r));
            int blue = qBlue(c) * 5 - (qBlue(t) + qBlue(b) + qBlue(l) + qBlue(r));

            destLine[x] = qRgba(
                qBound(0, qRound(qRed(c) * (1 - amt) + red * amt), 255),
                qBound(0, qRound(qGreen(c) * (1 - amt) + green * amt), 255),
                qBound(0, qRound(qBlue(c) * (1 - amt) + blue * amt), 255),
                qAlpha(c)
            );
        }
    }
}

void Functional::updateAll()
{
    if (m_mainWindow->getQImageO().isNull()) return;
    //WH
    baseSize = m_mainWindow->getQImageO().scaled(
        m_mainWindow->getImageLabel()->size(),
        Qt::KeepAspectRatio
    ).size();

    int disW = baseSize.width() * sliderW->value() / 100;
    int disH = baseSize.height() * sliderH->value() / 100;
    //WH
    QImage previewImg = m_mainWindow->getQImageO().scaled(disW, disH,
        Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
        .convertToFormat(QImage::Format_ARGB32);


    //sharpness
    if (sliderSharpness->value() != 0) sharpness(previewImg, sliderSharpness->value());
    //sharpness
    //blur
    if (sliderSharpness->value() != 0) sharpness(previewImg, sliderSharpness->value()/4);
    if (sliderBlur->value() != 0)      sharpness(previewImg, -sliderBlur->value()/3);
    //blur


    //contrast


    if (sliderСontrast->value() != 0 || sliderBrightness->value() != 0)
    {
        contrastAndBrightness(lut, sliderСontrast->value(), sliderBrightness->value());
        lutToImage(previewImg, lut);
    }
    //contrast

    //res
    m_mainWindow->setQImageD(previewImg);
    m_mainWindow->getImageLabel()->setPixmap(QPixmap::fromImage(previewImg));
    //res
}

void Functional::updateResult()
{
    if (m_mainWindow->getQImageO().isNull()) return;

    //WH
    resW = m_mainWindow->getQImageO().width() * sliderW->value() / 100;
    resH = m_mainWindow->getQImageO().height() * sliderH->value() / 100;
    //WH

    QImage fullImg = m_mainWindow->getQImageO().scaled(resW, resH,
        Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
        .convertToFormat(QImage::Format_ARGB32);


    //sharpness
    if (sliderSharpness->value() != 0) sharpness(fullImg, sliderSharpness->value());
    if (sliderBlur->value() != 0)      sharpness(fullImg, -sliderBlur->value());
    //sharpness

    //contrast


    if (sliderСontrast->value() != 0 || sliderBrightness->value() != 0)
    {
        contrastAndBrightness(lut, sliderСontrast->value(), sliderBrightness->value());
        lutToImage(fullImg, lut);
    }
    //contrast

    //res
    m_mainWindow->setQImageR(fullImg);
    //res
}

void Functional::resetBtn()
{
    resetSlideWH();
}

void Functional::saveBtn()
{
    updateResult();

    if (m_mainWindow->getQImageR().isNull()) return;

    QString filePath = QFileDialog::getSaveFileName(this, tr("Save"), "", tr("Images (*.png *.jpg *.jpeg)"));

    if (!filePath.isEmpty()) 
    {
        m_mainWindow->getQImageR().save(filePath);
    }
}

void Functional::resetSlideWH()
{
    sliderW->setValue(100);
    sliderH->setValue(100);

    sliderСontrast->setValue(0);
    sliderBrightness->setValue(0);

    sliderSharpness->setValue(0);
    sliderBlur->setValue(0);

    updateAll();
    updateResult();
}

Functional::~Functional() {}


