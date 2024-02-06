#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "paintingarea.h"
#include <QToolBar>

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

    // Create an action for the "Pencil" button
    QAction *selectToolPencilAction = new QAction("Pencil", this);
    toolbar->addAction(selectToolPencilAction);
    connect(selectToolPencilAction, &QAction::triggered, [paintingArea]() { paintingArea->selectTool(PaintingArea::Pencil); });
    
    // Create an action for the "Line" button
    QAction *selectToolLineAction = new QAction("Line", this);
    toolbar->addAction(selectToolLineAction);
    connect(selectToolLineAction, &QAction::triggered, [paintingArea]() { paintingArea->selectTool(PaintingArea::Line); });

    // Create an action for the "Square" button
    QAction *selectToolSquareAction = new QAction("Square", this);
    toolbar->addAction(selectToolSquareAction);
    connect(selectToolSquareAction, &QAction::triggered, [paintingArea]() { paintingArea->selectTool(PaintingArea::Square); });
    
    // Create an action for the "Circle" button
    QAction *selectToolCircleAction = new QAction("Circle", this);
    toolbar->addAction(selectToolCircleAction);
    connect(selectToolCircleAction, &QAction::triggered, [paintingArea]() { paintingArea->selectTool(PaintingArea::Circle); });

    // Create an action for the "Erase" button
    QAction *selectToolEraseAction = new QAction("Erase", this);
    toolbar->addAction(selectToolEraseAction);
    connect(selectToolEraseAction, &QAction::triggered, [paintingArea]() { paintingArea->selectTool(PaintingArea::Eraser); });
}

MainWindow::~MainWindow()
{
    delete ui;
}