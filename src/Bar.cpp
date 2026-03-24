#pragma once
#include "Bar.h"
#include "PhotoEditorQT.h"
#include <QFileDialog>
#include <QMessageBox>
#include "Functional.h"

Bar::Bar(PhotoEditorQT* mainWin) : QObject(mainWin), m_mainWindow(mainWin)
{
    if (!mainWin) return;
    mBar = mainWin->menuBar();

    fileMenu = mBar->addMenu(tr("File"));
    helpMenu = mBar->addMenu(tr("Reference"));

    openAction = fileMenu->addAction(tr("Open photo"));
    saveAction = fileMenu->addAction(tr("Save photo"));
    fileMenu->addSeparator();
    exitAction = fileMenu->addAction(tr("Exit"));

    aboutAction = helpMenu->addAction(tr("About the program"));


    QString barStyle = R"(
        QMenuBar 
        {
            background-color: #FFFFFF; 
            border: 1px solid #DEE2E6; 
            border-radius: 12px;  
            padding: 5px 10px;
            color: #2D3436;
            font-weight: bold;
            font-size: 12px;
            margin: 0px; 
        }

        QMenuBar::item 
        {
            background-color: transparent;
            padding: 8px 15px;
            border-radius: 8px; 
            margin-right: 5px;
        }

        QMenuBar::item:selected 
        {
            background-color: #F1F2F6;
            color: #000000;
        }

        QMenu 
        {
            background-color: #FFFFFF;
            border: 1px solid #DEE2E6;
            border-radius: 12px; 
            padding: 5px;
        }

        QMenu::item
        {
            padding: 8px 25px;
            border-radius: 6px;
            color: #2D3436;
        }

        QMenu::item:selected 
        {
            background-color: #2D3436; 
            color: #FFFFFF;
        }

        QMenu::separator
        {
            height: 1px;
            background: #EDF0F2;
            margin: 5px 10px;
        }
    )";
    mBar->setStyleSheet(barStyle);

    connect(openAction, &QAction::triggered, this, &Bar::actionOpen);
    connect(saveAction, &QAction::triggered, this, &Bar::actionSave);
    connect(exitAction, &QAction::triggered, mainWin, &QWidget::close);

    connect(aboutAction, &QAction::triggered, this, [this]()
        {
            if (m_mainWindow)
            {
                QMessageBox::about(m_mainWindow, tr("About the program"), tr("This is a simple photo editor demo in Qt and C++"));
            }
        });
}

void Bar::actionOpen()
{
	if (!m_mainWindow) return;

	QString fileName = QFileDialog::getOpenFileName(m_mainWindow, tr("Select an image"), "", tr("Image (*.jpg *.png *.jpeg)"));

	if (fileName.isEmpty()) return;


	m_mainWindow->setQImageO(fileName);

	m_mainWindow->setQImageR(m_mainWindow->getQImageO());
	
	QImage preview = m_mainWindow->getQImageR().scaled(
		m_mainWindow->getImageLabel()->size(),
		Qt::KeepAspectRatio,
		Qt::SmoothTransformation
	);

	m_mainWindow->setQImageD(preview);

	if (m_mainWindow->getFunctional()) m_mainWindow->getFunctional()->resetSlideWH();

	m_mainWindow->getImageLabel()->setPixmap(QPixmap::fromImage(preview));
	m_mainWindow->setImage(fileName);

}
void Bar::actionSave()
{
	if (!m_mainWindow || !m_mainWindow->getFunctional()) return;

	m_mainWindow->getFunctional()->updateResult();

	QImage imgToSave = m_mainWindow->getQImageR();
	if (imgToSave.isNull()) return;

	QString filePath = QFileDialog::getSaveFileName(m_mainWindow, tr("Save"), "", tr("Images (*.png *.jpg *.jpeg)"));

	if (!filePath.isEmpty()) 
	{
		imgToSave.save(filePath);
	}
}

Bar::~Bar() {}

