#include <gtest/gtest.h>

#include "logger/loggerConf.hpp"

int main(int argc, char** argv)
{
    if (argc > 2 && strcmp(argv[1], "--log") == 0)
    {
        logger::LoggerConf::get().setLogToStderr();
    }
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
