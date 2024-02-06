#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "paintingarea.h"
#include <QToolBar>
#include <QActionGroup>
#include <QSettings>
#include <QFileDialog>
#include <QColorDialog>
#include <QFileInfo>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Brian's C++ Painting App");

    // Set the application style and stylesheet
    qApp->setStyle("fusion");
    qApp->setStyleSheet("QMainWindow { background-color: #2F4858; }"
                    "QToolBar { background-color: #136173; border: none; margin: 2px; }"
                    "QToolBar::separator { background-color: #009487; width: 2px; height: 2px; margin: 5px; }"
                    "QToolButton { background-color: #136173; border: none; color: white; margin: 0px; padding: 5px; border-radius: 3px; }"
                    "QToolButton:hover { background-color: #00AC7B; }"
                    "QToolButton:checked { background-color: #5EC265; }");

    // Create a PaintingArea and set it as the central widget
    PaintingArea *paintingArea = new PaintingArea(this);
    this->setCentralWidget(paintingArea);

    paintingArea->setStyleSheet("background-color: white;");
    paintingArea->setCursor(Qt::CrossCursor);

    // Create a toolbar
    QToolBar *toolbar = addToolBar("toolbar");
    toolbar->setIconSize(QSize(20, 20));

    // Load the last selected tool
    QSettings settings("BrianPoole", "CPP-Paint");
    paintingArea->selectTool(static_cast<PaintingArea::Tool>(settings.value("lastSelectedTool", PaintingArea::Pencil).toInt()));

    // Create actions for clearing the image and changing the color
    QAction *clearAction = new QAction(style()->standardIcon(QStyle::SP_FileIcon), "Clear", this);
    toolbar->addAction(clearAction);
    connect(clearAction, &QAction::triggered, [paintingArea]() { paintingArea->clearImage(); });

    // Create actions for Load/Save
    QAction *loadAction = new QAction(style()->standardIcon(QStyle::SP_DialogOpenButton), "Load", this);
    toolbar->addAction(loadAction);
    connect(loadAction, &QAction::triggered, [paintingArea, this]() { 
        // Prompt the user to select an image file to load
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Images (*.png *.xpm *.jpg)"));
        if (!fileName.isEmpty()) 
        {
            paintingArea->loadImage(fileName); 
        }
    });
    QAction *saveAction = new QAction(style()->standardIcon(QStyle::SP_DialogSaveButton), "Save", this);
    toolbar->addAction(saveAction);
    connect(saveAction, &QAction::triggered, [paintingArea]() { 
        // Prompt the user to select a file name and location to save the image
        QString fileName = QFileDialog::getSaveFileName(paintingArea, tr("Save Image"), "", tr("Images (*.png *.xpm *.jpg)"));
        QString fileType = QFileInfo(fileName).suffix();
        if (!fileName.isEmpty()) 
        {
            paintingArea->saveImage(fileName, fileType.toStdString().c_str()); 
        }
    });

    // Add a separator to the toolbar
    toolbar->addSeparator();

    // Create actions for Undo/Redo
    QAction *undoAction = new QAction(style()->standardIcon(QStyle::SP_ArrowBack), "Undo", this);
    toolbar->addAction(undoAction);
    connect(undoAction, &QAction::triggered, [paintingArea]() { paintingArea->undo(); });
    QAction *redoAction = new QAction(style()->standardIcon(QStyle::SP_ArrowForward), "Redo", this);
    toolbar->addAction(redoAction);
    connect(redoAction, &QAction::triggered, [paintingArea]() { paintingArea->redo(); });

    // Add a separator to the toolbar
    toolbar->addSeparator();

    // Create a QActionGroup
    QActionGroup *actionGroup = new QActionGroup(this);

    // Create actions for each tool
    createToolAction("Pencil", PaintingArea::Pencil, actionGroup, toolbar, paintingArea);
    createToolAction("Line", PaintingArea::Line, actionGroup, toolbar, paintingArea);
    createToolAction("Rectangle", PaintingArea::Rectangle, actionGroup, toolbar, paintingArea);
    createToolAction("Ellipse", PaintingArea::Ellipse, actionGroup, toolbar, paintingArea);
    createToolAction("Star", PaintingArea::Star, actionGroup, toolbar, paintingArea);
    createToolAction("Eraser", PaintingArea::Eraser, actionGroup, toolbar, paintingArea);

    // Create an action for changing the color
    QAction *colorAction = new QAction("Color", this);
    toolbar->addAction(colorAction);
    connect(colorAction, &QAction::triggered, [paintingArea, colorAction, this]() {
        QColor color = QColorDialog::getColor(paintingArea->getColor(), this, "Select Pen Color");
        if (color.isValid()) {
            paintingArea->setPenColor(color);
        }
    });
}

/**
 * Create an action for a tool and add it to the toolbar
 */
void MainWindow::createToolAction(const QString& name, int tool, QActionGroup* actionGroup, QToolBar* toolbar, PaintingArea* paintingArea) 
{
    // Create an action for the tool
    QAction *action = new QAction(name, this);
    action->setCheckable(true);
    actionGroup->addAction(action);
    toolbar->addAction(action);

    // Connect the action to the PaintingArea's selectTool method
    connect(action, &QAction::triggered, [paintingArea, action, tool]() { 
        paintingArea->selectTool(static_cast<PaintingArea::Tool>(tool)); 
        action->setChecked(true); 
    });

    // Set the action as checked if it is the currently selected tool
    if (paintingArea->getSelectedTool() == tool) 
    {
        action->setChecked(true);
    }
}

MainWindow::~MainWindow()
{
    // Save the last selected tool
    QSettings settings("BrianPoole", "CPP-Paint");
    settings.setValue("lastSelectedTool", static_cast<int>(static_cast<PaintingArea*>(this->centralWidget())->getSelectedTool()));

    delete ui;
}