![foreman_logo](https://raw.github.com/cybergarage/foreman-doc/master/img/icon.png)

# Building and Testing

`foreman-cc` is a core package of Foreman which is written by C++. To build Foreman, you have to install the library, `libforeman++`, at first.

## System Requirement

The `foreman-cc` uses the following package. Please install the packages in your platform before compiling `foreman-cc`.

| Library | Requirements version | Mandatory |
|---|---|---|
| [SQLite](https://www.sqlite.org)  | >= 3.16.0  | O |
| [libuuid](http://www.ossp.org/pkg/lib/uuid/)  | >= 1.6.2 | O |
| [Folly](https://www.sqlite.org)  | >= 2017.08.21.00  | X (--enable-beringei) |
| [ALGLIB](http://www.alglib.net)  | >= 3.9.0  | X (--enable-alglib) |
| [Boost](http://www.boost.org/)  | >= 1.65.0  | X (--enable-test) |
| [google-benchmark](https://github.com/google/benchmark)  | >= 1.2.0  | X ( --enable-benchmark) |

528  brew tap  brewsci/science
529  brew install alglib

## Directory Structure

The `foreman-cc` package has the header files, the source files and the project files to build the library, `libforeman++`. The files are included in the following directories separatedly.

| Type | Directory  | Description |
|---|---|---|
| Header  | include  | Public include header files  |
| Source  | src  | Source code and internal header files  |
| Project  | lib  | Project files for major platforms such as Unix and MacOSX |
| Unit Test  | test  |  Unit tests using [Boost](http://www.boost.org) test library |
| Benchmark Test  | bin  |  Benchmark tests using [google-benchmark](https://github.com/google/benchmark) |

## Esay Installation

## MacOSX

### Homebrew

Using [Homebrew](https://brew.sh/), you can install `foreman-cc` easily. To install `foreman-cc`, use `brew` command as the following.

```
./setup_macosx 
brew tap brewsci/science
brew install alglib

brew install ossp-uuid

brew tap cybergarage/homebrew https://github.com/cybergarage/homebrew
brew install foreman-cc
```

Please check the following site if you want to know about the our original site for [Homebrew](https://brew.sh/) in more detail.

- [nosql/homebrew](https://github.com/cybergarage/homebrew)

## Building from Source

## Linux

To build on Linux platform, use `configure` as the following.

```
git clone https://github.com/cybergarage/foreman-cc.git
cd foreman-cc/
./configure_linux
make -j 10
make install
```

### Ubuntu

To build on Ubuntu, use `configure_ubuntu` instead of `configure` as the following.

```
....
./configure_ubuntu
....
```

## MacOSX

To build [foreman-cc](https://github.com/cybergarage/foreman-cc), you have to install latest [XCode](https://developer.apple.com/xcode/) from AppStore and the following commands using [Homebrew](https://brew.sh).

```
./setup_macosx 
```

To build on MacOSX, use `configure_macosx` instead of `configure` as the following.

```
./boostrap
./configure_macosx
make -j 10
make install
```

#### XCode

For XCode, the following projects are avairable for building and testing the library.

| Project | Path | Description |
|---|---|---|
| Library  | lib/macosx/xcode/libforeman++.xcodeproj  | Project for libforeman++ |
| Unit Test  |test/macosx/xcode/foremantest.xcodeproj  |  |
