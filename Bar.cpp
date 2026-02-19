#pragma once
#include "Bar.h"
#include "PhotoEditorQT.h"
#include <QFileDialog>
#include <QMessageBox>
#include "Functional.h"

Bar::Bar(PhotoEditorQT* mainWin) : QObject(mainWin), m_mainWindow(mainWin)
{

	mBar = mainWin->menuBar();
	fileMenu = mBar->addMenu("File");
	helpMenu = mBar->addMenu("Reference");

	openAction = fileMenu->addAction("Open photo");
	saveAction = fileMenu->addAction("Save photo");
	exitAction = fileMenu->addAction("Exit");

	aboutAction = helpMenu->addAction("About the program");

	connect(openAction, &QAction::triggered, this, &Bar::actionOpen);
	connect(saveAction, &QAction::triggered, this, &Bar::actionSave);
	connect(exitAction, &QAction::triggered, mainWin, &QWidget::close);


	connect(aboutAction, &QAction::triggered, mainWin, [mainWin]() {
		QMessageBox::about(mainWin, "About the program", "This is a simple photo editor to demonstrate\n how easy it is to create applications\n in QT and C++");
	});

}

void Bar::actionOpen()
{
	QString fileName = QFileDialog::getOpenFileName(m_mainWindow, "Select an image", "", "Image (*.jpg *.png *.jpeg)");

	m_mainWindow->setQImageO(fileName);

	m_mainWindow->setQImageR(m_mainWindow->getQImageO());
	
	
	m_mainWindow->setQImageD(m_mainWindow->getQImageR().scaled(m_mainWindow->getImageLabel()->size(),
		Qt::KeepAspectRatio,
		Qt::SmoothTransformation));

	m_mainWindow->getFunctional()->resetSlideWH();
	m_mainWindow->getImageLabel()->setPixmap(
		QPixmap::fromImage(m_mainWindow->getQImageD()));

	m_mainWindow->setImage(fileName);

}
void Bar::actionSave()
{
	m_mainWindow->getFunctional()->getUpdate();

	if (m_mainWindow->getQImageR().isNull()) return;

	QString filePath = QFileDialog::getSaveFileName(m_mainWindow, tr("Save"), "", tr("Images (*.png *.jpg *.jpeg)"));

	if (!filePath.isEmpty())
	{
		m_mainWindow->getQImageR().save(filePath);
	}
}
Bar::~Bar()
{
}



