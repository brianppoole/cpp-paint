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
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        // Create a QPainter object to draw on the image
        QPainter painter(&image);

        // Set the pen style and width
        QPen pen(color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

        if (tool == Pencil || tool == Eraser) {
            // Draw a line from the last point to the current point
            if (tool == Eraser) {
                pen.setColor(Qt::white);
            }
            painter.setPen(pen);
            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.drawLine(lastPoint, event->pos());
            lastPoint = event->pos();
        } else {
            // If the tool is not Pencil, draw the shape on the temporary image
            tempImage = image; // Copy the image to the temporary image
            QPainter painter(&tempImage);
            painter.setRenderHint(QPainter::Antialiasing, true);
            switch (tool) {
                case Line:
                    painter.setPen(pen);
                    painter.drawLine(lastPoint, event->pos());
                    break;
                case Rectangle:
                    painter.setPen(pen);
                    painter.drawRect(QRect(lastPoint, event->pos()));
                    break;
                case Ellipse:
                    painter.setPen(pen);
                    painter.drawEllipse(QRect(lastPoint, event->pos()));
                    break;
                case Star:
                    painter.setPen(pen);
                    painter.drawPolygon(starPolygon(lastPoint, event->pos(), 5, 0.5));
                    break;
                default:
                    break;
            }
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
        image = tempImage; // Copy the temporary image back to the image
        update();
    }
}

void PaintingArea::selectTool(Tool newTool) {
    tool = newTool;
}

void PaintingArea::setColor(const QColor &newColor) {
    color = newColor;
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
    // Hmm... should we clear the undo stack and redo stack here? Sort of nice to be able to go back...
    undoStack.push(image); // Push the current image onto the stack
    redoStack.clear(); // Clear the redo stack

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

    // Log to the console

    QRect dirtyRect = event->rect();
    if (drawing && tool != Pencil && tool != Eraser) {
        painter.drawPixmap(0, 0, tempImage);
    } else {
        painter.drawPixmap(0, 0, image);
    }
}