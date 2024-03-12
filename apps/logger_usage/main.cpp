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

struct Trade
{
    [[nodiscard]] auto to_string() const -> std::string
    {
        std::stringstream sstr;
        sstr << "Price=" << price << "|Quantity=" << quantity << "|Side=" << side;
        return sstr.str();
    }

    uint32_t price{};
    uint32_t quantity{};
    char side{};
};

int main(int argc, char *argv[])
{
    using namespace logger;
    using enum logger::LogLevel;
    logger::Logger<BBO, Trade> logger(logger::LogMode::File, logger::LogLevel::Trace, "/tmp/logger_usage", true);

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

    auto thread_3 = std::thread([&logger]() {
        std::this_thread::sleep_for(std::chrono::microseconds(100));

        for (uint i = 0; i < 100; i++) {
            Trade trade{.price = i * 1000, .quantity = i, .side = 'B'};
            logger.log(Warning, trade);
        }
    });

    thread_1.join();
    thread_2.join();
    thread_3.join();
    return 0;
}
