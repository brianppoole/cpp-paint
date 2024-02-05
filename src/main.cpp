// main.cpp
#include "drawing.h"

int main() {
    Drawing drawing(20, 10);

    drawing.draw(); // Initial empty canvas

    drawing.drawShape(5, 3, '*');
    drawing.drawRectangle(2, 2, 8, 5, '#');
    drawing.drawCircle(15, 7, 3, 'O');
    drawing.drawLine(1, 1, 18, 8, '=');

    drawing.draw(); // Updated canvas

    drawing.undo(); // Undo the last operation

    drawing.draw(); // Canvas after undo

    drawing.redo(); // Redo the undone operation

    drawing.draw(); // Canvas after redo

    return 0;
}
