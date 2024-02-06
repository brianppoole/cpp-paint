#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "paintingarea.h"
#include <QToolBar>
#include <QActionGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create a PaintingArea and set it as the central widget
    PaintingArea *paintingArea = new PaintingArea(this);
    this->setCentralWidget(paintingArea);

    // Create a toolbar
    QToolBar *toolbar = addToolBar("toolbar");

    // Create actions for Undo/Redo
    QAction *undoAction = new QAction("Undo", this);
    toolbar->addAction(undoAction);
    connect(undoAction, &QAction::triggered, [paintingArea]() { paintingArea->undo(); });
    QAction *redoAction = new QAction("Redo", this);
    toolbar->addAction(redoAction);
    connect(redoAction, &QAction::triggered, [paintingArea]() { paintingArea->redo(); });

    // Create a QActionGroup
    QActionGroup *actionGroup = new QActionGroup(this);

    // Create an action for the "Pencil" button
    QAction *selectToolPencilAction = new QAction("Pencil", this);
    selectToolPencilAction->setCheckable(true); // Make the action checkable
    selectToolPencilAction->setChecked(true); // Set the action as checked by default
    actionGroup->addAction(selectToolPencilAction); // Add the action to the action group
    toolbar->addAction(selectToolPencilAction);
    connect(selectToolPencilAction, &QAction::triggered, [paintingArea, selectToolPencilAction]() { 
        paintingArea->selectTool(PaintingArea::Pencil); 
        selectToolPencilAction->setChecked(true); 
    });

    // Create an action for the "Line" button
    QAction *selectToolLineAction = new QAction("Line", this);
    selectToolLineAction->setCheckable(true);
    actionGroup->addAction(selectToolLineAction);
    toolbar->addAction(selectToolLineAction);
    connect(selectToolLineAction, &QAction::triggered, [paintingArea, selectToolLineAction]() { 
        paintingArea->selectTool(PaintingArea::Line); 
        selectToolLineAction->setChecked(true); 
    });

    // Create an action for the "Rectangle" button
    QAction *selectToolRectangleAction = new QAction("Rectangle", this);
    selectToolRectangleAction->setCheckable(true);
    actionGroup->addAction(selectToolRectangleAction);
    toolbar->addAction(selectToolRectangleAction);
    connect(selectToolRectangleAction, &QAction::triggered, [paintingArea, selectToolRectangleAction]() { 
        paintingArea->selectTool(PaintingArea::Rectangle); 
        selectToolRectangleAction->setChecked(true); 
    });

    // Create an action for the "Ellipse" button
    QAction *selectToolEllipseAction = new QAction("Ellipse", this);
    selectToolEllipseAction->setCheckable(true);
    actionGroup->addAction(selectToolEllipseAction);
    toolbar->addAction(selectToolEllipseAction);
    connect(selectToolEllipseAction, &QAction::triggered, [paintingArea, selectToolEllipseAction]() { 
        paintingArea->selectTool(PaintingArea::Ellipse); 
        selectToolEllipseAction->setChecked(true); 
    });

    // Create an action for the "Eraser" button
    QAction *selectToolEraserAction = new QAction("Eraser", this);
    selectToolEraserAction->setCheckable(true);
    actionGroup->addAction(selectToolEraserAction);
    toolbar->addAction(selectToolEraserAction);
    connect(selectToolEraserAction, &QAction::triggered, [paintingArea, selectToolEraserAction]() { 
        paintingArea->selectTool(PaintingArea::Eraser); 
        selectToolEraserAction->setChecked(true); 
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}