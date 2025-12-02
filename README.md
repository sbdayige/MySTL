# MySTL

这是一个简单的 C++ STL 容器实现项目，包含以下自定义容器：

- `MyString`: 自定义字符串类，支持基本的构造、拷贝、移动和拼接操作。
- `MyQueue`: 基于链表实现的队列，支持入队、出队、判空等操作。
- `MyVector`: 动态数组实现的向量，支持自动扩容、线程安全（部分）操作。

## 项目结构

```
.
├── CMakeLists.txt      # CMake 构建配置文件
├── main.cpp            # 测试入口文件
├── MyQueue.hpp         # 队列实现
├── MyString.hpp        # 字符串实现
├── MyVector.hpp        # 向量实现
└── README.md           # 项目说明文档
```

## 编译与运行

本项目使用 CMake 进行构建管理。

### 前置要求

- C++ 编译器 (支持 C++17 标准，如 g++)
- CMake (版本 >= 3.10)

### 构建步骤

1. 创建构建目录：
   ```bash
   mkdir build
   cd build
   ```

2. 生成构建文件：
   ```bash
   cmake ..
   ```

3. 编译项目：
   ```bash
   make
   ```

### 运行测试

编译成功后，在 `build` 目录下运行生成的可执行文件：

```bash
./MySTL
```

## 如何添加新文件

如果你想添加新的类或功能：

1. **头文件 (.hpp)**: 直接在项目根目录下创建 `.hpp` 文件，并在 `main.cpp` 或其他文件中 `#include` 即可。
2. **源文件 (.cpp)**: 如果你创建了新的 `.cpp` 实现文件，需要修改 `CMakeLists.txt`，将其添加到 `add_executable` 命令中：

   ```cmake
   add_executable(MySTL main.cpp NewFile.cpp)
   ```
