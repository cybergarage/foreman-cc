![foreman_logo](https://raw.github.com/cybergarage/foreman-doc/master/img/icon.png)

# Coding Guidelines

## Supported Compilers and Platforms

The `foreman-cc` supports the following compilers and platforms now.

| Platform | Compiler | Requirement |
|---|---|---|
| Ubuntu 16.04 | GCC 5.4.0 | Must |
| MacOSX 10.12 | LLVM 9.0.0 (XCode 9.0) |  Must |
| CentOS 7.3.0 | GCC 4.8.5 | Should |
| CentOS 6.8.0 | GCC 4.4.7 | Should |

## Coding Guidelines

To develop `foreman-cc`, you must follow understand the following coding guidelines basically.

- [WebKit Code Style Guidelines](https://webkit.org/code-style-guidelines/)

## Extra Coding Guidelines

### Comply to C++ 11 specification

Basically, comply to C++ 11 specifications which are supported by GCC and Clang as the following.

- [C++ compiler support](http://en.cppreference.com/w/cpp/compiler_support)

### Prefer auto to explicit type declarations

Unless required for explicit type declarations, use `auto` to declare any variables proactively for simplicity and refactoring purpose.

#### Right

```
std::vector<int> vec;
....
auto var = vec.at(0);
```

#### Wrong

```
std::vector<int> vec;
....
int var = vec.at(0);
```

### Formatter

We extends the standard guideline, and the all source codes of `foreman-cc` are formatted automatically by `clang-format` based on the following setting.

- [.clang-format](https://github.com/cybergarage/foreman-cc/blob/master/.clang-format)
