#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include<utility>
#include<vector>
#include"kv_windows.h"
using namespace std;

unsigned char UC = 0xCA,DC = 0xCB,ULB = 201,DLB = 200,URB = 187,DRB = 188,HT = 205,VT = 186,LC = 0xCC,RC = 0xB9,NC = 0xCE;

vector<pair<int,WORD>> ColorPalette = {{1,RED},{2,BROWN},{3,GREEN},{4,BLUE},{5,YELLOW},{6,DARK_GREEN},
                                       {7,DARK_BLUE},{8,DARK_TURQUOISE},{9,TURQUOISE},{10,PINK},
                                       {11,PURPLE},{12,OLIVE},{13,WHITE},{14,BLACK},{15,GRAY},{16,DARK_GRAY}};

vector<unsigned char> BrushPalette = {219,178,177,176,32};

void ClearLog()
{
    ShowCursor(FALSE);
    SetCursorAt(100,55);
    cout<<"                                        ";
    SetCursorAt(100,55);
}
bool Exist(string path)
{
    ifstream ifile;
    ifile.open(path.c_str(),ios::in|ios::binary);
    return bool(ifile);
}
void SaveinExisting(CHAR_INFO cbuf[168*54],string path)
{
    fstream fout;
    fout.open(("Saved ASCII Images\\"+path).c_str(),ios::out|ios::binary);
    for(int i=0;i<168*54;i++)
        fout.write((char*)&cbuf[i],sizeof(cbuf[i]));
    fout.close();
}
void Save(CHAR_INFO cbuf[168*54],string path)
{
    if(!Exist(path))
    {
        fstream fout;
        fout.open(("Saved ASCII Images\\"+path).c_str(),ios::out|ios::binary);
        for(int i=0;i<168*54;i++)
            fout.write((char*)&cbuf[i],sizeof(cbuf[i]));
        fout.close();
    }
    else
    {
        ClearLog();
        cout<<"Overwrite ? (Y/N) - ";char ch = cin.get();
        if(ch == 'Y' || ch == 'y')
        {
            fstream fout;
            fout.open(path.c_str(),ios::out|ios::binary);
            for(int i=0;i<168*54;i++)
                fout.write((char*)&cbuf[i],sizeof(cbuf[i]));
            fout.close();
        }
    }
}
void Load(CHAR_INFO cbuf[168*54],string path)
{
    fstream fin;
    fin.open(("Saved ASCII Images\\"+path).c_str(),ios::in|ios::binary);
    for(int i=0;i<168*54;i++)
        fin.read((char*)&cbuf[i],sizeof(cbuf[i]));
    fin.close();
}
void PrintButtons(int currpos,string txt,WORD CC)
{
    int len = txt.length()+2;
    SetCursorAt(currpos,54);
    SetConsoleColor(BGWHITE|BLACK);
    cout<<char(201); for(int i=0;i<len;i++) cout<<char(205); cout<<char(187);
    SetCursorAt(currpos,55);
    cout<<char(186);
    SetConsoleColor(CC|BGWHITE);
    cout<<" "<<txt<<" ";
    SetConsoleColor(BGWHITE|BLACK);
    cout<<char(186);
    SetCursorAt(currpos,56);
    cout<<char(200);
    for(int i=0;i<len;i++) cout<<char(205);
    cout<<char(188);
}
void ClickButton(string txt,int x1,WORD CC,WORD CB)
{
    SetCursorAt(x1+1,55);
    SetConsoleColor(CC|CB);
    cout<<" "<<txt<<" ";
}
void PrintPalette()
{
    SetCursorAt(4,54);
    SetConsoleColor(BLACK|BGWHITE);
    cout<<char(201);
    for(int i=1;i<32/2;i++) cout<<char(205)<<char(203);
    cout<<char(205)<<char(187);
    SetCursorAt(4,55);
    int i=0;
    cout<<char(186);
    for(i=0;i<16;i++)
    {
        SetConsoleColor(ColorPalette[i].second);
        cout<<char(219);
        SetConsoleColor(BLACK|BGWHITE);
        cout<<char(186);
    }
    SetCursorAt(4,56);
    cout<<char(200);
    for(int i=1;i<33/2;i++) cout<<char(205)<<char(202);
    cout<<char(205)<<char(188);
}
void PrintBrushes(WORD CF,WORD CB = BGWHITE)
{
    SetCursorAt(39,54);
    SetConsoleColor(BGWHITE|BLACK);
    cout<<char(201);
    for(int i=1;i<5;i++) cout<<char(205)<<char(203);
    cout<<char(205)<<char(187);
    SetCursorAt(39,55);
    int i=0;
    cout<<char(186);
    for(i=0;i<5;i++)
    {
        SetConsoleColor(CF|CB);
        cout<<BrushPalette.at(i);
        SetConsoleColor(BLACK|BGWHITE);
        cout<<char(186);
    }
    SetCursorAt(39,56);
    cout<<char(200);
    for(int i=1;i<5;i++) cout<<char(205)<<char(202);
    cout<<char(205)<<char(188);
}
void PrintSizeButtons(int rsize)
{
    SetCursorAt(52,54);
    SetConsoleColor(BGWHITE|BLACK);
    cout<<ULB<<HT<<DC<<HT<<HT<<HT<<DC<<HT<<URB;
    SetCursorAt(52,55);
    SetConsoleColor(BGWHITE|BLACK);
    cout<<VT;
    SetConsoleColor(BGWHITE|DARK_GREEN);
    cout<<"+";
    SetConsoleColor(BGWHITE|BLACK);
    cout<<VT;
    SetConsoleColor(BGWHITE|BLUE);
    cout<<" "<<rsize<<" ";
    SetConsoleColor(BGWHITE|BLACK);
    cout<<VT;
    SetConsoleColor(BGWHITE|RED);
    cout<<"-";
    SetConsoleColor(BGWHITE|BLACK);
    cout<<VT;
    SetCursorAt(52,56);
    SetConsoleColor(BGWHITE|BLACK);
    cout<<DLB<<HT<<UC<<HT<<HT<<HT<<UC<<HT<<DRB;
}
void ClickSizeButtonsP(int rsize)
{
    SetCursorAt(53,55);
    SetConsoleColor(WHITE|BGDARK_GREEN);
    cout<<"+";
    SetConsoleColor(BLACK|BGWHITE);
}
void ClickSizeButtonsM(int rsize)
{
    SetCursorAt(59,55);
    SetConsoleColor(WHITE|BGRED);
    cout<<"-";
    SetConsoleColor(BLACK|BGWHITE);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR CmdLine, int nCmdShow)
{
    SetConsoleTitleW(L"||    ASCII PAINT     ||     By - Kinshuk Vasisht");
    unsigned char Brush = char(219);
    short Rubber = 1;
    GetDefault();
    WORD CurrentFColor=BLACK, CurrentBColor=BGWHITE;
    SetConsoleSize(168,57,0);
    CHAR_INFO cbuf[168*54];
    CHAR_INFO cmem[168*3];
    for(int i=0;i<168*54;i++)
    {
        cbuf[i].Char.AsciiChar=' ';
        cbuf[i].Attributes=CurrentBColor;
    }
    for(int i=0;i<168*3;i++)
    {
        cmem[i].Char.AsciiChar=' ';
        cmem[i].Attributes=CurrentBColor;
    }
    COORD charBufSize = {168,54};
    COORD characterPos = {0,0};
    SMALL_RECT writeArea = {0,0,167,53};
    COORD charBufSize2 = {168,3};
    COORD characterPos2 = {0,0};
    SMALL_RECT writeArea2 = {0,54,167,56};
    WriteConsoleOutput(out,cmem, charBufSize2, characterPos2, &writeArea2);
    PrintPalette();
    PrintBrushes(CurrentFColor,CurrentBColor);
    PrintButtons(68,"SAVE",DARK_GREEN);
    PrintButtons(78,"LOAD",BLUE);
    PrintButtons(88,"QUIT",RED);
    PrintButtons(140,"CLEAR",BLUE);
    PrintButtons(152,"SAVE AS",DARK_GREEN);
    PrintSizeButtons(Rubber);
    SetCursorAt(168,56);
    ShowCursor(0);
    reset:
    ShowCursor(FALSE);
    WriteConsoleOutput(out,cbuf, charBufSize, characterPos, &writeArea);
    bool run=true;
    DWORD ev=0;
    INPUT_RECORD Buf;
    SetConsoleColor(CurrentFColor|CurrentBColor);
    string path = "";
    while(run)
    {
        ReadConsoleInput(in,&Buf,1,&ev);
        switch(Buf.EventType)
        {
        case KEY_EVENT:
            {
                if(Buf.Event.KeyEvent.wVirtualKeyCode==VK_ESCAPE)
                    run=false;
                else if(Buf.Event.KeyEvent.uChar.AsciiChar=='c')
                {
                    for (int i = 0; i < 168 * 54; ++i)
                    {
                        cbuf[i].Char.AsciiChar = ' ';
                        cbuf[i].Attributes=CurrentBColor;
                    }
                    WriteConsoleOutputA(out,cbuf, charBufSize, characterPos, &writeArea);
                }
                else if(Buf.Event.KeyEvent.uChar.AsciiChar=='x')
                {
                    int no;
                    SetConsoleColor(BGWHITE|BLACK);
                    SetCursorAt(100,55);cout<<"Enter a New Color Number -> ";cin>>no;
                    for(int i=0;i<32;i++)
                    {
                        if(ColorPalette[i].first==no&&no<17) CurrentFColor=ColorPalette[i].second;
                    }
                    ClearLog();
                    goto reset;
                }
                else if(Buf.Event.KeyEvent.uChar.AsciiChar=='s')
                {
                    int no;
                    SetConsoleColor(BGWHITE|BLACK);
                    SetCursorAt(100,55);cout<<"Enter a New ASCII Number -> ";cin>>no;
                    Brush = char(no);
                    ClearLog();
                    goto reset;
                }
                break;
            }
        case MOUSE_EVENT:
            {
                if(Buf.Event.MouseEvent.dwMousePosition.Y>=54)
                {
                    if(Buf.Event.MouseEvent.dwMousePosition.Y == 55)
                    {
                        switch(Buf.Event.MouseEvent.dwButtonState)
                        {
                        case FROM_LEFT_1ST_BUTTON_PRESSED:
                            {
                                switch(Buf.Event.MouseEvent.dwMousePosition.X)
                                {
                                case 5:
                                    CurrentFColor = RED;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 7:
                                    CurrentFColor = BROWN;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 9:
                                    CurrentFColor = GREEN;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 11:
                                    CurrentFColor = BLUE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 13:
                                    CurrentFColor = YELLOW;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 15:
                                    CurrentFColor = DARK_GREEN;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 17:
                                    CurrentFColor = DARK_BLUE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 19:
                                    CurrentFColor = DARK_TURQUOISE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 21:
                                    CurrentFColor = TURQUOISE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 23:
                                    CurrentFColor = PINK;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 25:
                                    CurrentFColor = PURPLE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 27:
                                    CurrentFColor = OLIVE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 29:
                                    CurrentFColor = WHITE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 31:
                                    CurrentFColor = BLACK;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 33:
                                    CurrentFColor = GRAY;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 35:
                                    CurrentFColor = DARK_GRAY;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 40:
                                    Brush = BrushPalette[0];
                                    break;
                                case 42:
                                    Brush = BrushPalette[1];
                                    break;
                                case 44:
                                    Brush = BrushPalette[2];
                                    break;
                                case 46:
                                    Brush = BrushPalette[3];
                                    break;
                                case 48:
                                    Brush = BrushPalette[4];
                                    break;
                                case 53:
                                    ClickSizeButtonsP(Rubber);
                                    Sleep(100);
                                    if(Rubber<9)
                                        Rubber++;
                                    else
                                    {
                                        SetCursorAt(100,55);
                                        cout<<"Maximum Size Reached !";
                                        Sleep(1000);
                                        ClearLog();
                                    }
                                    PrintSizeButtons(Rubber);
                                    break;
                                case 59:
                                    ClickSizeButtonsM(Rubber);
                                    Sleep(100);
                                    if(Rubber>1)
                                        Rubber--;
                                    else
                                    {
                                        SetCursorAt(100,55);
                                        cout<<"Minimum Size Reached !";
                                        Sleep(1000);
                                        ClearLog();
                                    }
                                    PrintSizeButtons(Rubber);
                                    break;
                                }
                                if((Buf.Event.MouseEvent.dwMousePosition.X>88)&&(Buf.Event.MouseEvent.dwMousePosition.X<95))
                                {
                                    ClickButton("QUIT",88,WHITE,BGRED);
                                    Sleep(100);
                                    PrintButtons(88,"QUIT",RED);
                                    run = false;
                                }
                                if((Buf.Event.MouseEvent.dwMousePosition.X>141)&&(Buf.Event.MouseEvent.dwMousePosition.X<148))
                                {
                                    ClickButton("CLEAR",140,WHITE,BGBLUE);
                                    Sleep(100);
                                    PrintButtons(140,"CLEAR",BLUE);
                                    for (int i = 0; i < 168 * 54; ++i)
                                    {
                                        cbuf[i].Char.AsciiChar = ' ';
                                        cbuf[i].Attributes=CurrentBColor;
                                    }
                                    WriteConsoleOutputA(out,cbuf, charBufSize, characterPos, &writeArea);
                                }
                                if((Buf.Event.MouseEvent.dwMousePosition.X>153)&&(Buf.Event.MouseEvent.dwMousePosition.X<162))
                                {
                                    cin.clear();
                                    fflush(stdin);
                                    ClickButton("SAVE AS",152,WHITE,BGDARK_GREEN);
                                    Sleep(100);
                                    PrintButtons(152,"SAVE AS",DARK_GREEN);
                                    SetCursorAt(100,55); cout<<"Name : ";getline(cin,path);
                                    Save(cbuf,path+".afi");
                                    ClearLog();
                                }
                                if((Buf.Event.MouseEvent.dwMousePosition.X>78)&&(Buf.Event.MouseEvent.dwMousePosition.X<85))
                                {
                                    cin.clear();
                                    fflush(stdin);
                                    ClickButton("LOAD",78,WHITE,BGBLUE);
                                    Sleep(100);
                                    PrintButtons(78,"LOAD",BLUE);
                                    SetCursorAt(100,55); cout<<"Name : ";getline(cin,path);
                                    if(Exist("Saved ASCII Images\\"+path+".afi"))
                                    {
                                        Load(cbuf,path+".afi");
                                        WriteConsoleOutputA(out,cbuf, charBufSize, characterPos, &writeArea);
                                    }
                                    else
                                    {
                                        SetCursorAt(100,55);
                                        cout<<"File Doesn't Exist!";
                                        Sleep(1000);
                                    }
                                    ClearLog();
                                }
                                if((Buf.Event.MouseEvent.dwMousePosition.X>68)&&(Buf.Event.MouseEvent.dwMousePosition.X<75))
                                {
                                    cin.clear();
                                    fflush(stdin);
                                    ClickButton("SAVE",68,WHITE,BGDARK_GREEN);
                                    Sleep(100);
                                    PrintButtons(68,"SAVE",DARK_GREEN);
                                    if(path != "") SaveinExisting(cbuf,path+".afi");
                                    else
                                    {
                                        SetCursorAt(100,55);
                                        cout<<"Nothing Recently Saved or Loaded!";
                                        Sleep(1000);
                                        ClearLog();
                                    }
                                }
                                break;
                            }
                        case RIGHTMOST_BUTTON_PRESSED:
                            {
                                switch(Buf.Event.MouseEvent.dwMousePosition.X)
                                {
                                case 5:
                                    CurrentBColor = BGRED;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 7:
                                    CurrentBColor = BGBROWN;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 9:
                                    CurrentBColor = BGGREEN;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 11:
                                    CurrentBColor = BGBLUE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 13:
                                    CurrentBColor = BGYELLOW;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 15:
                                    CurrentBColor = BGDARK_GREEN;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 17:
                                    CurrentBColor = BGDARK_BLUE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 19:
                                    CurrentBColor = BGDARK_TURQUOISE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 21:
                                    CurrentBColor = BGTURQUOISE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 23:
                                    CurrentBColor = BGPINK;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 25:
                                    CurrentBColor = BGPURPLE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 27:
                                    CurrentBColor = BGOLIVE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 29:
                                    CurrentBColor = BGWHITE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 31:
                                    CurrentBColor = 0;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 33:
                                    CurrentBColor = BGGRAY;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 35:
                                    CurrentBColor = BGDARK_GRAY;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                }
                                break;
                            }
                        }
                    }
                }
                else
                {
                    if(GetAsyncKeyState(VK_LSHIFT))
                    {

                    }
                    else
                    {
                        int X, Y;
                        if(Buf.Event.MouseEvent.dwMousePosition.X>=168-Rubber && Buf.Event.MouseEvent.dwMousePosition.Y<(54-Rubber))
                        {
                            X = Buf.Event.MouseEvent.dwMousePosition.X-Rubber+1;
                            Y = Buf.Event.MouseEvent.dwMousePosition.Y;
                        }
                        else if(Buf.Event.MouseEvent.dwMousePosition.Y>=54-Rubber && Buf.Event.MouseEvent.dwMousePosition.X<(168-Rubber))
                        {
                            X = Buf.Event.MouseEvent.dwMousePosition.X;
                            Y = Buf.Event.MouseEvent.dwMousePosition.Y-Rubber+1;
                        }
                        else if(Buf.Event.MouseEvent.dwMousePosition.X>=(168-Rubber) && Buf.Event.MouseEvent.dwMousePosition.Y>=(54-Rubber))
                        {
                            X = Buf.Event.MouseEvent.dwMousePosition.X-Rubber+1;
                            Y = Buf.Event.MouseEvent.dwMousePosition.Y-Rubber+1;
                        }
                        else
                        {
                            X = Buf.Event.MouseEvent.dwMousePosition.X;
                            Y = Buf.Event.MouseEvent.dwMousePosition.Y;
                        }
                        switch(Buf.Event.MouseEvent.dwButtonState)
                        {
                        case FROM_LEFT_1ST_BUTTON_PRESSED:
                            cbuf[(Buf.Event.MouseEvent.dwMousePosition.X)+(168*Buf.Event.MouseEvent.dwMousePosition.Y)].Char.AsciiChar=Brush;
                            cbuf[(Buf.Event.MouseEvent.dwMousePosition.X)+(168*Buf.Event.MouseEvent.dwMousePosition.Y)].Attributes=CurrentFColor|CurrentBColor;
                            WriteConsoleOutputA(out,cbuf, charBufSize, characterPos, &writeArea);
                            break;
                        case RIGHTMOST_BUTTON_PRESSED:
                            for(int i=0;i<Rubber;i++)
                            {
                                for(int j=0;j<Rubber;j++)
                                {
                                    cbuf[(X+j)+(168*(Y+i))].Char.AsciiChar = ' ';
                                    cbuf[(X+j)+(168*(Y+i))].Attributes = CurrentBColor;
                                }
                            }
                            WriteConsoleOutputA(out,cbuf, charBufSize, characterPos, &writeArea);
                            break;
                        }
                    }
                }
                break;
            }
        }
    }
    ShowCursor(TRUE);
    SetConsoleColor(BGWHITE|BLACK);
    SetCursorAt(100,55);cout<<"Aborting. Are You Sure? (Y/N) -: ";char key = cin.get();
    if(key=='Y') exit(0);
    else
    {
        ClearLog();
        goto reset;
    }
}
