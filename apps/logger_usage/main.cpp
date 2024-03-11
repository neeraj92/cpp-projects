#include <chrono>
#include <sstream>
#include <thread>
#include "logger/log_mode.h"
#include "logger/logger.h"
#include "logger/string_log_storage.h"

struct BBO
{
    auto to_string() const -> std::string
    {
        std::stringstream sstr;

        sstr << "BestBid=" << best_bid << "|BestAsk=" << best_ask;
        return sstr.str();
    }

    uint32_t best_bid{};
    uint32_t best_ask{};
};

int main(int argc, char *argv[])
{
    using namespace logger;
    using enum logger::LogLevel;
    logger::Logger<BBO> logger(logger::LogLevel::Trace);

    auto thread_1 = std::thread([&logger]() {
        for (int i = 0; i < 100; i++) {
            logger.log(Error, StringLogStorage("Dummy", i, "testing", true));
        }
    });

    auto thread_2 = std::thread([&logger]() {
        std::this_thread::sleep_for(std::chrono::microseconds(100));
        BBO bbo{.best_bid = 20, .best_ask = 25};
        for (int i = 0; i < 100; i++) {
            bbo.best_bid = i * 5;
            bbo.best_ask = (i + 1) * 5;
            logger.log(Trace, bbo);
        }
    });

    thread_1.join();
    thread_2.join();
    return 0;
}
