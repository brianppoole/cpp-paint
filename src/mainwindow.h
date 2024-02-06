#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QActionGroup>
#include <QToolBar>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class PaintingArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PaintingArea* paintingArea;
    void createToolAction(const QString& name, int tool, QActionGroup* actionGroup, QToolBar* toolbar, PaintingArea* paintingArea);
};
#endif // MAINWINDOW_H
