# CGoggles

[![Code Style](https://img.shields.io/badge/code_style-VS_Code-blue.svg?style=flat)](https://google.github.io/styleguide/cppguide.html)
[![Versioning](https://img.shields.io/badge/versioning-semantic-brightgreen.svg?style=flat)](https://semver.org/)
[![Commit Style](https://img.shields.io/badge/commit_style-gitmoji-yellow.svg?style=flat)](https://gitmoji.carloscuesta.me/)
![Top Language](https://img.shields.io/github/languages/top/evaneliasyoung/cgoggles.svg?style=flat)
![Code Size](https://img.shields.io/github/languages/code-size/evaneliasyoung/cgoggles.svg?style=flat)
[![Issues](https://img.shields.io/github/issues/evaneliasyoung/cgoggles.svg?style=flat)](https://github.com/evaneliasyoung/cgoggles/issues)
[![Last Commit](https://img.shields.io/github/last-commit/evaneliasyoung/cgoggles.svg?style=flat)](https://github.com/evaneliasyoung/cgoggles/commit/master)

The ultimate cross-platform System information CLI tool.
Written in C++ to allow for speed-compile times and speed-operation times.
This is made as first a passion-project and next a final-project for my programming class.

## News and Changes

### Version 0.1.0 - 2019-03-25

### Latest Activity

(last 7 major and minor version releases)

- Version 0.1.0: Initial release

You can find all changes here: [detailed changelog](CHANGELOG.md)

## Reference

### 1. OS

| Call             | Linux | Mac | Win | Comments                             |
| ---------------- | ----- | --- | --- | ------------------------------------ |
| os               |   ~   |  X  |  X  | *Everything below*                   |
| os.All           |   ~   |  X  |  X  | *Everything below*                   |
| os.Platform      |   X   |  X  |  x  | Windows                              |
| os.Caption       |       |  X  |  x  | Microsoft Windows 10 Pro             |
| os.Serial        |       |  X  |  x  | 00000-00000-00000-XXXXX              |
| os.Bit           |       |  X  |  x  | 64                                   |
| os.InstallTime   |       |  X  |  x  | 2018-12-04T04:41:06                  |
| os.BootTime      |       |  X  |  x  | 2019-03-22T18:03:37                  |
| os.CurTime       |       |  X  |  x  | 2019-03-25T17:49:18                  |
| os.Kernel        |       |  X  |  x  | 10.0.0                               |
| os.Version       |       |  X  |  x  | 10.0.0                               |

### 2. CPU

| Call             | Linux | Mac | Win | Comments                             |
| ---------------- | ----- | --- | --- | ------------------------------------ |
| cpu              |       |     |  X  | *Everything below*                   |
| cpu.All          |       |     |  X  | *Everything below*                   |
| cpu.Manufacturer |       |     |  X  | AuthenticAMD                         |
| cpu.Architecture |       |     |  X  | x64                                  |
| cpu.SocketType   |       |     |  X  | AM4                                  |
| cpu.Brand        |       |     |  X  | AMD Ryzen 5 1600x Six-Core Processor |
| cpu.Family       |       |     |  X  | 23                                   |
| cpu.Model        |       |     |  X  | 1                                    |
| cpu.Stepping     |       |     |  X  | 1                                    |
| cpu.Cores        |       |     |  X  | 6                                    |
| cpu.Threads      |       |     |  X  | 12                                   |
| cpu.Speed        |       |     |  X  | 3620 GHz                             |
| cpu.MaxSpeed     |       |     |  X  | 3620 GHz                             |
