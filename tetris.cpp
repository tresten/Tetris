#include <windows.h>
#include<iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

/*
void map()
{
    char b=219;
    ofstream outfile("map.txt");
    for(int i=0; i<14; i++)
        outfile<<b;
    outfile<<endl;
    for (int i=0; i<20; i++)
    {
        outfile<<b;
        for (int i=0; i<12; i++)
            outfile<<' ';
        outfile<<b<<endl;
    }
    for(int i=0; i<14; i++)
        outfile<<b;
    outfile<<endl;

}
*/

struct Square
{
    vector<int> xpos={1,1,2,2};
    vector<int> ypos={1,2,1,2};
};

vector<string> getMap()
{
    vector<string> tmap;
    ifstream infile("map.txt");
    if (infile)
    {
        string s;
        while(getline(infile,s))
        {
            tmap.push_back(s);
            cout<<s<<endl;
        }

    }
    return tmap;
}

void clearScreen()
{
    system("CLS");
}

void printScreen(vector<string>tmap)
{
    for(int i=0; i<tmap.size(); i++)
        cout<<tmap.at(i)<<endl;
}

bool checkNextPos(int x, int y, vector<string>tmap)
{
    if (tmap.at(y).at(x)=='л')
    {
        return false;
    }

    else
    {
        //system("pause");
       return true;
    }



}

bool checkLeft(Square square, vector<string> tmap)
{
    bool b=true;
    for(int i =0; i<square.xpos.size()&&b; i++)
    {
        b=checkNextPos(square.xpos.at(i)-1, square.ypos.at(i),tmap);
    }
    return b;
}

bool checkRight(Square square, vector<string> tmap)
{
    bool b=true;
    for(int i =0; i<square.xpos.size()&&b; i++)
    {
        b=checkNextPos(square.xpos.at(i)+1, square.ypos.at(i),tmap);
    }
    return b;
}
void deleteCurrentPos(vector<string> &tmap, Square square)
{
    for(int i=0; i<square.xpos.size(); i++)
        tmap.at(square.ypos.at(i)).at(square.xpos.at(i))=' ';
}

void updateMap(vector<string> &tmap, Square square)
{
    for(int i=0; i<square.xpos.size(); i++)
        tmap.at(square.ypos.at(i)).at(square.xpos.at(i))=219;
}

void checkFullLine (vector<string> &tmap)
{
    for (int i=1; i< tmap.size()-1; i++)
    {
        if (tmap.at(i)=="лллллллллллллл")
        {
            for (int j=i; j>1; j--)
            {
                tmap.at(j)=tmap.at(j-1);
            }
        }
    }
}

Square pickNewCharacter(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4)
{
    vector<int>xpo={x1+5,x2+5,x3+5,x4+5};
    vector<int>ypo={y1,y2,y3,y4};
    Square s;
    s.xpos=xpo;
    s.ypos=ypo;

    return s;
}

int main()
{
    bool gameon=true, noCharacter=true;
    int y=0;
    char block=219;

    vector<string> tmap=getMap();

    Square square;
    int counter=0;
    while(gameon)
    {
        Sleep(300);
        counter++;

        if (noCharacter)
        {
            checkFullLine(tmap);
            switch(counter%7)
            {
                case(0):
                    square=pickNewCharacter(1,1,2,3,1,2,2,2);
                    break;
                case(1):
                    square=pickNewCharacter(1,2,3,3,2,2,2,1);
                    break;
                case(2):
                    square=pickNewCharacter(1,1,1,1,1,2,3,4);
                    break;
                case(3):
                    square=pickNewCharacter(1,2,2,3,2,2,1,1);
                    break;
                case(4):
                    square=pickNewCharacter(1,2,2,3,1,1,2,2);
                    break;
                case(5):
                    square=pickNewCharacter(1,1,2,2,1,2,1,2);
                    break;
                case(6):
                    square=pickNewCharacter(1,2,2,3,2,2,1,2);
                    break;
            }
            noCharacter=false;
        }
        deleteCurrentPos(tmap, square);
        for(int i=0; i<4; i++)
        {
            if (!checkNextPos(square.xpos.at(i),square.ypos.at(i)+1,tmap))
                noCharacter=true;
        }

        if (!noCharacter)
        {
            for (int j=0; j<4; j++)
                square.ypos.at(j)++;
        }

        if (GetAsyncKeyState(VK_LEFT)&&checkLeft(square,tmap))
        {
            for (int i=0; i<square.xpos.size(); i++)
                square.xpos.at(i)--;
        }
        if (GetAsyncKeyState(VK_RIGHT)&&checkRight(square,tmap))
        {
            for (int i=0; i<square.xpos.size(); i++)
                square.xpos.at(i)++;
        }
        updateMap(tmap, square);

        clearScreen();
        printScreen(tmap);
    }

    return 0;
}
