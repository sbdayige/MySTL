# MySTL

这是一个简单的 C++ STL 容器实现项目，包含以下自定义容器：

- `MyString`: 自定义字符串类，支持基本的构造、拷贝、移动和拼接操作。
- `MyQueue`: 基于链表实现的队列，支持入队、出队、判空等操作。
- `MyVector`: 动态数组实现的向量，支持自动扩容、线程安全（部分）操作。

# MySTL

这是一个用于练习与教学的轻量级 C++ 容器实现仓库，包含自定义的 `MyString`、`MyQueue`、`MyVector` 等实现，源码以头文件（`.hpp`）形式放在 `h/` 目录，测试入口在 `main.cpp`。

主要目标：
- 学习容器实现的内存管理、拷贝/移动语义、迭代与容量管理等核心概念；
- 提供一个小型可编译、可测试的示例工程，便于在本地或 IDE 中调试与观察行为。

## 当前项目结构

```
.                                   # 工作区根
├── CMakeLists.txt                  # CMake 构建脚本（已配置 compile_commands）
├── main.cpp                        # 程序入口与单文件测试
├── h/                              # 所有头文件统一放到 h/ 下
│   ├── MyQueue.hpp
│   ├── MyString.hpp
│   └── MyVector.hpp
├── .vscode/                         # 可选：VS Code 配置（intellisense 配置已提供）
├── build/                          # 构建目录（建议加入 .gitignore）
└── README.md
```

## 构建与运行

要求：已安装支持 C++17 的编译器（如 `g++`）和 CMake（>= 3.10）。

推荐的构建步骤（在项目根目录下）：

```bash
mkdir -p build
cd build
# 使用项目自带的 CMakeLists.txt（它已开启 CMAKE_EXPORT_COMPILE_COMMANDS）
cmake ..
make
# 运行测试程序
./MySTL
```

说明：CMakeLists 已创建一个 `header_checks` 的 OBJECT 库，用于让 CMake 在 `compile_commands.json` 中包含 `h/` 下的头文件，从而让 VS Code/IntelliSense 能以同样的编译参数分析头文件（更准确地显示头文件内的编译错误）。该 OBJECT 库不参与最终链接，因此不会影响可执行文件。

## 在 IDE（例如 VS Code）中得到头文件错误提示

1. 确保在 `build/` 目录中存在 `compile_commands.json`（CMake 会根据 `CMAKE_EXPORT_COMPILE_COMMANDS` 生成）。
2. 在 `.vscode/c_cpp_properties.json` 中设置 `"compileCommands"` 指向 `${workspaceFolder}/build/compile_commands.json`。
3. 如果使用 VS Code，请重载窗口或重置 IntelliSense 数据库：`Developer: Reload Window` / `C/C++: Reset IntelliSense Database`。

这样可以使编辑器在打开 `h/*.hpp` 时也能正确地显示编译错误（与直接编译时一致）。

## 如何添加新头文件或源文件

- 添加头文件到 `h/`：
  1. 把 `YourType.hpp` 放到 `h/` 目录；
  2. 在 `CMakeLists.txt` 的 `add_library(header_checks OBJECT ...)` 中加入 `h/YourType.hpp`，以便生成对应的 `compile_commands` 条目；
  3. 在 `main.cpp` 中 `#include "h/YourType.hpp"` 或把包含路径改为 `#include "YourType.hpp"`（CMake 已将 `h/` 加入 include path）。

- 如果新增 `.cpp` 源文件（实现分离）：
  1. 新建 `src/YourType.cpp` 或在根目录添加 `.cpp` 文件；
  2. 在 `CMakeLists.txt` 的 `add_executable(MySTL ...)` 中把新 `.cpp` 文件加入（例如 `add_executable(MySTL main.cpp src/YourType.cpp)`）；
  3. 重新运行 `cmake ..` 与 `make`。

> 可选：若不想每次手动编辑 CMakeLists，你可以使用 `file(GLOB ...)` 或 `aux_source_directory()` 来自动收集源文件，但这在大型项目中不推荐用于增量构建的精确控制。

## 代码风格与静态检查（可选）

仓库中保留了为方便实验的最小工具链配置。如果需要，可在 CMake 中集成 `clang-tidy`、`cppcheck` 或 `clang-format` 来做静态检查与格式化。

## 常见问题

- 为什么头文件中的错误在 IDE 中不显示？
  - 可能原因：缺少 `compile_commands.json`、IDE 没配置 `compileCommands` 路径、或 CMake 没为头文件生成条目。请按照上述步骤检查 `build/compile_commands.json` 是否包含 `h/*.hpp` 的条目。

## 联系与改进

如果你希望我帮你把 `CMakeLists.txt` 改为自动包含 `h/` 下所有头文件或将实现改为分离的 `.cpp`/`.hpp` 结构，我可以直接修改并演示完整的构建流程。

---

（本 README 根据当前仓库结构生成，路径与命令以项目根目录为基准）
