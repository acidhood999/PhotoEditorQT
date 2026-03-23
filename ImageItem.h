#pragma once

#include <QWidget>
#include <QPixmap> 
#include <QString>
#include <QPointer> 
#include <memory>

class QLabel;
class QGridLayout;

class ImageItem : public QWidget
{
    Q_OBJECT

public:
    explicit ImageItem(QWidget* parent = nullptr);
    ~ImageItem() override;

    void setData(const QPixmap& pixmap, const QString& name, const QString& resolution, const QString& size_img, const QString& path_img);
    QString getPath() const { return this->path; }

private:
    QPointer<QLabel> img;
    QPointer <QGridLayout> layout;

    QString path;
};
