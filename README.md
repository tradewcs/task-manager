# Mini Task Manager (`taskman`)

A lightweight Linux terminal-based task manager written in **C**.  
It allows users to list, inspect, search, and terminate processes from the command line, with optional sorting by memory or CPU usage.

---

## Features

- List all running processes (`PID`, `Name`, `Memory`, `CPU`)  
- Sort processes by memory (`--sort=mem`) or CPU usage (`--sort=cpu`)  
- Display detailed process information (`Name`, `State`, `Memory`, `Threads`)  
- Kill a process by PID using `SIGTERM`  
- Search for processes by name  

---

## Installation

1. Clone the repository:  
```bash
git clone <repo-url>
cd task-manager
```

2. Build the project:  
```bash
make
```

3. Run the executable:  
```bash
./taskman list
```

---

## Usage

```bash
./taskman list [--sort=cpu|mem]   # List processes
./taskman info <pid>              # Show details of a specific process
./taskman kill <pid>              # Terminate a process by PID
./taskman search <name>           # Find processes matching a name
```

**Examples:**

```bash
./taskman list --sort=mem
./taskman info 1234
./taskman kill 5678
./taskman search firefox
```

---
