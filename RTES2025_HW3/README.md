# 📚 Embedded Linux Exercise 3 : OrangePi Zero 2 Plus

Welcome to the Embedded Linux exercise for setting up and exploring the **OrangePi Zero 2 Plus** board. Follow the steps below to configure the board, connect to networks, and implement tasks to deepen your understanding of embedded systems. 🚀

# Assignment Submission Instructions

Push your repository to your GitHub account and set it to public. I will clone the repository and assign your grade based on its contents. Additionally, record a video (using your phone, not screen recording) demonstrating the stages of your code (e.g., development or execution). Create a text file named `repolink.txt` containing only your GitHub repository URL. Package the video, the repository folder, and `repolink.txt` into a single ZIP file named `RTES2025_HW3_{student_number}.zip`, where `{student_number}` is your student ID. Upload the ZIP file to CW. Answer the assignment questions in the repository's `README.md` file using Markdown syntax.

The ZIP file should follow this directory structure:

```
RTES2025_HW3_401234567
├── HW3.mp4  # Supported formats: mp4, mkv, mpeg, or similar
├── repolink.txt       # Contains the GitHub repository URL
└── RTES2025_HW3       # Repository folder
    ├── auto-wifi-connect
    ├── ipc
    └── ...
```

---

### 🛠️ Setting Up the OrangePi Zero 2 Plus
Follow the instructional video to configure the OrangePi Zero 2 Plus board.

---

### 🌐 Wi-Fi and SSH Connection
1. Create a Wi-Fi hotspot using your phone 📱 or laptop 💻 with a custom SSID and password. Ensure the frequency is set to **2.4 GHz** and internet access is enabled.
   - **💡 Tip**: Use the `nmcli` command to connect to Wi-Fi.
   - **💡 Tip**: Connect to the board via SSH using the **Remote – SSH** extension in VS Code or an SSH client (e.g., PuTTY) for a smoother workflow.

---

### 🗂️ Introduction to Git
Clone the provided repository 📂 using SSH. The repository contains incomplete code and testing tools for the tasks below.
---

### 📡 Automatic Wi-Fi Connection
Write a shell script 🖥️ using `nmcli` to automatically connect to a specified Wi-Fi network (e.g., **MySSID**) if the device is not already connected.
- Schedule the script to run **every minutes** using a **cron job**.
- Configure the script to execute once at **system boot** using the cron `@reboot` directive.
- Log connection status, available Wi-Fi networks, and other relevant details to a file named `auto-connect.log`.

---

### 🔗 Inter-Process Communication Mechanisms
Explore three inter-process communication (IPC) methods to understand task communication in Linux:
1. **FIFO** 📥📤
Description: FIFO stands for First In, First Out, also known as named pipes. It is a special file that allows one-way communication between processes in a producer-consumer style.

How it works: One process writes data into the FIFO, and another process reads data out in the same order it was written.

Usage:

Suitable for simple, unidirectional communication between processes that have a producer-consumer relationship.

Unlike anonymous pipes, FIFOs have a name and exist as special files in the filesystem, allowing unrelated processes to communicate.

Characteristics:

Operates in a byte-stream fashion, preserving the order of bytes.

Data is transient; once read, it is removed from the pipe.

Simple to implement but less efficient for large data or complex synchronization.

A FIFO is a special file that allows unrelated processes to communicate in a first-in, first-out manner. It’s created using the mkfifo command and accessed like a regular file.
Example:
mkfifo /tmp/myfifo
echo "Hello" > /tmp/myfifo  # Writer
cat /tmp/myfifo             # Reader
Good for simple, one-way communication between two processes.

2. **Linux Signals** ⚡
Description: Signals are limited, asynchronous notifications sent to a process to notify it of events like interrupts, termination requests, or exceptions.

How it works:

A process can send a signal to another process or itself using system calls like kill().

Signals carry minimal information — essentially just the signal number — and trigger a predefined or custom signal handler.

Common signals:

SIGINT (interrupt from keyboard, e.g., Ctrl+C),

SIGTERM (termination request),

SIGKILL (force kill, cannot be caught or ignored),

SIGUSR1 and SIGUSR2 (user-defined signals).

Usage:

Useful for control and notification purposes rather than data transfer.

Allows processes to interrupt or modify the behavior of others (e.g., graceful shutdown).

Limitations:

Signals do not carry payload data beyond their type.

Overuse can cause race conditions or missed signals without careful programming.

Signals are used to notify a process that an event has occurred, such as an interrupt or termination request. Each signal has a numeric ID (e.g., SIGINT = 2).

Example (in C):
signal(SIGINT, handler_function);
🟢 Useful for control and status events.
🔴 Not ideal for sending data.

3. **Shared Memory** 🗄️
Description: Shared memory allows multiple processes to access a common memory segment directly, enabling high-speed data exchange.

How it works:

A segment of memory is created (e.g., via shmget() or shm_open()) and mapped into the address space of multiple processes.

Processes read and write to this memory as if it were their own.

Advantages:

Fastest IPC method since no copying of data between kernel and user space is needed.

Suitable for exchanging large volumes of data or complex data structures.

Challenges:

Requires explicit synchronization mechanisms (mutexes, semaphores) to prevent race conditions and data corruption.

Complexity increases with the number of processes sharing the memory.

Usage:

Ideal for applications requiring efficient data sharing, like multimedia processing, databases, or real-time systems.
| IPC Mechanism | Data Transfer | Direction      | Persistence               | Speed     | Complexity | Typical Use Cases              |
| ------------- | ------------- | -------------- | ------------------------- | --------- | ---------- | ------------------------------ |
| FIFO          | Byte stream   | Unidirectional | Transient                 | Moderate  | Low        | Simple producer-consumer tasks |
| Signals       | Signal number | Asynchronous   | Transient                 | Fast      | Moderate   | Notifications, control signals |
| Shared Memory | Shared memory | Bidirectional  | Persistent (till removed) | Very fast | High       | Large data, high performance   |


| Feature        | FIFO           | Signals             | Shared Memory    |
| -------------- | -------------- | ------------------- | ---------------- |
| Speed          | Medium         | Very Fast (notify)  | Very High        |
| Data Type      | Stream (bytes) | Simple notification | Bulk data        |
| Sync Required? | No             | No                  | Yes (mutex, sem) |
| Complexity     | Low            | Low to Medium       | High             |


#### 1. FIFO
Complete the provided `fifo-sender.sh` and `fifo-receiver.sh` scripts in the GitHub repository. When executed:
- The sender script should create a FIFO (if it doesn't exist) and transmit terminal input to the receiver via the FIFO.
- The receiver should display the input immediately.

#### 2. Linux Signals
Complete the provided C++ programs `signal-receiver.cpp` and `signal-sender.cpp`:
- **Receiver** 🖨️: Prints its **PID** on startup, waits for signals, and logs each received signal to a file.
- **Sender** 📩: Accepts a PID and signal number as command-line arguments and sends the signal to the specified process.

Answer the following:
- ❓ What is the difference between the **SIGINT** and **SIGKILL** signals?

| Signal    | Description                                                                               | Can Be Handled? |
| --------- | ----------------------------------------------------------------------------------------- | --------------- |
| `SIGINT`  | Sent when you press `Ctrl+C` in the terminal. Asks the process to terminate *gracefully*. | ✅ Yes           |
| `SIGKILL` | Forcefully terminates a process *immediately* without cleanup or handler execution.       | ❌ No            |

SIGINT gives the process a chance to clean up (e.g., close files), but SIGKILL is brutal and non-negotiable.

| Feature                   | SIGINT                                                                          | SIGKILL                                                 |
| ------------------------- | ------------------------------------------------------------------------------- | ------------------------------------------------------- |
| Signal Number             | 2                                                                               | 9                                                       |
| Purpose                   | Interrupt signal (typically sent when user presses Ctrl+C)                      | Kill signal (forces immediate termination)              |
| Can be caught or handled? | **Yes**, processes can catch, ignore, or handle SIGINT                          | **No**, cannot be caught, blocked, or ignored           |
| Effect on process         | Process can perform cleanup before terminating or continue execution if handled | Immediate termination without cleanup                   |
| Use case                  | Graceful termination initiated by user                                          | Forceful termination of unresponsive or stuck processes |

- ❓ Which signals can be caught or handled by a process?

Most signals can be caught, handled, or ignored using functions like signal() or sigaction().
However, some signals cannot be caught, blocked, or ignored:

❌ SIGKILL (9)

❌ SIGSTOP (19)

All other signals (e.g., SIGTERM, SIGUSR1, SIGINT) can be handled or ignored.
Most signals can be caught or handled by installing a signal handler using signal() or sigaction().

Exceptions:

SIGKILL (signal number 9) and

SIGSTOP (signal number 19)
cannot be caught, blocked, or ignored.
These signals are reserved for forcing process termination or stopping.


- ❓ How many signals are defined in Linux?

There are typically 31 standard signals (1–31) and several real-time signals starting from signal number 34 (usually up to 64), depending on the architecture.

You can list all signals using:
kill -l
Example output includes: SIGHUP, SIGINT, SIGQUIT, SIGILL, ..., SIGRTMIN, SIGRTMAX.

 Total: Around 64 signals on most Linux systems (standard + real-time).
 Linux defines a set of standard signals, typically 31 signals (1 to 31), including signals like SIGINT, SIGTERM, SIGQUIT, etc.

Additionally, Linux supports real-time signals, numbered from 32 to 64, which provide more flexible user-defined signal mechanisms.

root@orangepizeroplus:~# kill -l
 1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL       5) SIGTRAP
 6) SIGABRT      7) SIGBUS       8) SIGFPE       9) SIGKILL     10) SIGUSR1
11) SIGSEGV     12) SIGUSR2     13) SIGPIPE     14) SIGALRM     15) SIGTERM
16) SIGSTKFLT   17) SIGCHLD     18) SIGCONT     19) SIGSTOP     20) SIGTSTP
21) SIGTTIN     22) SIGTTOU     23) SIGURG      24) SIGXCPU     25) SIGXFSZ
26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGIO       30) SIGPWR
31) SIGSYS      34) SIGRTMIN    35) SIGRTMIN+1  36) SIGRTMIN+2  37) SIGRTMIN+3
38) SIGRTMIN+4  39) SIGRTMIN+5  40) SIGRTMIN+6  41) SIGRTMIN+7  42) SIGRTMIN+8
43) SIGRTMIN+9  44) SIGRTMIN+10 45) SIGRTMIN+11 46) SIGRTMIN+12 47) SIGRTMIN+13
48) SIGRTMIN+14 49) SIGRTMIN+15 50) SIGRTMAX-14 51) SIGRTMAX-13 52) SIGRTMAX-12
53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9  56) SIGRTMAX-8  57) SIGRTMAX-7
58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4  61) SIGRTMAX-3  62) SIGRTMAX-2
63) SIGRTMAX-1  64) SIGRTMAX


#### 3. Shared Memory
Complete the provided C++ programs `shm-writer.cpp` and `shm-reader.cpp`:
- **Writer** ✍️: Creates a shared memory segment and writes user input into a **10-character circular buffer**.
- **Reader** 📖: Reads and displays the contents of the shared memory upon execution.

Answer the following:
- ❓ What are the key differences between FIFO and shared memory for IPC?

| Feature             | FIFO (Named Pipe)                     | Shared Memory                                   |
| ------------------- | ------------------------------------- | ----------------------------------------------- |
| **Speed**           | Slower (data is copied via kernel)    | Very fast (direct memory access)                |
| **Direction**       | One-way or half-duplex                | Two-way with proper synchronization             |
| **Persistence**     | Exists as a file in the filesystem    | Lives in memory; needs setup via APIs           |
| **Synchronization** | Implicit (reader blocks if no writer) | Requires explicit mechanisms (e.g., semaphores) |
| **Use Case**        | Simple data exchange                  | High-performance, large data sharing            |
| **Complexity**      | Simple to implement                   | More complex (setup + sync)                     |

Use FIFO for simplicity, and Shared Memory when performance is critical.

| Aspect                  | FIFO (Named Pipe)                             | Shared Memory                                                                   |
| ----------------------- | --------------------------------------------- | ------------------------------------------------------------------------------- |
| **Communication type**  | Byte-stream communication via a kernel buffer | Direct access to a common memory segment                                        |
| **Data transfer speed** | Generally slower due to kernel involvement    | Fastest IPC method since data is accessed directly in RAM                       |
| **Data persistence**    | Data is transient and consumed as it is read  | Data persists in shared memory until explicitly removed                         |
| **Synchronization**     | Implicit (blocking read/write operations)     | Requires explicit synchronization (e.g., semaphores) to prevent race conditions |
| **Directionality**      | Typically unidirectional per FIFO             | Bidirectional by default                                                        |
| **Complexity**          | Simple to use and implement                   | More complex due to manual memory management and synchronization                |
| **Use case**            | Simple producer-consumer scenarios            | High-performance scenarios with large data sharing or complex data structures   |

Summary:

FIFO acts like a pipe where one process writes and another reads sequentially through the kernel, making it easier but slower and unidirectional.

Shared Memory lets processes access the same memory region directly, providing high speed and bidirectional communication but requiring careful synchronization to avoid conflicts.





---

### 🌍 Basic Web Server
Complete the provided shell script 🌐 to create a simple web server that listens on **port 80** and responds to HTTP requests with the system’s current **date and time**.
- It should print the response in the terminal too when run by terminal.
- Create a Systemd Service (webserver.service) so that:
    Start after the network is online (connected to wifi).
    Restart automatically if the script exits (with a 5-second delay).
    Log output and errors to the system journal.
    Run on system boot.
You should put the service file behind the webserver script in the submission and in the repository.

- **💡 Tip**: Use the `nc` (netcat) command for handling network connections.
    
---

### 📚 Useful Reference Websites
- **OrangePi Documentation**: [Official OrangePi Wiki](http://www.orangepi.org/orangepiwiki/) – Guides for setting up OrangePi boards.
- **Linux Networking**: [nmcli Documentation](https://networkmanager.dev/docs/api/latest/nmcli.html) – Manage Wi-Fi with `nmcli`.
- **Git Basics**: [Git SCM](https://git-scm.com/doc) – Official Git documentation for cloning and managing repositories.
- **Systemd Services**: [Systemd Documentation](https://www.freedesktop.org/software/systemd/man/systemd.service.html) – Guide to creating systemd services.
- **Linux IPC**: [Beej’s Guide to IPC](https://beej.us/guide/bgipc/) – Comprehensive resource on FIFO, signals, and shared memory.
- **Netcat Usage**: [Netcat Manual](http://nc110.sourceforge.net/) – Learn how to use `nc` for networking tasks.

---

Happy coding! 🎉
