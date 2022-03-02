#pragma once
#include <Windows.h>
#include <conio.h>
#include<iostream>
#include "Point.h"
#include "Snake.h"
#include "Borders.h"
#include "Food.h"
using namespace std;
enum Situation { GAMEOVER, WON, RUNNING };

class GameController
{
private :
	Borders *screen;
    Food *food;
    Snake *snake;
    Situation situation;
    int score;
    Point CreateFood()
    {
        Point point;
        point.xAxis = rand() % (screen->GetWidth() - 1);
        point.yAxis = rand() % (screen->GetHeight() - 1);
        return point;
    }
    bool isHeadPointEqualFoodPoint()
    {
        //use operator overloading in the condition.
        if ((food->GetPoint().xAxis == snake->GetHead().second.xAxis) && (food->GetPoint().yAxis == snake->GetHead().second.yAxis))
            return true;
        return false;
    }
    void DrawUpperBorder()
    {
        for (int i = 0; i <= screen->GetWidth();i++)//draw upper borders
            cout << '#';
        cout << endl;
    }
    void DrawBottomBorder()
    {
        for (int i = 0; i <= screen->GetWidth();i++)//draw bottom border
            cout << '#' ;
          cout << endl;
    }
    void DrawLeftBorder(int index)
    {
        if (index == 0)
            cout << '#';
    }
    void DrawRightBorder(int index)
    {
        if((index == screen->GetWidth() - 1))
            cout << '#';
    }
    void DrawSpaces(bool flag)
    {
        if (flag == false) //draw Spaces.
            cout << " ";
    }
    void DrawFood(int i ,int j ,bool *flag)
    {
        if (food->GetPoint().yAxis == i && food->GetPoint().xAxis == j) //draw Fruit.
        {
            cout << food->GetFruitShape();
            *flag = true;
        }
    }
    void DrawSnakeHead(int i, int j ,bool* flag)
    {
        
        if ((snake->GetHead().second.xAxis == j) && (snake->GetHead().second.yAxis == i)) //draw SnakeHead.
        {
            cout << snake->GetHead().first;
            *flag = true;
        }
    }
    void DrawTail(int i ,int j ,bool *flag)
    {
        vector<pair<char, Point>>tail = snake->GetTail();
        for (int k = 0; k < tail.size();k++)
        {
            if ((tail[k].second.xAxis == j) && (tail[k].second.yAxis == i))
            {
                cout << tail[k].first;
                *flag = true;
                break;
            }
        }
    }
    void Draw()
    {
        system("cls");
        DrawUpperBorder();
        for (int i = 0; i < screen->GetHeight();i++)
        {
            for (int j = 0; j < screen->GetWidth();j++)
            {
                bool flag = false;
                if (snake->GetTail().size() != 0)//draw tail.
                    DrawTail(i, j, &flag);
                DrawLeftBorder(j);
                DrawRightBorder(j);
                DrawSnakeHead(i, j, &flag);
                if(!isHeadPointEqualFoodPoint())
                DrawFood(i, j, &flag);
                DrawSpaces(flag);
            }
            cout << endl;
        }
        DrawBottomBorder();
    }
    void PressKey()
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'a':
                snake->SetDirection(LEFT);
                break;
            case 'd':
                snake->SetDirection(RIGHT);
                break;
            case 'w':
                snake->SetDirection(UP);
                break;
            case 's':
                snake->SetDirection(DOWN);
                break;
            case 'x':
                situation = GAMEOVER;
                break;
            }
        }
    }
public :
	GameController() {
        score = 0;
        situation = RUNNING;
        screen = new Borders(45, 15);
        food = new Food(CreateFood(), '*');
        pair<char, Point>head = {'O' , Point(screen->GetWidth() / 2, screen->GetHeight() / 2)};
        snake = new Snake(head);
	}
    void Run()
    {
        while (situation == RUNNING)
        {
            Draw();
            cout << "Score : " << score;
            cout << endl;
            PressKey();
            if (isHeadPointEqualFoodPoint()) 
            {
                snake->eat();
                score += 10;
                food->SetPoint(CreateFood());
            }
            snake->Move();
            if (snake->isCrashed(screen))
            {
                situation = GAMEOVER;
            }
            Sleep(100);
        }
    }
	
};

