#include "paintingarea.h"

PaintingArea::PaintingArea(QWidget *parent) : QWidget(parent), drawing(false) {
    this->resize(parent->size()); // Resize the widget to the size of the parent
    image = QPixmap(size()); // Create a QPixmap the same size as the widget
    image.fill(Qt::white); // Fill the QPixmap with white
}

void PaintingArea::resizeEvent(QResizeEvent *event) {
    // If the widget is resized to be larger than the image, resize the image to match the new size
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void PaintingArea::resizeImage(QPixmap *image, const QSize &newSize) {
    // If the image is already the correct size, do nothing
    if (image->size() == newSize)
        return;

    // Create a new QPixmap with the new size and fill it with white
    QPixmap newImage(newSize);
    newImage.fill(Qt::white);
    QPainter painter(&newImage);
    painter.drawPixmap(QPoint(0, 0), *image);
    *image = newImage;
}

void PaintingArea::mousePressEvent(QMouseEvent *event) {
    // If the left mouse button is pressed, start drawing
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawing = true;
    }
}

void PaintingArea::mouseMoveEvent(QMouseEvent *event) {
    // If the left mouse button is pressed and drawing has started, draw a line from the last point to the current point
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        QPainter painter(&image);
        painter.setPen(color); // Set the color of the pen
        painter.drawLine(lastPoint, event->pos());
        lastPoint = event->pos();
        update();
    }
}

void PaintingArea::mouseReleaseEvent(QMouseEvent *event) {
    // If the left mouse button is released, stop drawing
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
    }
}

void PaintingArea::selectTool(Mode tool) {
    mode = tool;
    if (tool == Eraser) {
        color = Qt::white;
    } else {
        color = Qt::black;
    }
}

void PaintingArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // // Draw a circle at (50, 50) with radius 30
    // painter.drawEllipse(50, 50, 30, 30);

    // // Draw a square at (100, 50) with side length 30
    // painter.drawRect(100, 50, 30, 30);

    // // Draw a line from (50, 100) to (100, 150)
    // painter.drawLine(50, 100, 100, 150);

    painter.drawPixmap(0, 0, image);
}