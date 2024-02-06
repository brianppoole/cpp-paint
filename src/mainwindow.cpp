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
        if (!fileName.isEmpty()) {
            paintingArea->loadImage(fileName); 
        }
    });
    QAction *saveAction = new QAction(style()->standardIcon(QStyle::SP_DialogSaveButton), "Save", this);
    toolbar->addAction(saveAction);
    connect(saveAction, &QAction::triggered, [paintingArea]() { 
        // Prompt the user to select a file name and location to save the image
        QString fileName = QFileDialog::getSaveFileName(paintingArea, tr("Save Image"), "", tr("Images (*.png *.xpm *.jpg)"));
        QString fileType = QFileInfo(fileName).suffix();
        if (!fileName.isEmpty()) {
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

    // Create an action for the "Pencil" button
    QAction *selectToolPencilAction = new QAction("Pencil", this);
    selectToolPencilAction->setCheckable(true); // Make the action checkable
    actionGroup->addAction(selectToolPencilAction); // Add the action to the action group
    toolbar->addAction(selectToolPencilAction);
    connect(selectToolPencilAction, &QAction::triggered, [paintingArea, selectToolPencilAction]() { 
        paintingArea->selectTool(PaintingArea::Pencil); 
        selectToolPencilAction->setChecked(true); 
    });
    // Set the action as the checked action if the tool is Pencil
    if (paintingArea->getSelectedTool() == PaintingArea::Pencil) {
        selectToolPencilAction->setChecked(true);
    }

    // Create an action for the "Line" button
    QAction *selectToolLineAction = new QAction("Line", this);
    selectToolLineAction->setCheckable(true);
    actionGroup->addAction(selectToolLineAction);
    toolbar->addAction(selectToolLineAction);
    connect(selectToolLineAction, &QAction::triggered, [paintingArea, selectToolLineAction]() { 
        paintingArea->selectTool(PaintingArea::Line); 
        selectToolLineAction->setChecked(true); 
    });
    // Set the action as the checked action if the tool is Line
    if (paintingArea->getSelectedTool() == PaintingArea::Line) {
        selectToolLineAction->setChecked(true);
    }

    // Create an action for the "Rectangle" button
    QAction *selectToolRectangleAction = new QAction("Rectangle", this);
    selectToolRectangleAction->setCheckable(true);
    actionGroup->addAction(selectToolRectangleAction);
    toolbar->addAction(selectToolRectangleAction);
    connect(selectToolRectangleAction, &QAction::triggered, [paintingArea, selectToolRectangleAction]() { 
        paintingArea->selectTool(PaintingArea::Rectangle); 
        selectToolRectangleAction->setChecked(true); 
    });
    // Set the action as the checked action if the tool is Rectangle
    if (paintingArea->getSelectedTool() == PaintingArea::Rectangle) {
        selectToolRectangleAction->setChecked(true);
    }

    // Create an action for the "Ellipse" button
    QAction *selectToolEllipseAction = new QAction("Ellipse", this);
    selectToolEllipseAction->setCheckable(true);
    actionGroup->addAction(selectToolEllipseAction);
    toolbar->addAction(selectToolEllipseAction);
    connect(selectToolEllipseAction, &QAction::triggered, [paintingArea, selectToolEllipseAction]() { 
        paintingArea->selectTool(PaintingArea::Ellipse); 
        selectToolEllipseAction->setChecked(true); 
    });
    // Set the action as the checked action if the tool is Ellipse
    if (paintingArea->getSelectedTool() == PaintingArea::Ellipse) {
        selectToolEllipseAction->setChecked(true);
    }

    // Create an action for the "Eraser" button
    QAction *selectToolEraserAction = new QAction("Eraser", this);
    selectToolEraserAction->setCheckable(true);
    actionGroup->addAction(selectToolEraserAction);
    toolbar->addAction(selectToolEraserAction);
    connect(selectToolEraserAction, &QAction::triggered, [paintingArea, selectToolEraserAction]() { 
        paintingArea->selectTool(PaintingArea::Eraser); 
        selectToolEraserAction->setChecked(true); 
    });
    // Set the action as the checked action if the tool is Eraser
    if (paintingArea->getSelectedTool() == PaintingArea::Eraser) {
        selectToolEraserAction->setChecked(true);
    }

    // Create an action for changing the color
    QAction *colorAction = new QAction("Color", this);
    toolbar->addAction(colorAction);
    connect(colorAction, &QAction::triggered, [paintingArea, colorAction, this]() {
        QColor color = QColorDialog::getColor(paintingArea->getColor(), this, "Select Color");
        if (color.isValid()) {
            paintingArea->setColor(color);
        }
    });
}

MainWindow::~MainWindow()
{
    // Save the last selected tool
    QSettings settings("BrianPoole", "CPP-Paint");
    settings.setValue("lastSelectedTool", static_cast<int>(static_cast<PaintingArea*>(this->centralWidget())->getSelectedTool()));

    delete ui;
}