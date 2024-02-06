#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>

class PaintingArea : public QWidget {
    Q_OBJECT

public:
    PaintingArea(QWidget *parent = nullptr);
    
    enum Mode { Pencil, Line, Square, Circle, Eraser }; // Define the Draw and Erase enum values

    void selectTool(Mode mode);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:

    void resizeImage(QPixmap *image, const QSize &newSize);

    QPoint lastPoint;
    QPixmap image;
    bool drawing;
    Mode mode; // Add the mode member
    QColor color; // Add the color member
};