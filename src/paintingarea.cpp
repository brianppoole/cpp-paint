#include "paintingarea.h"

/**
 * @brief Constructs a new PaintingArea object.
 *
 * This function is called to construct a new PaintingArea object.
 * It resizes the widget to the size of the parent and creates a QPixmap the same size as the widget, filling it with white.
 *
 * @param parent The parent widget.
 */
PaintingArea::PaintingArea(QWidget *parent) : QWidget(parent), drawing(false), tool(Pencil)
{
    this->resize(parent->size()); // Resize the widget to the size of the parent
    image = QPixmap(size());      // Create a QPixmap the same size as the widget
    image.fill(Qt::white);        // Fill the QPixmap with white
}

/**
 * @brief Handles the paint event for the painting area.
 *
 * This function is called when the widget needs to be repainted.
 * It draws the image on the widget.
 *
 * @param event The paint event object containing information about the event.
 */
void PaintingArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (drawing && tool != Pencil && tool != Eraser)
    {
        painter.drawPixmap(0, 0, tempImage);
    }
    else
    {
        painter.drawPixmap(0, 0, image);
    }
}

/**
 * @brief Handles the resize event for the painting area.
 *
 * This function is called when the widget is resized.
 * If the widget is resized to be larger than the image, it resizes the image to match the new size.
 *
 * @param event The resize event object containing information about the event.
 */
void PaintingArea::resizeEvent(QResizeEvent *event)
{
    // If the widget is resized to be larger than the image, resize the image to match the new size
    if (width() > image.width() || height() > image.height())
    {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

/**
 * @brief Resizes the image to the specified size.
 *
 * This function is called to resize the image to the specified size.
 *
 * @param image The image to resize.
 * @param newSize The new size to resize the image to.
 *
 * @see resizeEvent
 * @see PaintingArea
 * @see QPainter
 */
void PaintingArea::resizeImage(QPixmap *image, const QSize &newSize)
{
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

/**
 * @brief Handles the mouse press event for the painting area.
 *
 * This function is called when the mouse is pressed over the painting area.
 * If the left mouse button is pressed, it starts drawing and saves the current image to the undo stack.
 *
 * @param event The mouse event object containing information about the event.
 */
void PaintingArea::mousePressEvent(QMouseEvent *event)
{
    // If the left mouse button is pressed, start drawing
    if (event->button() == Qt::LeftButton)
    {
        lastPoint = event->pos();
        drawing = true;
        tempImage = image; // Copy the image to the temporary image

        undoStack.push(image); // Push the current image onto the stack
        redoStack.clear();     // Clear the redo stack
    }
}

/**
 * @brief Handles the mouse move event for the painting area.
 *
 * This function is called when the mouse is moved over the painting area.
 * If the left mouse button is pressed and the tool is Pencil, it draws a line from the last point to the current point.
 * If the tool is not Pencil, it draws the corresponding shape on the temporary image.
 *
 * @param event The mouse event object containing information about the event.
 */
void PaintingArea::mouseMoveEvent(QMouseEvent *event)
{
    // If the left mouse button is pressed and the tool is Pencil, draw a line from the last point to the current point
    if ((event->buttons() & Qt::LeftButton) && drawing)
    {
        // Create a QPainter object to draw on the image
        QPainter painter(&image);

        // Set the pen style and width
        QPen pen(color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

        if (tool == Pencil || tool == Eraser)
        {
            // Draw a line from the last point to the current point
            if (tool == Eraser)
            {
                pen.setColor(Qt::white);
            }
            painter.setPen(pen);
            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.drawLine(lastPoint, event->pos());
            lastPoint = event->pos();
        }
        else
        {
            // If the tool is not Pencil, draw the shape on the temporary image
            tempImage = image; // Copy the image to the temporary image
            QPainter painter(&tempImage);
            painter.setRenderHint(QPainter::Antialiasing, true);
            switch (tool)
            {
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

/**
 * @brief Handles the mouse release event for the painting area.
 *
 * This function is called when the mouse button is released over the painting area.
 * If the left mouse button is released, it stops drawing.
 * If the tool is not Pencil, it copies the temporary image back to the image.
 *
 * @param event The mouse event object containing information about the event.
 */
void PaintingArea::mouseReleaseEvent(QMouseEvent *event)
{
    // If the left mouse button is released, stop drawing
    if (event->button() == Qt::LeftButton && drawing)
    {
        drawing = false;
    }

    // If the tool is not Pencil, then the shape is complete, so copy the temporary image back to the image
    if (tool != Pencil && tool != Eraser)
    {
        image = tempImage; // Copy the temporary image back to the image
        update();
    }
}

/**
 * @brief Selects the specified tool for drawing.
 *
 * @param newTool The tool to select for drawing.
 */
void PaintingArea::selectTool(Tool newTool)
{
    tool = newTool;
}

/**
 * @brief Sets the color for drawing.
 *
 * @param newColor The color to set for drawing.
 */
void PaintingArea::setPenColor(const QColor &newColor)
{
    color = newColor;
}

/**
 * @brief Undoes the last action.
 */
void PaintingArea::undo()
{
    if (!undoStack.isEmpty())
    {
        redoStack.push(image);   // Push the current image onto the redo stack
        image = undoStack.pop(); // Pop the last image from the stack
        tempImage = image;       // Copy the image to the temporary image
        update();
    }
}

/**
 * @brief Redoes the last undone action.
 */
void PaintingArea::redo()
{
    if (!redoStack.isEmpty())
    {
        undoStack.push(image);   // Push the current image onto the undo stack
        image = redoStack.pop(); // Pop the last image from the stack
        tempImage = image;       // Copy the image to the temporary image
        update();
    }
}

/**
 * @brief Clears the image.
 */
void PaintingArea::clearImage()
{
    // Hmm... should we clear the undo stack and redo stack here? Sort of nice to be able to go back...
    undoStack.push(image); // Push the current image onto the stack
    redoStack.clear();     // Clear the redo stack

    image.fill(Qt::white); // Fill the image with white
    update();
}

/**
 * @brief Loads an image from a file.
 *
 * @param fileName The name of the file to load the image from.
 */
void PaintingArea::loadImage(const QString &fileName)
{
    image = QPixmap(fileName); // Load the image from the file
    tempImage = image;         // Copy the image to the temporary image
    update();
}

/**
 * @brief Saves the image to a file.
 *
 * @param fileName The name of the file to save the image to.
 * @param fileFormat The format of the file to save the image to.
 */
void PaintingArea::saveImage(const QString &fileName, const char *fileFormat)
{
    image.save(fileName, fileFormat);
}

/**
 * @brief Creates a star polygon.
 *
 * @param center The center point of the star.
 * @param outer The outer point of the star.
 * @param points The number of points on the star.
 * @param ratio The ratio of the inner radius to the outer radius.
 * @return The star polygon.
 */
QPolygonF PaintingArea::starPolygon(QPointF center, QPointF outer, int points, double ratio)
{
    QPolygonF polygon;
    double angleStep = 2 * M_PI / points;
    double outerRadius = QLineF(center, outer).length();
    double innerRadius = outerRadius * ratio;
    for (int i = 0; i < points; ++i)
    {
        double angle = i * angleStep;
        polygon << center + QPointF(cos(angle), sin(angle)) * outerRadius;
        angle += angleStep / 2;
        polygon << center + QPointF(cos(angle), sin(angle)) * innerRadius;
    }
    return polygon;
}