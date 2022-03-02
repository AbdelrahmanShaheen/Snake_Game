#pragma once
#include<iostream>
#include"Point.h"
#include<vector>
#include"Borders.h"
using namespace std;

enum Direction { STOP = 0, UP, LEFT, RIGHT, DOWN };

class Snake
{
private :
    pair<char, Point>head;
    vector<pair<char, Point>>tail;
    Direction direction;
    void MoveUp()
    {
        head.second.yAxis--;
    }
    void MoveDown()
    { 
        head.second.yAxis++; 
    }
    void MoveLeft()
    {
        head.second.xAxis--;
    }
    void MoveRight()
    {
        head.second.xAxis++;
    }
    void Shift()
    {
        if (tail.size() > 1)
        {
            int i = 0;
            for (i = 1; i < tail.size(); i++)
                tail[i - 1] = tail[i];
            tail[tail.size() - 1].second = head.second;
        }
        else if (tail.size() == 1)
        {
            tail[0].second = head.second;
        }
    }
    bool isCrashedWithBorder(Borders* screen)
    {
        if ((head.second.xAxis >= screen->GetWidth() - 1) || (head.second.xAxis < 0) || (head.second.yAxis < 0) || (head.second.yAxis >= screen->GetHeight()))
        {
            return true;
        }
        return false;
    }
    bool isCrashedWithItSelf()
    {
        for (int k = 0; k < tail.size();k++)
        {
            if ((tail[k].second.xAxis == head.second.xAxis) && (tail[k].second.yAxis == head.second.yAxis)) //use operator overloading here.
            {
                return true;
            }
        }
        return false;
    }
public : 
    Snake(){}
    Snake(pair<char, Point>head) : head(head){}
    Snake(pair<char, Point>head , vector<pair<char, Point>>tail) : head(head) ,tail(tail){}
    pair<char, Point> GetHead() const
    {
        return head;
    }
    vector<pair<char, Point>> GetTail() const
    {
        return tail;
    }
    void SetDirection(Direction dir)
    {
        direction = dir;
    }
    void eat()
    {
        if (tail.size() == 0)
            tail.push_back({ 'o' ,head.second });
        else
            tail.push_back({ 'o' ,tail[tail.size() - 1].second });
    }
    void Move()
    {
        Shift();
        switch (direction)
        {
        case STOP:
            break;
        case UP:
            MoveUp();
            break;
        case LEFT:
            MoveLeft();
            break;
        case RIGHT:
            MoveRight();
            break;
        case DOWN:
            MoveDown();
            break;
        }
    }
    bool isCrashed(Borders* screen)
    {
        bool flag1 = false ,flag2 = false;
        flag1 = isCrashedWithBorder(screen);
        flag2 = isCrashedWithItSelf();
        if (flag1 || flag2)
            return true;
    }
};

