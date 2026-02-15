#include "PhotoEditorQT.h"
#include "ImageItem.h"
#include "Bar.h"
#include "Functional.h"

PhotoEditorQT::PhotoEditorQT(QWidget* parent) : QMainWindow(parent)
{
    imageLabel = new QLabel();
    imageLabel->setFixedSize(500, 350);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet(
        "QLabel {"
        "   border: 1px solid #C2C2C2;"
        "   border-radius: 10px;"
        "   background-color: #DFDFDF;"
        "}"
    );


    listImg = new QListWidget(this);
    listImg->setFixedWidth(150);
       
    
   
    functional = new Functional(this);

    leftContent = new QWidget();
    leftLayout = new QVBoxLayout(leftContent);
    leftLayout->addWidget(imageLabel, 0, Qt::AlignCenter);
    leftLayout->addWidget(functional->getToolsContainer()); 
    leftLayout->addStretch();

    container = new QWidget(this);
    hLayout = new QHBoxLayout(container);
    hLayout->addWidget(leftContent);
    hLayout->addWidget(listImg);

    connect(listImg, &QListWidget::itemDoubleClicked, this, &PhotoEditorQT::on_listWidget_itemDoubleClicked);

    setCentralWidget(container);
    WindowSet();
    
    bar = new Bar(this);
}

void PhotoEditorQT::on_listWidget_itemDoubleClicked(QListWidgetItem* item)
{
    imgItem = qobject_cast<ImageItem*>(listImg->itemWidget(item));
    firstImg = imgItem->getPath();
    
    secondImg = firstImg.scaled(
        imageLabel->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
    );

    functional->resetSlideWH();

    imageLabel->setPixmap(secondImg);

}

void PhotoEditorQT::setImage(QString& filename)
{
    listImg->clear();

    QFileInfo infoFile(filename);
    QDir dir = infoFile.absolutePath();
    QStringList filter = { "*.jpg", "*.png", "*.jpeg" };
    QFileInfoList list = dir.entryInfoList(filter);

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
    this->setFixedSize(680, 800);
 
}

PhotoEditorQT::~PhotoEditorQT()
{
    
}