#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <time.h>
#include "menu.h"
using namespace std;
using namespace sf;
 

const int row = 20;
const int col = 10;

int field[row][col] = {0};
struct Point
{
    int x, y;
} a[4],b[4];
int figures[7][4] =
{
    1,3,5,7, // I
    2,4,5,7, // Z
    3,5,4,6, // S
    3,5,4,7, // T
    2,3,5,7, // L
    3,5,7,6, // J
    2,3,4,5, // O
};

bool check()
{
    for (int i = 0; i <= 3; i++)
    {
        if (a[i].x < 0 || a[i].x >= col || a[i].y >= row) return 0;
        else if(field[a[i].y][a[i].x]) return 0;
    }
    return 1;
}

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(320, 480), "My Game!!!");
    window.setFramerateLimit(60);
    Menu menu(window.getSize().x, window.getSize().y);
    menu.setItemIndex();
    
    Texture t1, t2, t4;
    t1.loadFromFile("../tiles.png");
    t2.loadFromFile("../background.png");
    t4.loadFromFile("../gameover.png");

    Sprite s, bgr, frame, gov;
    s.setTexture(t1);
    bgr.setTexture(t2);
    gov.setTexture(t4);

    int d = 0;
    bool rotate = 0;
    int cNum = 1;
    float time = 0, delay = 0.3;
    int score = 0;
    bool test = 0;
    int kt = 0;

    Text text;
    Font font;
    font.loadFromFile("BarlowCondensed-Bold.ttf");
    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(Color::White);
    text.setString("SCORE");
    text.setPosition(245, 70);

 
    Clock clock;

    while (window.isOpen())
    {
        float t = clock.getElapsedTime().asSeconds();
        clock.restart();
        time += t;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) rotate = true;
                else if (event.key.code == Keyboard::Left) d = -1;
                else if (event.key.code == Keyboard::Right) d = 1;
            }     
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::A) menu.MoveUp();
                else if (event.key.code == Keyboard::D) menu.MoveDown();
                else if (event.key.code == Keyboard::Return)
                {
                    if (menu.GetPressedItem() == 0) kt = 1;
                    else window.close();
                }
            }
            if (event.type == Event::Closed)
                window.close();
        }

        
        window.clear();
        if (kt == 0)
            window.draw(gov);

        if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.1;

        //move

        for (int i = 0; i <= 3; i++)
        {
            b[i] = a[i]; 
            a[i].x += d; 
        }
        if (!check()) for(int i = 0; i <= 3; i++) a[i] = b[i];

        //xoay
        if (rotate)
        {
            Point p = a[1]; 
            for (int i=0; i <=3 ;i++)
            {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
            if (!check()) for (int i = 0; i <= 3; i++) a[i] = b[i];
        }
        
        if (time > delay)
        {
            for (int i = 0; i <= 3; i++)
            {
                b[i] = a[i];
                a[i].y += 1;
            }
            if (!check())
            {
                for (int i = 0; i <= 3; i++)
                    field[b[i].y][b[i].x] = cNum;
                cNum = 1 + rand() % 7;
                int n = rand() % 7;
                for (int i = 0; i <= 3; i++)
                {
                    a[i].x = figures[n][i] % 2;
                    a[i].y = figures[n][i] / 2;
                }
            }
            time = 0;
        }

        //check line
        int k = row - 1;
        for (int i = row - 1; i > 0; i--)
        {
            int cnt = 0;
            for (int j = 0; j < col; j++)
            {
               if (field[i][j]) cnt++;
               field[k][j]  = field[i][j];
            }
            if (cnt < col) k--;
            else score += 10;
        }
        
        for (int i = 0; i < col; i++)
        {
            if (field[1][i]) test = 1;
        }

        d = 0;
        rotate = 0;
        delay = 0.3;

        if (!test)
        {
            window.clear(Color::White);
            window.draw(bgr);

            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    if (field[i][j] == 0) continue;
                    s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
                    s.setPosition(j * 18, i * 18);
                    s.move(28, 31);
                    window.draw(s);
                }
            }

            for (int i = 0; i <= 3; i++)
            {
                s.setTextureRect(IntRect(cNum * 18, 0, 18, 18));
                s.setPosition(a[i].x * 18, a[i].y * 18);
                s.move(28, 31);
                window.draw(s);
            }

            text.setString("Scores\n" + score);
            window.draw(text);
        }
        else
        {
            if (time >= 5.f)
            {
                window.draw(gov);
                text.setCharacterSize(40);
                text.setPosition(245, 70);
                window.draw(text);
            }
        }
             
        window.display();
    }

    return 0;
}