# C++ Scientific Calculator

An interview-ready Qt desktop app that showcases modern C++17, signal/slot driven UI design, and clean separation between presentation and business logic. The project demonstrates my ability to ship polished developer tooling: a calculator that supports compound expressions, keyboard-driven history browsing, and error-safe evaluation.

## Why this project stands out

- **Deliberate UX polish.** Results are automatically remembered, and the input field supports `↑`/`↓` history navigation so power users can iterate on calculations without touching the mouse.
- **Robust expression parsing.** Token-based parsing handles whitespace-tolerant addition, subtraction, multiplication, and division while guarding against division-by-zero edge cases.
- **Qt best practices.** The UI is authored in Qt Designer (`calculator.ui`), wired up through `QMainWindow` subclasses, and leverages signal-slot connections for input events and button presses.
- **Scalable architecture.** Computational logic lives in `Calculator::getInputs()` and can be unit-tested or extended (for example, to support scientific functions) without UI churn. The class also exposes a lightweight `add` helper for reuse.

## Tech stack

| Layer | Technologies |
| --- | --- |
| Language | Modern C++17 |
| UI toolkit | Qt 5/6 Widgets, Qt Designer `.ui` forms |
| Build system | CMake with `AUTOUIC`, `AUTOMOC`, and `AUTORCC` enabled |

## Project structure

```
CPP-Scientific-Calculator/
├── CMakeLists.txt          # Cross-platform build configuration
├── calculator.h/.cpp       # QMainWindow subclass implementing calculator logic
├── calculator.ui           # Designer-authored interface definition
└── main.cpp                # QApplication bootstrap
```

## Getting started

1. **Install dependencies.**
   - Qt 5.15+ (or Qt 6) with Widgets module
   - CMake ≥ 3.16
   - A C++17-capable compiler (MSVC, Clang, or GCC)
2. **Configure the build.**
   ```bash
   cmake -S . -B build -DCMAKE_PREFIX_PATH=/path/to/Qt
   ```
   Set `CMAKE_PREFIX_PATH` to your Qt installation root (e.g., `~/Qt/6.5.0/gcc_64`).
3. **Compile and run.**
   ```bash
   cmake --build build
   ./build/CPP-Scientific-Calculator
   ```

## Feature tour

- **Expression entry.** Enter expressions such as `12 ÷ 4 + 3 × 5` using the on-screen keypad or the keyboard; the app automatically inserts spacing around operators for reliable parsing.
- **Keyboard shortcuts.** Press `Enter` to evaluate, `↑`/`↓` to cycle through past results, and the UI keeps the latest result selected for immediate editing.
- **Defensive math.** Division by zero is trapped and surfaced via stderr, illustrating error-handling discipline.

## Extensibility roadmap

- Support advanced scientific operations (trigonometric functions, powers, parentheses) by expanding the tokenizer.
- Persist history across sessions using Qt's `QSettings` or a lightweight SQLite store.
- Add automated tests with Qt Test to showcase TDD and CI/CD readiness.

## Recruiter takeaways

- Demonstrates fluency in Qt's widget stack, signal/slot architecture, and event filters.
- Highlights attention to UX detail and error handling in a desktop environment.
- Provides a solid foundation for discussing cross-platform desktop development, modern C++ patterns, and future enhancements.
