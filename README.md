# SimpleLogger

SimpleLogger is a simple C++ logging library designed for easy integration into your projects. It offers flexibility in logging levels, multiple output streams, thread-safety, and configuration options.

## Install

### Git Submodules

1. Download the library as a submodule:

   ```bash
   git submodule add git@github.com:PlungedInCode/SimpleLogger.git lib
   ```

   or clone the repository directly:

   ```bash
   git clone git@github.com:PlungedInCode/SimpleLogger.git
   ```

2. Integrate it into your CMake project:

   ```cmake
   add_subdirectory(lib/SimpleLogger)
   target_link_libraries(your_project LoggerCPP)
   ```

## Getting Started

Include the header in your C++ file:

```cpp
#include "Logger.hpp"
```

Then, initialize the logger level (by default, it's `kInfo`) and start logging:

```cpp
int main() {
    Logger::SetLogLevel(LogLevel::kDebug);
    LOG_DEBUG("Hello, SimpleLogger!");
    return 0;
}
```

### Levels

SimpleLogger supports the following log levels:

- TRACE
- DEBUG
- INFO
- WARNING
- ERROR

Use these levels to control the verbosity of your logs.

## Usage Samples

### Basic Usage

```cpp
#include "Logger.hpp"

int main() {
    LOG_TRACE("This is a trace message.");
    LOG_DEBUG("This is a debug message.");
    LOG_INFO("This is an info message.");
    LOG_WARNING("This is a warning message.");
    LOG_ERROR("This is an error message.");
    return 0;
}
```

### Time Stamps

Enable time stamps for log entries:

```cpp
Logger::EnableTimeStamp();
LOG_INFO("Log entry with timestamp.");
Logger::DisableTimeStamp();
```

### File Stamp

Enable file stamps (file and line number) for log entries:

```cpp
Logger::EnableFileStamp();
LOG_INFO("Log entry with line stamp.");
Logger::DisableFileStamp();
```

### File/Console Logging

There are three types of logging(by default, type is `kConsole` ):
- File
- Console
- Both
```cpp
Logger::SetStream(OutputStream::kBoth);
Logger::SetLogFile("MyLogs.txt");
LOG_INFO("Log entry to file.");
```
## Contribution

Feel free to contribute to SimpleLogger by submitting issues or pull requests.

### TODO

- [ ] Log Formatting `Logger::SetLogFormat("[{timestamp}] [{level}] {message}");`
- [ ] Log Rotation
- [ ] Stream Logging
- [ ] Contextual Logging
- [ ] Time Controller for Debugging
- [ ] Log Tagging
- [ ] Conditional Logging
- [ ] Asynchronous Logging
