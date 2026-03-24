#include "PhotoEditorQT.h"
#include "ImageItem.h"
#include "Bar.h"
#include "Functional.h"

PhotoEditorQT::PhotoEditorQT(QWidget* parent) : QMainWindow(parent)
{
    imageLabel = new QLabel(this);
    imageLabel->setObjectName("previewLabel");
    imageLabel->setFixedSize(890, 490);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setScaledContents(false);

    QPointer<QWidget> listWrapper = new QWidget(this);
    listWrapper->setObjectName("listWrapper");
    listWrapper->setFixedWidth(170);
    listWrapper->setFixedHeight(490);

    QPointer <QVBoxLayout> listWrapperLayout = new QVBoxLayout(listWrapper);
    listWrapperLayout->setContentsMargins(10, 10, 10, 10);

    listImg = new QListWidget(this);
    listImg->setObjectName("photoList");
    listImg->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    listImg->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    listWrapperLayout->addWidget(listImg);

    functional = new Functional(this);
    functional->getToolsContainer()->setObjectName("toolsContainer");

    topWidget = new QWidget(this);
    topLayout = new QHBoxLayout(topWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(15);
    topLayout->setAlignment(Qt::AlignTop);

    topLayout->addWidget(imageLabel);
    topLayout->addWidget(listWrapper);

    container = new QWidget(this);
    container->setObjectName("mainContainer");
    mainLayout = new QVBoxLayout(container);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(20);

    bar = new Bar(this);
    QPointer <QMenuBar> mBar = bar->getMenuBar();
    mBar->setParent(container);

    mainLayout->addWidget(mBar);
    mainLayout->addWidget(topWidget, 0, Qt::AlignLeft);
    mainLayout->addWidget(functional->getToolsContainer());
    mainLayout->addStretch();

    connect(listImg, &QListWidget::itemDoubleClicked, this, &PhotoEditorQT::on_listWidget_itemDoubleClicked);

    setCentralWidget(container);
    WindowSet();

    

    QString softContrastStyle = R"(
       
        QMainWindow, QWidget#mainContainer 
        {
            background-color: #EDEDED; 
            color: #495057;
        }

     
        QWidget#listWrapper 
        {
            background-color: #FFFFFF;
            border: 1px solid #DEE2E6;
            border-radius: 20px;
        }

        QListWidget#photoList 
        {
            background-color: transparent;
            border: none;
            outline: none;
        }

        QListWidget#photoList::item
        {
            background-color: #F8F9FA; 
            border: 1px solid #E9ECEF;
            border-radius: 12px;
            margin-bottom: 8px;
            padding: 5px;
        }

        QListWidget#photoList::item:hover 
        {
            background-color: #F1F3F5;
            border: 1px solid #DEE2E6;
        }

 
        QListWidget#photoList::item:selected
        {
            background-color: #E9ECEF;
            border: 1px solid #ADB5BD;
            color: #212529;
        }


        QScrollBar:vertical
        {
            border: none;
            background: transparent;
            width: 4px;
            
        }
        QScrollBar::handle:vertical 
        {
            background: #CED4DA;
            border-radius: 2px;
        }

       
        QLabel#previewLabel 
        {
            background-color: #FFFFFF;
            border: 1px solid #DEE2E6;
            border-radius: 20px;
        }
  
    
    )";
    this->setStyleSheet(softContrastStyle);
}

void PhotoEditorQT::on_listWidget_itemDoubleClicked(QListWidgetItem* item)
{
    imgItem = qobject_cast<ImageItem*>(listImg->itemWidget(item));
    if (!imgItem) return;

    setQImageO(imgItem->getPath());//1

    imgR = imgO;//2

    imgD = imgO.scaled(
        imageLabel->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
    );//3

    functional->resetSlideWH();
    imageLabel->setPixmap(QPixmap::fromImage(imgD));

}

void PhotoEditorQT::setImage(QString& filename)
{
    listImg->clear();

    infoFile.setFile(filename);

    dir = infoFile.absolutePath();

    filter = { "*.jpg", "*.png", "*.jpeg" };
    list = dir.entryInfoList(filter);

    for (int i = 0; i < list.count(); i++)
    {
        QFileInfo f = list.at(i);
        QListWidgetItem* listItem = new QListWidgetItem(listImg);
        imgItem = new ImageItem(listImg);

        QPixmap pix(f.filePath());
        QString res = QString("%1x%2").arg(pix.width()).arg(pix.height());
        QString sizeStr = QString::number(f.size() / 1024) + " KB";

        imgItem->setData(pix.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation),
            f.fileName(), res, sizeStr, f.filePath());

        listItem->setSizeHint(imgItem->sizeHint());
        listImg->setItemWidget(listItem, imgItem);
    }
}

void PhotoEditorQT::WindowSet()
{
    this->setWindowTitle("Photo editor");
    this->setFixedSize(1100,760);
    this->setWindowIcon(QIcon(":/PhotoEditorQT/image.ico"));
}

PhotoEditorQT::~PhotoEditorQT() {}