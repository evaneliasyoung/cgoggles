# CGoggles

[![Code Style](https://img.shields.io/badge/code_style-VS_Code-blue.svg?style=flat)](https://google.github.io/styleguide/cppguide.html)
[![Versioning](https://img.shields.io/badge/versioning-semantic-brightgreen.svg?style=flat)](https://semver.org/)
[![Commit Style](https://img.shields.io/badge/commit_style-gitmoji-yellow.svg?style=flat)](https://gitmoji.carloscuesta.me/)
![Top Language](https://img.shields.io/github/languages/top/evaneliasyoung/cgoggles.svg?style=flat)
![Code Size](https://img.shields.io/github/languages/code-size/evaneliasyoung/cgoggles.svg?style=flat)
[![Issues](https://img.shields.io/github/issues/evaneliasyoung/cgoggles.svg?style=flat)](https://github.com/evaneliasyoung/cgoggles/issues)
[![Last Commit](https://img.shields.io/github/last-commit/evaneliasyoung/cgoggles.svg?style=flat)](https://github.com/evaneliasyoung/cgoggles/commit/master)

The ultimate cross-platform System information CLI tool.
Written in C++ to allow for speedy-compile times and speedy-operation times.
This is made as first a passion-project and next a final-project for my programming class.

## News and Changes

### Version 0.3.1 - 2019-04-17

### Latest Activity

(last 7 major and minor version releases)

- Version 0.3.1: Pretty-print option for storage
- Version 0.3.0: System information and Most Linux support
- Version 0.2.0: GPU, Storage, and FileSystem information
- Version 0.1.1: Mac compatability
- Version 0.1.0: Initial release

You can find all changes here: [detailed changelog](CHANGELOG.md)

## Reference

~ Partial Support

X Complete Support

S Sudo Support


### 1. OS

| Call           | Linux | Mac | Win | Comments                 |
| -------------- | ----- | --- | --- | ------------------------ |
| os             | ~     | X   | X   | *Everything below*       |
| os.All         | ~     | X   | X   | *Everything below*       |
| os.Platform    | X     | X   | X   | Windows                  |
| os.Caption     | X     | X   | X   | Microsoft Windows 10 Pro |
| os.Serial      | S     | X   | X   | 00000-00000-00000-XXXXX  |
| os.Bit         | X     | X   | X   | 64                       |
| os.InstallTime | X     | X   | X   | 2018-12-04T04:41:06      |
| os.BootTime    | X     | X   | X   | 2019-03-22T18:03:37      |
| os.CurTime     | X     | X   | X   | 2019-03-25T17:49:18      |
| os.Kernel      | X     | X   | X   | 10.0.0                   |
| os.Version     | X     | X   | X   | 10.0.0                   |

### 2. System
| Call             | Linux | Mac | Win | Comments                             |
| ---------------- | ----- | --- | --- | ------------------------------------ |
| sys              | X     | X   | X   | *Everything below*                   |
| sys.All          | X     | X   | X   | *Everything below*                   |
| sys.Manufacturer | X     | X   | X   | Apple Inc.                           |
| sys.Model        | X     | X   | X   | MacBookPro11,5                       |
| sys.Version      | X     | X   | X   | 1.0                                  |
| sys.Serial       | S     | X   | X   | XXXXXXXXXXXX                         |
| sys.UUID         | S     | X   | X   | XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX |

### 2. CPU

| Call             | Linux | Mac | Win | Comments                             |
| ---------------- | ----- | --- | --- | ------------------------------------ |
| cpu              | X     | X   | X   | *Everything below*                   |
| cpu.All          | X     | X   | X   | *Everything below*                   |
| cpu.Manufacturer | X     | X   | X   | AuthenticAMD                         |
| cpu.Architecture | X     | X   | X   | x64                                  |
| cpu.SocketType   | X     | X   | X   | AM4                                  |
| cpu.Brand        | X     | X   | X   | AMD Ryzen 5 1600x Six-Core Processor |
| cpu.Family       | X     | X   | X   | 23                                   |
| cpu.Model        | X     | X   | X   | 1                                    |
| cpu.Stepping     | X     | X   | X   | 1                                    |
| cpu.Cores        | X     | X   | X   | 6                                    |
| cpu.Threads      | X     | X   | X   | 12                                   |
| cpu.Speed        | X     | X   | X   | 3.620 GHz                            |
| cpu.MaxSpeed     | X     | X   | X   | 3.620 GHz                            |

### 3. GPU

| Call        | Linux | Mac | Win | Comments           |
| ----------- | ----- | --- | --- | ------------------ |
| gpu         |       | X   | X   | *Everything below* |
| gpu.All     |       | X   | X   | *Everything below* |
| gpu.Vendor  |       | X   | X   | Intel              |
| gpu.Model   |       | X   | X   | Intel Iris Pro     |
| gpu.Bus     |       | X   | X   | Built-In           |
| gpu.VRAM    |       | X   | X   | 1536               |
| gpu.Dynamic |       | X   | X   | Yes                |

### 4. RAM

| Call                  | Linux | Mac | Win | Comments           |
| --------------------- | ----- | --- | --- | ------------------ |
| ram                   | S     |  ~  | ~   | *Everything below* |
| ram.All               | S     |  ~  | ~   | *Everything below* |
| ram.Size              | S     |  X  | X   | 8589934592         |
| ram.Bank              | S     |  X  | X   | DIMM1              |
| ram.Type              | S     |  X  | X   | DDR4               |
| ram.Speed             | S     |  X  | X   | 3200 MHz           |
| ram.FormFactor        | S     |     | X   | DIMM               |
| ram.Manufacturer      | S     |  X  | X   | Samsung            |
| ram.Part              | S     |  X  | X   | M378B1G73EB0-YK0   |
| ram.Serial            | S     |  X  | X   | XXXXXXXXXXXX       |
| ram.VoltageConfigured | S     |     | X   | 2.4 V              |
| ram.VoltageMin        | S     |     | X   | 2.4 V              |
| ram.VoltageMax        | S     |     | X   | 2.4 V              |

### 5. Storage

| Call               | Linux | Mac | Win | Comments                             |
| ------------------ | ----- | --- | --- | ------------------------------------ |
| storage            | X     | ~   | ~   | *Everything below*                   |
| storage.All        | X     | ~   | ~   | *Everything below*                   |
| storage.Name       | X     | X   | X   | Name                                 |
| storage.Type       | X     | X   | X   | Type                                 |
| storage.FileSystem | X     | X   | X   | NTFS                                 |
| storage.Mount      | X     | X   | X   | /dev/disk0s1                         |
| storage.Size       | X     | X   | X   | 500277790720                         |
| storage.Physical   | X     | X   | X   | 5002HDD77790720                      |
| storage.UUID       | X     | X   | X   | XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX |
| storage.Label      | X     | X   | X   | VM                                   |
| storage.Model      | X     | X   |     | APPLE SSD SM0512G                    |
| storage.Serial     | X     |     | X   | XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX |
| storage.Removable  | X     | X   | X   | No                                   |
| storage.Protocol   | X     | X   |     | PCI                                  |

### 6. File Systems

| Call     | Linux | Mac | Win | Comments             |
| -------- | ----- | --- | --- | -------------------- |
| fs       | X     | X   | X   | *Everything below*   |
| fs.All   | X     | X   | X   | *Everything below*   |
| fs.FS    | X     | X   | X   | /dev/disk1s1         |
| fs.Type  | X     | X   | X   | HFS                  |
| fs.Size  | X     | X   | X   | 18446744072211382272 |
| fs.Used  | X     | X   | X   | 18446744073346375680 |
| fs.Mount | X     | X   | X   | /                    |
