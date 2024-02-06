#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>
#include <QStack>

class PaintingArea : public QWidget {
    Q_OBJECT

public:
    PaintingArea(QWidget *parent = nullptr);
    
    enum Tool { Pencil, Line, Rectangle, Ellipse, Star, Eraser }; // Define the Draw and Erase enum values

    Tool getSelectedTool() const { return tool; }
    QColor getColor() const { return color; }

    void selectTool(Tool tool);
    void setColor(const QColor &newColor);
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

    void resizeImage(QPixmap *image, const QSize &newSize);

    QPoint lastPoint;
    QPixmap image;
    QPixmap tempImage;
    bool drawing;
    Tool tool;
    QColor color;
    QStack<QPixmap> undoStack;
    QStack<QPixmap> redoStack;

    
    QPolygonF starPolygon(QPointF center, QPointF outer, int points, double ratio) {
        QPolygonF polygon;
        double angleStep = 2 * M_PI / points;
        double outerRadius = QLineF(center, outer).length();
        double innerRadius = outerRadius * ratio;
        for (int i = 0; i < points; ++i) {
            double angle = i * angleStep;
            polygon << center + QPointF(cos(angle), sin(angle)) * outerRadius;
            angle += angleStep / 2;
            polygon << center + QPointF(cos(angle), sin(angle)) * innerRadius;
        }
        return polygon;
    }
};