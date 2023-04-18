# FastString - 快速的固定长度字符串存储类
FastString 是一个使用 C++ 编写的开源项目，旨在提供一种快速的固定长度字符串存储类，通过使用 AVX2 指令集进行比较以及缓存行对齐的设计来优化性能。FastString 支持最大长度为 64 字节的字符串，并提供了简单的构造函数和比较运算符，以便于在性能敏感的场景中使用。

## 特性
* 支持固定长度的字符串存储，最大长度为 64 字节。
* 使用 AVX2 指令集进行比较，提高比较性能。
* 缓存行对齐的设计，进一步优化性能。
* 使用零拷贝方式构造对象，减少复杂度和执行时间。

## 使用案例
以下是 FastString 类的简单使用案例：
```c++
#include "fast_string.hpp"

int main() {
    // 构造 FastString 对象
    const char* str1 = "hello";
    const char* str2 = "world";
    FastString<5> fs1(str1); // 最大长度为 5 的 FastString 对象
    FastString<5> fs2(str2); // 最大长度为 5 的 FastString 对象

    // 比较 FastString 对象
    if (fs1 == fs2) {
        std::cout << "fs1 equals fs2" << std::endl;
    } else {
        std::cout << "fs1 does not equal fs2" << std::endl;
    }

    return 0;
}
```
在上面的示例中，首先通过构造函数创建了两个 FastString 对象 fs1 和 fs2，分别存储了 "hello" 和 "world" 这两个字符串。然后使用比较运算符 == 进行了对象的比较，并根据比较结果输出相应的信息。
## 编译和安装
FastString 是一个头文件库，无需编译和安装，可以直接将 fast_string.hpp 文件包含到您的项目中使用。
## 贡献
欢迎对 FastString 提出改进和贡献代码。您可以通过提交 Issues、Pull Requests 或者与我们联系来参与贡献。
## 许可证
FastString 采用 MIT 许可证，详情请参见 LICENSE 文件。
## 感谢
本程序部分使用ChatGPT，感谢OpenAI团队
