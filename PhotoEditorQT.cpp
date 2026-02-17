#include "PhotoEditorQT.h"
#include "ImageItem.h"
#include "Bar.h"
#include "Functional.h"

PhotoEditorQT::PhotoEditorQT(QWidget* parent) : QMainWindow(parent)
{
    imageLabel = new QLabel();
    imageLabel->setFixedSize(500, 350);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setScaledContents(false);
    imageLabel->setStyleSheet("QLabel { border: 1px solid #C2C2C2; border-radius: 10px; background-color: #DFDFDF; }");

    listImg = new QListWidget(this);
    listImg->setFixedWidth(150);
    listImg->setFixedHeight(350); 

    functional = new Functional(this);

    topWidget = new QWidget();
    topLayout = new QHBoxLayout(topWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(10);
    topLayout->setAlignment(Qt::AlignTop);

    topLayout->addWidget(imageLabel);
    topLayout->addWidget(listImg);

    container = new QWidget(this);
    mainLayout = new QVBoxLayout(container);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(20);


    mainLayout->addWidget(topWidget, 0, Qt::AlignLeft);
    mainLayout->addWidget(functional->getToolsContainer());

    mainLayout->addStretch();

    connect(listImg, &QListWidget::itemDoubleClicked, this, &PhotoEditorQT::on_listWidget_itemDoubleClicked);

    setCentralWidget(container);
    WindowSet();
    bar = new Bar(this);
}

void PhotoEditorQT::on_listWidget_itemDoubleClicked(QListWidgetItem* item)
{
    imgItem = qobject_cast<ImageItem*>(listImg->itemWidget(item));

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
        imgItem = new ImageItem;

        QPixmap pix(f.filePath());
        QString res = QString("%1x%2").arg(pix.width()).arg(pix.height());
        QString sizeStr = QString::number(f.size() / 1024) + " KB";

        imgItem->setData(pix.scaledToWidth(100, Qt::SmoothTransformation),
            f.fileName(), res, sizeStr, f.filePath());

        listItem->setSizeHint(imgItem->sizeHint());
        listImg->setItemWidget(listItem, imgItem);
    }
}

void PhotoEditorQT::WindowSet()
{
    this->setWindowTitle("Photo editor");
    this->setFixedSize(690,555);
    this->setWindowIcon(QIcon(":/PhotoEditorQT/image.ico"));
}

PhotoEditorQT::~PhotoEditorQT()
{
    
}