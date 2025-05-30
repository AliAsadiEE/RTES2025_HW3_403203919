#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <string>

#define SHM_SIZE 10
const char* SHM_NAME = "/my_shm";

int main() {
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        std::cerr << "Failed to create shared memory: " << strerror(errno) << std::endl;
        return 1;
    }

    if (ftruncate(shm_fd, SHM_SIZE + 1) == -1) { // +1 for write_pos
        std::cerr << "Failed to resize shared memory: " << strerror(errno) << std::endl;
        return 1;
    }

    void* ptr = mmap(0, SHM_SIZE + 1, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        std::cerr << "Failed to map shared memory: " << strerror(errno) << std::endl;
        return 1;
    }

    char* mem = static_cast<char*>(ptr);
    char& write_pos = mem[SHM_SIZE];  // آخرین بایت برای نگهداری موقعیت نوشتن

    // مقدار اولیه موقعیت نوشتن رو اگر نامشخصه صفر کن
    if (write_pos < 0 || write_pos >= SHM_SIZE) {
        write_pos = 0;
    }

    std::string input;
    std::cout << "Enter text lines (type 'exit' to quit):" << std::endl;

    while (true) {
        std::getline(std::cin, input);
        if (input == "exit") {
            break;
        }

        for (char c : input) {
            mem[write_pos] = c;
            write_pos = (write_pos + 1) % SHM_SIZE;
        }
    }

    munmap(ptr, SHM_SIZE + 1);
    close(shm_fd);
    return 0;
}
