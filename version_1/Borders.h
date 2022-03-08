#pragma once
class Borders
{
private :
    int width;
    int height;

public :
    Borders(int width, int height) {
        this->height = height;
        this->width = width;
    }

    int GetWidth() const
    {
        return width;
    }

    int GetHeight() const
    {
        return height;
    }
};

