#pragma once

#include <QWidget>
#include <QPixmap> 
#include <QString>


class QLabel;
class QGridLayout;

class ImageItem : public QWidget
{
    Q_OBJECT

public:
    ImageItem(QWidget* parent = nullptr);
    ~ImageItem();

    void setData(const QPixmap& pixmap, const QString& name, const QString& resolution, const QString& size_img, const QString& path_img);
    QString getPath() const { return this->path; }

private:
    QLabel* img = nullptr;
    QGridLayout* layout = nullptr;

    QString path;
};
