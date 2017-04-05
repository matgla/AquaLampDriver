#pragma once

template <typename... Args>
class Expectation;

template <typename ReturnType>
class Expectation<ReturnType>
{
  public:
    Expectation(bool inSequence = false)
        : inSequence_(inSequence)
    {
    }

    void setInSequence()
    {
        inSequence_ = true;
    }

    bool inSequence()
    {
        return inSequence_;
    }

    void setFile(const std::string& file)
    {
        file_ = file;
    }

    void setLine(int line)
    {
        line_ = line;
    }

    const std::string& getFile() const
    {
        return file_;
    }

    int getLine() const
    {
        return line_;
    }

    void willReturn(const ReturnType& returns)
    {
        returns_ = returns;
    }

    ReturnType returnValue()
    {
        return returns_;
    }

  private:
    bool inSequence_;
    std::string file_;
    int line_;
    ReturnType returns_;
};

template <typename ReturnType, typename... Args>
class Expectation<ReturnType, Args...> : public Expectation<ReturnType>
{
  public:
    Expectation(std::tuple<Args...> expectedArgs, bool inSequence = false)
        : Expectation<ReturnType>(inSequence), expectedArgs_(expectedArgs)
    {
    }

    void setExpectedArgs(std::tuple<Args...> expectedArgs)
    {
        expectedArgs_ = expectedArgs;
    }

    const std::tuple<Args...>& getExpectedArgs()
    {
        return expectedArgs_;
    }

  private:
    std::tuple<Args...> expectedArgs_;
};