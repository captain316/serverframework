#include "../captain/include/captain.h"
#include <unistd.h>

captain::Logger::ptr g_logger = CAPTAIN_LOG_ROOT();

void fun1() {
    CAPTAIN_LOG_INFO(g_logger) << "name: " << captain::Thread::GetName()
                             << " this.name: " << captain::Thread::GetThis()->getName()
                             << " id: " << captain::GetThreadId()
                             << " this.id: " << captain::Thread::GetThis()->getId();

}

void fun2() {

}

int main(int argc, char** argv) {
    CAPTAIN_LOG_INFO(g_logger) << "thread test begin";

    std::vector<captain::Thread::ptr> thrs;  //线程池
    for(int i = 0; i < 5; ++i) {
        captain::Thread::ptr thr(new captain::Thread(&fun1, "name_" + std::to_string(i)));
        thrs.push_back(thr);
    }

    for(size_t i = 0; i < thrs.size(); ++i) {
        thrs[i]->join();
    }
    CAPTAIN_LOG_INFO(g_logger) << "thread test end";

    return 0;
}