#pragma once

#include <QObject>
#include <QtWidgets/QMainWindow>
#include <QMenuBar>
#include <QMenu>

class PhotoEditorQT;

class Bar : public QObject
{
	Q_OBJECT

public:

	Bar(PhotoEditorQT* parent = nullptr);

	~Bar();

private slots:
	void actionOpen();
	void actionSave();


private:
	PhotoEditorQT* m_mainWindow = nullptr;//save

	QMenuBar* mBar = nullptr;
	QMenu* fileMenu = nullptr;
	QMenu* helpMenu = nullptr;

	QAction* openAction = nullptr;
	QAction* saveAction = nullptr;
	QAction* exitAction = nullptr;
	QAction* aboutAction = nullptr;


	

};




