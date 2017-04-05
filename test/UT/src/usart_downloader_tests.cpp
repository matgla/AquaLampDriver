#include "gtest/gtest.h"

#include "messages.hpp"
#include "usart_downloader.hpp"


class UsartDownloaderShould : public ::testing::Test
{
  public:
    UsartDownloaderShould()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(UsartDownloaderShould, WaitForSoftwareProvider)
{
    Logger logger;
    UsartDownloader downloader(logger);
}
TEST_F(UsartDownloaderShould, secondTest)
{
    Logger logger;
    UsartDownloader downloader(logger);
}