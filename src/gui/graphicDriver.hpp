#pragma once

#include <functional>

namespace gui
{

class GraphicDriver
{
public:
    using SetPixelCallback  = std::function<void(int, int, bool)>;
    using GetWidthCallback  = std::function<int()>;
    using GetHeightCallback = std::function<int()>;

public:
    GraphicDriver(SetPixelCallback setPixel, GetWidthCallback getWidth, GetHeightCallback getHeight)
        : setPixel_(setPixel),
          getWidth_(getWidth),
          getHeight_(getHeight)
    {
    }

    void setPixel(int x, int y, bool enable)
    {
        setPixel_(x, y, enable);
    }

    int width() const
    {
        return getWidth_();
    }

    int height() const
    {
        return getHeight_();
    }

private:
    SetPixelCallback setPixel_;
    GetWidthCallback getWidth_;
    GetHeightCallback getHeight_;
};

} // namespace gui
