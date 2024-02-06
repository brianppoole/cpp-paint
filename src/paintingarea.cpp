#include "paintingarea.h"

PaintingArea::PaintingArea(QWidget *parent) : QWidget(parent), drawing(false), tool(Pencil) {
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
        tempImage = image; // Copy the image to the temporary image

        undoStack.push(image); // Push the current image onto the stack
        redoStack.clear(); // Clear the redo stack
    }
}

void PaintingArea::mouseMoveEvent(QMouseEvent *event) {
    // If the left mouse button is pressed and the tool is Pencil, draw a line from the last point to the current point
    if ((event->buttons() & Qt::LeftButton) && drawing && (tool == Pencil || tool == Eraser)) {
        QPainter painter(&image);
        painter.setPen(color);
        painter.drawLine(lastPoint, event->pos());
        lastPoint = event->pos();
        update();
    }

     // If the tool is not Pencil, draw the shape
    if (tool != Pencil && tool != Eraser) {
        tempImage = image; // Copy the image to the temporary image
        QPainter painter(&tempImage);
        painter.setPen(color);
        switch (tool) {
            case Line:
                painter.drawLine(lastPoint, event->pos());
                break;
            case Rectangle:
                painter.drawRect(QRect(lastPoint, event->pos()));
                break;
            case Ellipse:
                painter.drawEllipse(QRect(lastPoint, event->pos()));
                break;
            default:
                break;
        }
        update();
    }
}

void PaintingArea::mouseReleaseEvent(QMouseEvent *event) {
    // If the left mouse button is released, stop drawing
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
    }

    // If the tool is not Pencil, draw the shape
    if (tool != Pencil && tool != Eraser) {
        QPainter painter(&image);
        painter.setPen(color);
        switch (tool) {
            case Line:
                painter.drawLine(lastPoint, event->pos());
                break;
            case Rectangle:
                painter.drawRect(QRect(lastPoint, event->pos()));
                break;
            case Ellipse:
                painter.drawEllipse(QRect(lastPoint, event->pos()));
                break;
            default:
                break;
        }
        image = tempImage; // Copy the temporary image back to the image
        update();
    }
}

void PaintingArea::selectTool(Tool newTool) {
    tool = newTool;
    if (tool == Eraser) {
        color = Qt::white;
    } else {
        color = Qt::black;
    }
}

void PaintingArea::undo() {
    if (!undoStack.isEmpty()) {
        redoStack.push(image); // Push the current image onto the redo stack
        image = undoStack.pop(); // Pop the last image from the stack
        tempImage = image; // Copy the image to the temporary image
        update();
    }
}

void PaintingArea::redo() {
    if (!redoStack.isEmpty()) {
        undoStack.push(image); // Push the current image onto the undo stack
        image = redoStack.pop(); // Pop the last image from the stack
        tempImage = image; // Copy the image to the temporary image
        update();
    }
}

void PaintingArea::clearImage() {
    image.fill(Qt::white); // Fill the image with white
    update();
}

void PaintingArea::loadImage(const QString &fileName) {
    image = QPixmap(fileName); // Load the image from the file
    tempImage = image; // Copy the image to the temporary image
    update();
}

void PaintingArea::saveImage(const QString &fileName, const char *fileFormat) {
    image.save(fileName, fileFormat);
}

void PaintingArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // // Draw a circle at (50, 50) with radius 30
    // painter.drawEllipse(50, 50, 30, 30);

    // // Draw a square at (100, 50) with side length 30
    // painter.drawRect(100, 50, 30, 30);

    // // Draw a line from (50, 100) to (100, 150)
    // painter.drawLine(50, 100, 100, 150);

    QRect dirtyRect = event->rect();
    if (tool != Pencil && tool != Eraser) {
        painter.drawPixmap(0, 0, tempImage);
    } else {
        painter.drawPixmap(0, 0, image);
    }
}