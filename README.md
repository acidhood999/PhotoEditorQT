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
