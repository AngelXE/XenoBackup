# XenoBackup

**A lightweight automatic directory backup tool written in C++.**

XenoBackup automatically creates copies of a directory at a user-defined interval and stops after reaching a configurable backup limit.

Built as a small, dependency-free C++ command-line utility focused on simplicity and reliability.

<p align="center">
  <img width="385" height="256" alt="XenoBackup" src="https://github.com/user-attachments/assets/2cbbb1d7-13a9-40f2-b5f5-db6dcac13bb1" />
</p>

---

## ✨ Features

* 📁 **Directory backups** — recursively copies files and subdirectories.
* ⏱️ **Automatic intervals** — choose how often backups are created.
* 🔢 **Backup limits** — automatically stop after a specified number of backups.
* 🛡️ **Input validation** — rejects invalid and excessively large values.
* ⚡ **Lightweight** — uses standard C++ and system APIs.
* 🖥️ **Simple CLI** — no graphical interface or unnecessary dependencies.
* 📦 **Sequential backups** — backups are automatically numbered.
* ⚙️ **Automatic OS detection** — the included setup script detects your operating system.

---

## 📦 Requirements

XenoBackup requires:

* Python 3
* A C++ compiler

### Windows

* `g++`

### macOS

* `clang++`

### Linux

* `g++`

**No Python packages are required.**

---

## 🚀 Installation

Clone the repository:

```bash
git clone https://github.com/AngelXE/XenoBackup.git
```

Enter the project directory:

```bash
cd XenoBackup
```

Then run the setup script:

```bash
python3 setup.py
```

The setup script automatically detects your operating system and compiles XenoBackup.

### Windows

```text
[+] Windows Detected
[+] compiling...
[+] XenoBackup compiled successfully!
[+] Output: xenobackup.exe
```

### macOS

```text
[+] MacOS Detected
[+] compiling...
[+] XenoBackup compiled successfully!
[+] Output: xenobackup
```

### Linux

```text
[+] Linux Detected
[+] compiling...
[+] XenoBackup compiled successfully!
[+] Output: xenobackup
```

---

## ▶️ Running XenoBackup

### Windows

```powershell
.\xenobackup.exe
```

### macOS / Linux

```bash
./xenobackup
```

---

## 🚀 How It Works

You provide three things:

```text
directory> /path/to/project
interval in seconds> 60
backup limit> 10
```

XenoBackup then creates backups automatically:

```text
project_backup_1
project_backup_2
project_backup_3
project_backup_4
...
```

The program continues creating backups until the configured limit is reached.

---

## 🖥️ Example

```text
   _  __              ___           __
  | |/_/__ ___  ___  / _ )___ _____/ /____ _____
 _>  </ -_) _ \/ _ \/ _  / _ `/ __/  '_/ // / _ \
/_/|_|\__/_//_/\___/____/\_,_/\__/_/\_\\_,_/ .__/
                                          /_/

+-----------------------------------------------------+

directory> ./my-project
interval in seconds> 60
backup limit> 5

+-----------------------------------------------------+

directory: ./my-project
interval in seconds: 60
backup limit: 5

+-----------------------------------------------------+

[*] XenoBackup started.
[*] Next backup in 60 seconds.

[*] Creating backup...
[+] Backup created: my-project_backup_1

[*] Creating backup...
[+] Backup created: my-project_backup_2

[*] Creating backup...
[+] Backup created: my-project_backup_3
```

After the configured number of backups:

```text
[!] Backup limit reached.
```

---

## ⚙️ Configuration

### Directory

The directory that should be backed up.

```text
directory> ./my-project
```

### Backup interval

The amount of time between backups, in seconds.

```text
interval in seconds> 300
```

For example, `300` creates a backup every **5 minutes**.

### Backup limit

The maximum number of backups XenoBackup will create during the current run.

```text
backup limit> 20
```

---

## 📂 Backup Structure

If you back up:

```text
my-project/
├── src/
│   ├── main.cpp
│   └── utils.cpp
├── README.md
└── config.txt
```

XenoBackup creates:

```text
my-project_backup_1/
├── src/
│   ├── main.cpp
│   └── utils.cpp
├── README.md
└── config.txt
```

Each backup is a separate copy of the original directory.

---

## 🛠️ Manual Compilation

You can also compile XenoBackup manually without `setup.py`.

### macOS

```bash
clang++ main.cpp -o xenobackup
```

### Linux

```bash
g++ main.cpp -o xenobackup
```

### Windows

```powershell
g++ main.cpp -o xenobackup.exe
```

---

## 🧠 Why XenoBackup?

XenoBackup started as a small C++ project for experimenting with:

* File I/O
* Directory traversal
* Recursive operations
* Backup automation
* Input validation
* Timed operations
* C++ system programming
* Command-line interfaces

The project intentionally keeps things simple instead of relying on large frameworks or external libraries.

---

## 🚧 Roadmap

Future versions may include:

* [ ] Restore backups
* [ ] Backup compression
* [ ] Backup encryption
* [ ] Custom backup names
* [ ] Configuration files
* [ ] Backup history
* [ ] Better progress information
* [ ] Selective file backup
* [ ] Improved error handling
* [ ] Cross-platform filesystem support

---

## 🤝 Contributing

Have an idea for XenoBackup?

Issues, bug reports, improvements, and pull requests are welcome.

If you find a bug, please include:

1. Your operating system
2. Compiler and version
3. The command used to compile XenoBackup
4. The input that caused the problem
5. The resulting error

---

## 📄 License

XenoBackup is released under the **MIT License**.

See [`LICENSE`](LICENSE) for the full license text.

---

<p align="center">
  <strong>XenoBackup</strong><br>
  Simple. Automatic. C++.
</p>
