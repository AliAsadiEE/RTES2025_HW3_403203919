#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

#define SHM_SIZE 10
const char* SHM_NAME = "/my_shm";

int main() {
    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (shm_fd == -1) {
        std::cerr << "Failed to open shared memory: " << strerror(errno) << std::endl;
        return 1;
    }

    void* ptr = mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        std::cerr << "Failed to map shared memory: " << strerror(errno) << std::endl;
        return 1;
    }

    char buffer[SHM_SIZE + 1] = {0};
    memcpy(buffer, ptr, SHM_SIZE);
    std::cout << "SHM Content: \"" << buffer << "\"" << std::endl;

    munmap(ptr, SHM_SIZE);
    close(shm_fd);
    return 0;
}
