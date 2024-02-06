#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>
#include <QStack>

class PaintingArea : public QWidget {
    Q_OBJECT

public:
    PaintingArea(QWidget *parent = nullptr);
    
    enum Tool { Pencil, Line, Rectangle, Ellipse, Star, Eraser }; // enum for the different tools

    Tool getSelectedTool() const { return tool; }
    QColor getColor() const { return color; }

    void selectTool(Tool tool);
    void setPenColor(const QColor &newColor);
    void undo();
    void redo();
    void clearImage();
    void loadImage(const QString &fileName);
    void saveImage(const QString &fileName, const char *fileFormat);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPoint lastPoint;
    QPixmap image;
    QPixmap tempImage;
    bool drawing;
    Tool tool;
    QColor color;
    QStack<QPixmap> undoStack;
    QStack<QPixmap> redoStack;

    void resizeImage(QPixmap *image, const QSize &newSize);
    QPolygonF starPolygon(QPointF center, QPointF outer, int points, double ratio);
};