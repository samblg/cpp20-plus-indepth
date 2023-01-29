#include <filesystem>
#include <iostream>
#include <thread>
 
namespace fs = std::filesystem;
 
void createDirectoriesAsync(std::string directoryPath) {
    std::cout << "Create directory: " << directoryPath << std::endl;
    fs::create_directories(directoryPath);
}

int main() {
    std::cout << "Start task" << std::endl;
 
    std::thread makeDirTask1(createDirectoriesAsync, "dir1/a/b/c");
    std::thread makeDirTask2(createDirectoriesAsync, "dir2/1/2/3");
    std::thread makeDirTask3(createDirectoriesAsync, "dir3/A/B/C");
    
    makeDirTask1.join();
    makeDirTask2.join();
    makeDirTask3.join();
    std::cout << "All task finished" << std::endl;
 
    return 0;
}
