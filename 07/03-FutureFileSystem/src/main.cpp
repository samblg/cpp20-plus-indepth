#include <filesystem>
#include <iostream>
#include <future>
#include <exception>
 
namespace fs = std::filesystem;
 
void createDirectoriesAsync(
    std::string directoryPath,
    std::promise<bool> promise
) {
    try {
        std::cout << "Create directory: " << directoryPath << std::endl;
        bool result = fs::create_directories(directoryPath);
        
        promise.set_value(result);
    } catch (...) {
        promise.set_exception(std::current_exception());
        promise.set_value(false);
    }
}
 
int main() {
    std::cout << "Start task" << std::endl;
 
    std::promise<bool> taskPromise1;
    std::future<bool> taskFuture1 = taskPromise1.get_future();
    std::thread makeDirTask1(createDirectoriesAsync, "dir1/a/b/c", std::move(taskPromise1));
 
    std::promise<bool> taskPromise2;
    std::future<bool> taskFuture2 = taskPromise2.get_future();
    std::thread makeDirTask2(createDirectoriesAsync, "dir2/1/2/3", std::move(taskPromise2));
 
    std::promise<bool> taskPromise3;
    std::future<bool> taskFuture3 = taskPromise3.get_future();
    std::thread makeDirTask3(createDirectoriesAsync, "dir3/A/B/C", std::move(taskPromise3));
    
    taskFuture1.wait();
    taskFuture2.wait();
    taskFuture3.wait();
 
    std::cout << "Task1 result: " << taskFuture1.get() << std::endl;
    std::cout << "Task2 result: " << taskFuture2.get() << std::endl;
    std::cout << "Task3 result: " << taskFuture3.get() << std::endl;
 
    makeDirTask1.join();
    makeDirTask2.join();
    makeDirTask3.join();

    std::cout << "All task finished" << std::endl;
    return 0;
}
