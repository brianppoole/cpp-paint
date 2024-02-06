# Brian's C++ Painting App

This is a painting application developed by Brian Poole. It's written in C++ and provides a simple and intuitive interface for creating digital art.

## Building the Application

To build the application:

```bash
mkdir build
cd build
cmake ..
```

(On some systems, you may need to specify the path to the Qt installation directory using the `CMAKE_PREFIX_PATH` option. For example, on Windows, you might use `-DCMAKE_PREFIX_PATH=C:\Qt\6.6.1\mingw_64\lib\cmake`.)
```bash
cmake -DCMAKE_PREFIX_PATH=C:\Qt\6.6.1\mingw_64\lib\cmake ..
```

```bash
cmake --build . --config Release
```

## Running the Application

After building the application, you can run it using the following command:
```bash
./cpp-paint
```

Contact
Brian Poole - brian.p.poole@gmail.com

Project Link: https://github.com/brianppoole/cpp-paint