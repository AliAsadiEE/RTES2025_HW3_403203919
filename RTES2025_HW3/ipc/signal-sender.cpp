#include <iostream>
#include <csignal>
#include <cstdlib>
#include <cerrno>
#include <cstring>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <PID> <SIGNAL_NUMBER>" << std::endl;
        return 1;
    }

    pid_t pid = std::stoi(argv[1]);
    int sig = std::stoi(argv[2]);

    if (kill(pid, sig) == -1) {
        std::cerr << "Failed to send signal: " << strerror(errno) << std::endl;
        return 1;
    }

    std::cout << "Signal " << sig << " sent to PID " << pid << std::endl;
    return 0;
}
