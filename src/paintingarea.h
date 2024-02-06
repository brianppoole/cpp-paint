#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>
#include <QStack>

class PaintingArea : public QWidget {
    Q_OBJECT

public:
    PaintingArea(QWidget *parent = nullptr);
    
    enum Tool { Pencil, Line, Rectangle, Ellipse, Eraser }; // Define the Draw and Erase enum values

    Tool getSelectedTool() const { return tool; }

    void selectTool(Tool tool);
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
    Tool tool; // Add the tool member
    QColor color; // Add the color member
    QStack<QPixmap> undoStack; // Add a stack of images for undo
    QStack<QPixmap> redoStack; // Add a stack of images for redo
};