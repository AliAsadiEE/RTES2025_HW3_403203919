#include <iostream>
#include <fstream>
#include <signal.h>
#include <unistd.h>
#include <cstring>

std::ofstream logfile("received-signals.log", std::ios::app);

void signal_handler(int signal) {
    std::string name = strsignal(signal);
    std::cout << "Received signal: " << signal << " (" << name << ")" << std::endl;
    if (logfile.is_open()) {
        logfile << "Received signal: " << signal << " (" << name << ")" << std::endl;
    }
}

int main() {
    std::cout << "PID: " << getpid() << std::endl;
    for (int i = 1; i < 32; ++i) {
        signal(i, signal_handler);
    }
    while (true) {
        pause(); // wait for signal
    }
    return 0;
}
