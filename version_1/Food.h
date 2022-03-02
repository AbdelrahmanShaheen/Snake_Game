#pragma once
#include "Point.h"
class Food
{
private:
    Point fruitPoint;
    char fruitShape;
public :
    Food() {}
    Food(Point fruitPoint, char fruitShape) : fruitPoint(fruitPoint), fruitShape(fruitShape){}
    Point GetPoint() const
    {
        return fruitPoint;
    }
    char GetFruitShape() const
    {
        return fruitShape;
    }
    void SetPoint(Point point)
    {
        fruitPoint = point;
    }
};

