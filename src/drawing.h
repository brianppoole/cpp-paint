// drawing.h
#ifndef DRAWING_H
#define DRAWING_H

#include <iostream>
#include <vector>

class Drawing {
public:
    Drawing(int width, int height);

    void draw();
    void drawShape(int x, int y, char shape);
    void drawRectangle(int x, int y, int width, int height, char border);
    void drawCircle(int x, int y, int radius, char border);
    void drawLine(int x1, int y1, int x2, int y2, char border);

    void undo();
    void redo();

private:
    int width;
    int height;
    std::vector<std::vector<char>> canvas;

    // Undo and redo stacks
    std::vector<std::vector<std::vector<char>>> undoStack;
    std::vector<std::vector<std::vector<char>>> redoStack;
};

#endif // DRAWING_H
