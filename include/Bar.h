#pragma once

#include <QObject>
#include <QtWidgets/QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QPointer>

class PhotoEditorQT;

class Bar : public QObject
{
	Q_OBJECT

public:

	explicit Bar(PhotoEditorQT* parent = nullptr);
	QMenuBar* getMenuBar() { return mBar; }
	~Bar() override;

private slots:
	void actionOpen();
	void actionSave();


private:
	QPointer<PhotoEditorQT> m_mainWindow;//save

	QPointer<QMenuBar> mBar;
	QPointer<QMenu> fileMenu;
	QPointer<QMenu> helpMenu;

	QPointer<QAction> openAction;
	QPointer<QAction> saveAction;
	QPointer<QAction> exitAction;
	QPointer<QAction> aboutAction;
};




