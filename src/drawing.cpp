// drawing.cpp
#include "drawing.h"

Drawing::Drawing(int width, int height) : width(width), height(height) {
    canvas.resize(height, std::vector<char>(width, ' '));
}

void Drawing::draw() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << canvas[i][j];
        }
        std::cout << '\n';
    }
}

void Drawing::drawShape(int x, int y, char shape) {
    // Check if the given coordinates are within the canvas boundaries
    if (x >= 0 && x < width && y >= 0 && y < height) {
        // Modify the canvas at the specified coordinates with the given shape
        canvas[y][x] = shape;

        // Push the current state onto the undo stack
        undoStack.push_back(canvas);
    } else {
        std::cout << "Invalid coordinates for drawing shape.\n";
    }
}

void Drawing::drawRectangle(int x, int y, int width, int height, char border) {
    // Implement drawing rectangles
    // ...
}

void Drawing::drawCircle(int x, int y, int radius, char border) {
    // Implement drawing circles
    // ...
}

void Drawing::drawLine(int x1, int y1, int x2, int y2, char border) {
    // Implement drawing lines
    // ...
}

void Drawing::undo() {
    if (!undoStack.empty()) {
        // Pop the last state from the undo stack
        redoStack.push_back(canvas);
        canvas = undoStack.back();
        undoStack.pop_back();
    }
}

void Drawing::redo() {
    if (!redoStack.empty()) {
        // Pop the last state from the redo stack
        undoStack.push_back(canvas);
        canvas = redoStack.back();
        redoStack.pop_back();
    }
}
