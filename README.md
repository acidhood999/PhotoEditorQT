# PhotoEditorQT

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)

PhotoEditorQT is a high performance graphics editor based on C++ and the Qt 6 framework. The project focuses on efficient image processing using low level pixel manipulation techniques.

---

## Possibilities
* Project Gallery: An interactive image list with automatic metadata reading (resolution, file size) and thumbnail generation.
* Digital Filters: Custom implementation of sharpness and blur algorithms using convolution matrices.
* Color Correction: Optimized brightness and contrast adjustments.
* Transformation: High-quality image scaling using SmoothTransformation.
* Export: Save processed data in PNG, JPG, and JPEG formats.

## Tech stack and capabilities

The project is built on the principles of modularity (Separation of Concerns), which separates the interface and computational logic

* main.cpp: Initializes QApplication and starts the event loop.
* PhotoEditorQT (Core): The main controller, managing image states (Original, Result, Display) and interface layout.
* Functional (Business Logic): The processing engine, containing mathematical algorithms.
* Bar (UI Controller): The module for managing menus and system dialogs.
* ImageItem (Data Widget): A custom widget for visualizing items in a list.

## Optimization
* Direct Pixel Access: Instead of the slow setPixel(), direct access to the memory buffer is used via scanLine() and reinterpret_cast<QRgb*>
* LUT (Look-Up Table): Applying brightness and contrast filters in constant time 256, which eliminates complex calculations for each individual pixel
* Event Throttling (Debounce): Implemented a QTimer-based delay. Calculations are only started after user input has stabilized, preventing UI freezes when sliders are moving.
* Convolution Matrix: Hand-crafted implementation of the convolution matrix for the Sharpness filter.

## Assembly
* Qt 6.10.1+ (MSVC 2022 x64)
* Visual Studio 2022 with the Qt VS Tools extension
  
## Instructions
1. Clone the repository.
2. Open the project in Visual Studio.
3. Build the project in the Release configuration.
4. Configure Include Paths: Since the headers are located in a separate directory, you need to tell the compiler where to find them:  
   * Right-click on the project in Solution Explorer - Properties  
   * Go to C/C++ - General 
   * In Additional Include Directories, add: `$(ProjectDir)include`
```bash
Bash

windeployqt.exe --release path/to/PhotoEditorQT.exe
```

