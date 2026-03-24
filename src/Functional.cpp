#include "Functional.h"
#include "PhotoEditorQT.h"

Functional::Functional(PhotoEditorQT* mainWin) : QWidget(mainWin), m_mainWindow(mainWin)
{
    toolsContainer = new QWidget(this);
    QPointer<QGridLayout> mainToolsLayout = new QGridLayout(toolsContainer);
    mainToolsLayout->setContentsMargins(5, 5, 5, 5);
    mainToolsLayout->setSpacing(15);

    InitializationOfVar();

    m_debounceTimer = new QTimer(this);
    m_debounceTimer->setSingleShot(true);

    QPointer <QGroupBox> resolutionGroup = new QGroupBox("Resolution", this);
    QPointer <QGridLayout> resolutionLayout = new QGridLayout(resolutionGroup);
    resolutionLayout->addWidget(new QLabel("Width"), 0, 0);
    resolutionLayout->addWidget(sliderW, 0, 1);
    resolutionLayout->addWidget(new QLabel("Height"), 1, 0);
    resolutionLayout->addWidget(sliderH, 1, 1);
    applyGroupStyle(resolutionGroup);

    QPointer<QGroupBox> colorGroup = new QGroupBox("Contrast and Brightness", this);
    QPointer<QGridLayout> colorLayout = new QGridLayout(colorGroup);
    colorLayout->addWidget(new QLabel("Contrast"), 0, 0);
    colorLayout->addWidget(sliderСontrast, 0, 1);
    colorLayout->addWidget(new QLabel("Brightness"), 1, 0);
    colorLayout->addWidget(sliderBrightness, 1, 1);
    applyGroupStyle(colorGroup);

    QPointer<QGroupBox> Group = new QGroupBox("Effects", this);
    QPointer<QGridLayout> GroupLayout = new QGridLayout(Group);
    GroupLayout->addWidget(new QLabel("Sharpness"), 0, 0);
    GroupLayout->addWidget(sliderSharpness, 0, 1);
    GroupLayout->addWidget(new QLabel("Blur"), 1, 0);
    GroupLayout->addWidget(sliderBlur, 1, 1);
    applyGroupStyle(Group);

    mainToolsLayout->addWidget(resolutionGroup, 0, 0);
    mainToolsLayout->addWidget(colorGroup, 0, 1);
    mainToolsLayout->addWidget(Group, 0, 2);

    QPointer <QHBoxLayout> btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(10);
    btnLayout->addWidget(btnSave);
    btnLayout->addWidget(btnReset);
    btnLayout->addWidget(btnExit);
    mainToolsLayout->addLayout(btnLayout, 1, 0, 1, 3);

    toolsContainer->setStyleSheet(this->styleSheet());

    connect(m_debounceTimer, &QTimer::timeout, this, &Functional::updateAll);
    connect(sliderW, &QSlider::valueChanged, this, &Functional::onSliderValueChanged);
    connect(sliderH, &QSlider::valueChanged, this, &Functional::onSliderValueChanged);
    connect(sliderСontrast, &QSlider::valueChanged, this, &Functional::onSliderValueChanged);
    connect(sliderBrightness, &QSlider::valueChanged, this, &Functional::onSliderValueChanged);
    connect(sliderSharpness, &QSlider::valueChanged, this, &Functional::onSliderValueChanged);
    connect(sliderBlur, &QSlider::valueChanged, this, &Functional::onSliderValueChanged);
    connect(sliderW, &QSlider::sliderReleased, this, &Functional::updateResult);
    connect(sliderH, &QSlider::sliderReleased, this, &Functional::updateResult);
    connect(sliderСontrast, &QSlider::sliderReleased, this, &Functional::updateResult);
    connect(sliderBrightness, &QSlider::sliderReleased, this, &Functional::updateResult);
    connect(sliderBlur, &QSlider::sliderReleased, this, &Functional::updateResult);
    connect(btnSave, &QPushButton::clicked, this, &Functional::saveBtn);
    connect(btnReset, &QPushButton::clicked, this, &Functional::resetBtn);
    connect(btnExit, &QPushButton::clicked, mainWin, &QWidget::close);
}

void Functional::onSliderValueChanged()
{
    m_debounceTimer->start(150);
}

void Functional::InitializationOfVar()
{
    sliderW = new QSlider(Qt::Horizontal, this); sliderW->setRange(10, 200); sliderW->setValue(100);
    sliderH = new QSlider(Qt::Horizontal, this); sliderH->setRange(10, 200); sliderH->setValue(100);
    sliderСontrast = new QSlider(Qt::Horizontal, this); sliderСontrast->setRange(-100, 100); sliderСontrast->setValue(0);
    sliderBrightness = new QSlider(Qt::Horizontal, this); sliderBrightness->setRange(-100, 100); sliderBrightness->setValue(0);
    sliderSharpness = new QSlider(Qt::Horizontal, this); sliderSharpness->setRange(0, 100); sliderSharpness->setValue(0);
    sliderBlur = new QSlider(Qt::Horizontal, this); sliderBlur->setRange(0, 100); sliderBlur->setValue(0);

    btnSave = new QPushButton("Save Image", this);
    btnReset = new QPushButton("Reset All", this);
    btnExit = new QPushButton("Exit", this);

    btnSave->setObjectName("btnSave");
    btnReset->setObjectName("btnReset");
    btnExit->setObjectName("btnExit");


    QString elementsStyle = R"(
   
    QLabel 
    {
        color: #2D3436; 
        font-size: 12px;
        font-weight: bold; 
    }
    
    QPushButton 
    {
        background-color: #FFFFFF;
        border: 1px solid #DEE2E6;
        border-radius: 12px;
        padding: 8px 20px;
        color: #2D3436;
        font-weight: bold;
    }

    QPushButton:hover { background-color: #F1F2F6; }
    QPushButton#btnSave { background-color: #2D3436; color: #FFFFFF; }
    QPushButton#btnSave:hover { background-color: #000000; }

    QSlider::groove:horizontal
    {
        border: 1px solid #DEE2E6;
        height: 6px;
        background: #F8F9FA;
        border-radius: 3px;
    }

    QSlider::sub-page:horizontal 
    {
        background: #2D3436; 
        border: 1px solid #2D3436;
        height: 6px;
        border-radius: 3px;
    }

 
    QSlider::add-page:horizontal 
    {
        background: #F1F2F6;
        border: 1px solid #DEE2E6;
        height: 6px;
        border-radius: 3px;
    }

    QSlider::handle:horizontal 
    {
        background: #FFFFFF;
        border: 2px solid #2D3436;
        width: 14px;
        height: 14px;
        margin: -5px 0;
        border-radius: 8px;
    }

    QSlider::handle:horizontal:hover
    {
        background: #F1F2F6;
        transform: scale(1.1);
    }

    QPushButton#btnExit 
    {
        background-color: #FF7675;           
        border: none;
    }

    QPushButton#btnExit:hover 
    {
        background-color: #D63031; 
    }
    )";

    this->setStyleSheet(elementsStyle);
}

void Functional::applyGroupStyle(QGroupBox* group)
{
    group->setStyleSheet(
        "QGroupBox {"
        "border: 1px solid #DEE2E6;"
        "border-radius: 20px;"
        "background-color: #FFFFFF;"
        "margin-top: 5px;"
        "color: #2D3436;"
        "font-size: 12px;"
        "font-weight: bold;"
        "padding-top: 30px;"
        "}"
        "QGroupBox::title {"
        "subcontrol-origin: margin;"
        "subcontrol-position: top center;"
        "top: 15px;"
        "color: #2D3436;" 
        "font-weight: 800;"
        "font-size: 13px;"
        "text-transform: uppercase;"
        "letter-spacing: 1px;"
        "}"
    );
}
QImage Functional::processImageStatic(QImage img, int sharp, int blur, int cV, int bV)
{
    if (img.isNull()) return img;
    QImage res = img.convertToFormat(QImage::Format_ARGB32);

  
    if (sharp != 0) applySharpness(res, sharp);
    if (blur != 0)  applySharpness(res, -blur); 


    if (cV != 0 || bV != 0)
    {
        int localLut[256];
        float factor = (259.0f * (cV + 255.0f)) / (255.0f * (259.0f - cV));
        for (int i = 0; i < 256; i++) 
        {
            localLut[i] = qBound(0, qRound(factor * (i - 128) + 128) + bV, 255);
        }
        for (int y = 0; y < res.height(); y++)
        {
            QRgb* line = (QRgb*)res.scanLine(y);
            for (int x = 0; x < res.width(); x++)
            {
                line[x] = qRgba(localLut[qRed(line[x])], localLut[qGreen(line[x])], localLut[qBlue(line[x])], qAlpha(line[x]));
            }
        }
    }
    return res;
}

void Functional::applySharpness(QImage& img, int value)
{
    if (img.isNull() || value == 0) return;

    QImage source = img;
    float amt = value / 100.0f;
    int width = img.width();
    int height = img.height();

    for (int y = 1; y < height - 1; y++)
    {
        const QRgb* prev = (const QRgb*)source.constScanLine(y - 1);
        const QRgb* curr = (const QRgb*)source.constScanLine(y);
        const QRgb* next = (const QRgb*)source.constScanLine(y + 1);
        QRgb* dest = (QRgb*)img.scanLine(y);

        for (int x = 1; x < width - 1; x++) 
        {
            int r = qRed(curr[x]) * 5 - (qRed(prev[x]) + qRed(next[x]) + qRed(curr[x - 1]) + qRed(curr[x + 1]));
            int g = qGreen(curr[x]) * 5 - (qGreen(prev[x]) + qGreen(next[x]) + qGreen(curr[x - 1]) + qGreen(curr[x + 1]));
            int b = qBlue(curr[x]) * 5 - (qBlue(prev[x]) + qBlue(next[x]) + qBlue(curr[x - 1]) + qBlue(curr[x + 1]));

            dest[x] = qRgba(
                qBound(0, qRound(qRed(curr[x]) * (1 - amt) + r * amt), 255),
                qBound(0, qRound(qGreen(curr[x]) * (1 - amt) + g * amt), 255),
                qBound(0, qRound(qBlue(curr[x]) * (1 - amt) + b * amt), 255),
                qAlpha(curr[x])
            );
        }
    }
}


void Functional::updateAll()
{
    if (!m_mainWindow || m_mainWindow->getQImageO().isNull()) return;

    // size
    QSize labelSize = m_mainWindow->getImageLabel()->size();
    QSize scaledSize = m_mainWindow->getQImageO().scaled(labelSize, Qt::KeepAspectRatio).size();

    int previewW = scaledSize.width() * sliderW->value() / 100;
    int previewH = scaledSize.height() * sliderH->value() / 100;

    // 
    QImage previewImg = m_mainWindow->getQImageO().scaled(previewW, previewH, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    // filters
    previewImg = processImageStatic(previewImg,
        sliderSharpness->value(),
        sliderBlur->value(),
        sliderСontrast->value(),
        sliderBrightness->value());

    // display
    m_mainWindow->setQImageD(previewImg); 
    m_mainWindow->getImageLabel()->setPixmap(QPixmap::fromImage(previewImg));
}

void Functional::updateResult()
{
    if (!m_mainWindow || m_mainWindow->getQImageO().isNull()) return;

    int resW = m_mainWindow->getQImageO().width() * sliderW->value() / 100;
    int resH = m_mainWindow->getQImageO().height() * sliderH->value() / 100;
    int sV = sliderSharpness->value();
    int blV = sliderBlur->value();
    int cV = sliderСontrast->value();
    int bV = sliderBrightness->value();
    QImage sourceImg = m_mainWindow->getQImageO();

    QPointer<QFutureWatcher<QImage>> watcher = new QFutureWatcher<QImage>(this);

    connect(watcher.data(), &QFutureWatcher<QImage>::finished, this, [=]()
    {
        if (watcher && m_mainWindow)
        {
            m_mainWindow->setQImageR(watcher->result());
            watcher->deleteLater();
              
            // m_mainWindow->getImageLabel()->setPixmap(QPixmap::fromImage(m_mainWindow->getQImageR().scaled(m_mainWindow->getImageLabel()->size(), Qt::KeepAspectRatio)));
        }
    });

    watcher->setFuture(QtConcurrent::run([=]()
    {
        QImage scaled = sourceImg.scaled(resW, resH, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        return processImageStatic(scaled, sV, blV, cV, bV);
    }));
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


