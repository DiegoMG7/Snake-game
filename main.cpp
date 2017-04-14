#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>

using namespace std;
bool gameover;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100],tailY[100];
int nTail;//length of tail
enum direction {STOP = 0,LEFT,RIGHT,UP,DOWN};// direction is a class, the stuff in{} <--that is a structure, enum helps to create your own data
direction dir;
void setup()
{
	gameover = false;
	dir = STOP;
	x = width / 2;//position of the head(in the middle of the map)
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void draw()
{
	system("cls");

	for (int i = 0; i < width+2; ++i)//displays the top of our map
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; ++i)//print the map
	{
		for (int j = 0; j < width; ++j)
		{
			if (j == 0)
				cout << "#";//left wall

            if(i==y && j==x)
                cout << "O";
            else if(i==fruitY && j==fruitX)
                cout << "F";
            else
            {
                bool print=false;
                for (int k=0; k<nTail; ++k)
                {
                    if(tailX[k]==j && tailY[k]==i)
                    {
                        cout << "o";
                        print=true;
                    }
                }
                if(!print)
                    cout << " ";

            }


			if (j == width - 1)
				cout << "#";//right wall

		}
		cout << endl;
	}

	for (int i = 0; i < width+2; ++i)//displays the bottom of our game
		cout << "#";
	cout << endl;
	cout << "score: " << score << endl;
}

void input ()
{
    if(_kbhit())//key button press
    {
        switch(_getch())//sends the charachter that was pressed before
        {
            case 'a':
                dir=LEFT;
                break;

            case 'd':
                dir=RIGHT;
                break;

            case 'w':
                dir=UP;
                break;

            case 's':
                dir=DOWN;
                break;

            case 'x':
                gameover=true;
                break;
        }
    }
}

void logic()
{
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X,prev2Y;
    tailX[0]=x;
    tailY[0]=y;//to follow the head
    for(int i=1; i < nTail; ++i)//print move of the tail
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir)
    {
            case LEFT:
                --x;
                break;

            case RIGHT:
                ++x;
                break;

            case UP:
                --y;
                break;

            case DOWN:
                ++y;
                break;

            default:
                break;
    }

    if(x > width || x < 0 || y > height || y < 0)//going out the map
        gameover = true;
    for(int i=0; i<nTail; ++i)
        if(tailX[i]==x && tailY[i]==y)
            gameover=true;

    if(x==fruitX && y==fruitY)
    {
        score += 10;
        fruitX = rand() % width;// makes reappear the fruit
        fruitY = rand() % height;
        ++nTail;
    }

}


int main()
{
	setup();
	while (!gameover)
	{
		draw();
		input();
		logic();
		Sleep(100); //it makes it slower
	}
    return 0;
}

