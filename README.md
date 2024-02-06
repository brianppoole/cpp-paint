# Brian's C++ Painting App

[![cpp-paint-demo3.gif](https://i.postimg.cc/mgV8fDxZ/cpp-paint-demo3.gif)](https://postimg.cc/HrcQbTsF)

This is a painting application developed by Brian Poole. It's written in C++ and provides a simple and intuitive interface for creating digital art.

## Features

* **Drawing Tools**: The application provides various drawing tools like Pencil, Eraser, and the ability to draw basic shapes like circles, rectangles, and lines.
* **Color Selection**: Users can choose from a wide range of colors for their drawings.
* **Undo/Redo Functionality**: The application supports undo and redo operations, allowing users to easily correct mistakes or make changes.
* **Simple User Interface**: The application has a user-friendly interface that is easy to navigate and use.
* **Save/Load Functionality**: Users can save their current drawing and load it later.
* **Persistent Tool Selection**: The application remembers the user's tool selection between application loads.
* **Resizable Canvas**: The painting area automatically resizes to match the size of the window.

## Requirements

Before you proceed, ensure that you meet the following requirements:

* You have installed the latest version of [Qt6](https://www.qt.io/download-qt-installer).
* You have installed the latest version of [CMake](https://cmake.org/download/).
* You have a Windows/Linux/Mac machine.

## Building the Application

To build the application:

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

(On some systems, you may need to specify the path to the Qt installation directory using the `CMAKE_PREFIX_PATH` option. For example, on Windows, you might use `-DCMAKE_PREFIX_PATH=C:\Qt\6.6.1\mingw_64\lib\cmake`.)
```bash
cmake -DCMAKE_PREFIX_PATH=C:\Qt\6.6.1\mingw_64\lib\cmake ..
```

## Running the Application

After building the application, you can run it using the following command:
```bash
./cpp-paint
```

Contact
Brian Poole - coding@bripi.com

Project Link: https://github.com/brianppoole/cpp-paint
