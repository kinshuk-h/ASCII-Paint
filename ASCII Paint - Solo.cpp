#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include<utility>
#include<vector>
#include<windows.h>
#include<thread>

/// Basic Colors - FOREGROUND

#define RED            FOREGROUND_RED|FOREGROUND_INTENSITY
#define BROWN          FOREGROUND_RED
#define GREEN          FOREGROUND_GREEN|FOREGROUND_INTENSITY
#define DARK_GREEN     FOREGROUND_GREEN
#define BLUE           FOREGROUND_BLUE|FOREGROUND_INTENSITY
#define DARK_BLUE      FOREGROUND_BLUE
#define YELLOW         FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY
#define TURQUOISE      FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY
#define DARK_TURQUOISE FOREGROUND_GREEN|FOREGROUND_BLUE
#define PINK           FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY
#define PURPLE         FOREGROUND_BLUE|FOREGROUND_RED
#define OLIVE          FOREGROUND_GREEN|FOREGROUND_RED
#define WHITE          FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY
#define GRAY           FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE
#define DARK_GRAY      FOREGROUND_INTENSITY
#define BLACK          0

/// Basic Colors - BACKGROUND

#define BGRED            BACKGROUND_RED|BACKGROUND_INTENSITY
#define BGBROWN          BACKGROUND_RED
#define BGGREEN          BACKGROUND_GREEN|BACKGROUND_INTENSITY
#define BGDARK_GREEN     BACKGROUND_GREEN
#define BGBLUE           BACKGROUND_BLUE|BACKGROUND_INTENSITY
#define BGDARK_BLUE      BACKGROUND_BLUE
#define BGYELLOW         BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_INTENSITY
#define BGTURQUOISE      BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY
#define BGDARK_TURQUOISE BACKGROUND_GREEN|BACKGROUND_BLUE
#define BGPINK           BACKGROUND_BLUE|BACKGROUND_RED|BACKGROUND_INTENSITY
#define BGPURPLE         BACKGROUND_BLUE|BACKGROUND_RED
#define BGOLIVE          BACKGROUND_GREEN|BACKGROUND_RED
#define BGWHITE          BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_INTENSITY
#define BGGRAY           BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_BLUE
#define BGDARK_GRAY      BACKGROUND_INTENSITY

using namespace std;

HANDLE out=GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE in =GetStdHandle(STD_INPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;
WORD ORIGINAL;
HWND CONSOLE;
RECT R;
COORD CONSOLECOORD;
///Single Character Width
const double cW = 837.0/80.0;
///Single Character Height
const double cH = 523.0/30.0;

void GetDefault()
{
    GetConsoleScreenBufferInfo(out,&csbi);
    ::ORIGINAL=csbi.wAttributes;
    ::CONSOLE=GetConsoleWindow();
    GetWindowRect(CONSOLE, &R);
    R.left=0;
    R.top=0;
    CONSOLECOORD.X=0;
    CONSOLECOORD.Y=0;
}

void SetConsoleColor(WORD COLOR)
{
    SetConsoleTextAttribute(out,COLOR);
}

void SetConsoleSize(int w, int h, int rl=350)
{
    R.left=rl;
    R.right=R.left+w;
    R.top=0;
    R.bottom=R.top+h;
    MoveWindow(CONSOLE,R.left,R.top,w,h,FALSE);
    COORD BufferCoord = {SHORT(w),SHORT(h+10)};
    SetConsoleScreenBufferSize(out,BufferCoord);
    SMALL_RECT SIZE = {0,0,SHORT(w-1),SHORT(h-1)};
    SetConsoleWindowInfo(out,TRUE,&SIZE);
}

void SetCursorAt(int X,int Y)
{
    CONSOLECOORD.X=X;
    CONSOLECOORD.Y=Y;
    SetConsoleCursorPosition(out,CONSOLECOORD);
}

vector<pair<int,WORD>> ColorPalette = {{1,RED},{2,BROWN},{3,GREEN},{4,BLUE},{5,YELLOW},{6,DARK_GREEN},
                                       {7,DARK_BLUE},{8,DARK_TURQUOISE},{9,TURQUOISE},{10,PINK},
                                       {11,PURPLE},{12,OLIVE},{13,WHITE},{14,BLACK},{15,GRAY},{16,DARK_GRAY}};

vector<unsigned char> BrushPalette = {219,178,177,176,' '};

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
    ClearLog();
    cout<<"Size? - ";int sx,sy;cin>>sx>>sy;
    fstream fout;
    fout.open(("Saved ASCII Images\\"+path).c_str(),ios::out|ios::binary);
    if(sx == 0 || sy == 0)
    {
        for(int i=0;i<168*54;i++)
            fout.write((char*)&cbuf[i],sizeof(cbuf[i]));
        return;
    }
    for(int i=0;i<sy;i++)
    {
        for(int j=0;j<sx;j++)
        {
            fout.write((char*)&cbuf[(168*i)+j],sizeof(CHAR_INFO));
        }
    }
    fout.close();
}
void Save(CHAR_INFO cbuf[168*54],string path)
{
    if(!Exist(path))
    {
        ClearLog();
        cout<<"Size? - ";int sx,sy;cin>>sx>>sy;
        fstream fout;
        fout.open(("Saved ASCII Images\\"+path).c_str(),ios::out|ios::binary|ios::trunc);
        if(sx == 0 || sy == 0)
        {
            sx = 168; sy = 54;
            fout.write(reinterpret_cast<char*>(sx),sizeof(int));
            fout.write(reinterpret_cast<char*>(sy),sizeof(int));
            for(int i=0;i<168*54;i++)
                fout.write((char*)&cbuf[i],sizeof(cbuf[i]));
            return;
        }
        fout.write(reinterpret_cast<char*>(&sx),sizeof(int));
        fout.write(reinterpret_cast<char*>(&sy),sizeof(int));
        for(int i=0;i<sy;i++)
        {
            for(int j=0;j<sx;j++)
            {
                fout.write((char*)&cbuf[(168*i)+j],sizeof(CHAR_INFO));
            }
        }
        fout.close();
    }
    else
    {
        ClearLog();
        cout<<"Overwrite ? (Y/N) - ";char ch = cin.get();
        if(ch == 'Y' || ch == 'y')
        {
            ClearLog();
            cout<<"Size? - ";int sx,sy;cin>>sx>>sy;
            fstream fout;
            fout.open(("Saved ASCII Images\\"+path).c_str(),ios::out|ios::binary);
            if(sx == 0 || sy == 0)
            {
                sx = 168; sy = 54;
                fout.write(reinterpret_cast<char*>(sx),sizeof(int));
                fout.write(reinterpret_cast<char*>(sy),sizeof(int));
                for(int i=0;i<168*54;i++)
                    fout.write((char*)&cbuf[i],sizeof(cbuf[i]));
                return;
            }
            for(int i=0;i<sy;i++)
            {
                for(int j=0;j<sx;j++)
                {
                    fout.write((char*)&cbuf[(168*i)+j],sizeof(CHAR_INFO));
                }
            }
            fout.close();
        }
    }
}
void Load(CHAR_INFO cbuf[168*54],string path)
{
    ClearLog();
    fstream fin; int sx, sy;
    fin.open(("Saved ASCII Images\\"+path).c_str(),ios::in|ios::binary);
    fin.read(reinterpret_cast<char*>(&sx),sizeof(int));
    fin.read(reinterpret_cast<char*>(&sy),sizeof(int));
    //MessageBox(NULL,(to_string(sx)+" "+to_string(sy)).c_str(),"Size",MB_OK);
    for(int i=0;i<sy;i++)
    {
        for(int j=0;j<sx;j++)
        {
            fin.read((char*)&cbuf[(168*i)+j],sizeof(CHAR_INFO));
        }
    }
    if(sx<168 || sy<54)
    {
        for(int i=sx;i<168;i++)
        {
            for(int j=0;j<sy;j++)
            {
                cbuf[(168*j)+i].Char.AsciiChar = ' ';
                cbuf[(168*j)+i].Attributes = BLACK;
            }
        }
        for(int i=0;i<168;i++)
        {
            for(int j=sy;j<54;j++)
            {
                cbuf[(168*j)+i].Char.AsciiChar = ' ';
                cbuf[(168*j)+i].Attributes = BLACK;
            }
        }
    }
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
void PrintPalette()
{
    SetCursorAt(9,54);
    SetConsoleColor(BLACK|BGWHITE);
    cout<<char(201);
    for(int i=1;i<32/2;i++) cout<<char(205)<<char(203);
    cout<<char(205)<<char(187);
    SetCursorAt(9,55);
    int i=0;
    cout<<char(186);
    for(i=0;i<16;i++)
    {
        SetConsoleColor(ColorPalette[i].second);
        cout<<char(219);
        SetConsoleColor(BLACK|BGWHITE);
        cout<<char(186);
    }
    SetCursorAt(9,56);
    cout<<char(200);
    for(int i=1;i<33/2;i++) cout<<char(205)<<char(202);
    cout<<char(205)<<char(188);
}
void PrintBrushes(WORD CF,WORD CB = BGWHITE)
{
    SetCursorAt(49,54);
    SetConsoleColor(BGWHITE|BLACK);
    cout<<char(201);
    for(int i=1;i<5;i++) cout<<char(205)<<char(203);
    cout<<char(205)<<char(187);
    SetCursorAt(49,55);
    int i=0;
    cout<<char(186);
    for(i=0;i<5;i++)
    {
        SetConsoleColor(CF|CB);
        cout<<BrushPalette.at(i);
        SetConsoleColor(BLACK|BGWHITE);
        cout<<char(186);
    }
    SetCursorAt(49,56);
    cout<<char(200);
    for(int i=1;i<5;i++) cout<<char(205)<<char(202);
    cout<<char(205)<<char(188);
}

void Play()
{
    //PlaySound("Angel_Theme_Song.wav",nullptr,SND_ASYNC|SND_LOOP);
}

void Paint()
{
    SetConsoleTitleW(L"||    ASCII PAINT     ||     By - Kinshuk Vasisht");
    unsigned char Brush = char(219);
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
                else if(Buf.Event.KeyEvent.uChar.AsciiChar=='z')
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
                    char no;
                    SetConsoleColor(BGWHITE|BLACK);
                    SetCursorAt(100,55);cout<<"Enter a New Brush (ASCII Number) -> ";cin>>no;
                    Brush = no;
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
                                case 10:
                                    CurrentFColor = RED;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 12:
                                    CurrentFColor = BROWN;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 14:
                                    CurrentFColor = GREEN;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 16:
                                    CurrentFColor = BLUE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 18:
                                    CurrentFColor = YELLOW;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 20:
                                    CurrentFColor = DARK_GREEN;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 22:
                                    CurrentFColor = DARK_BLUE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 24:
                                    CurrentFColor = DARK_TURQUOISE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 26:
                                    CurrentFColor = TURQUOISE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 28:
                                    CurrentFColor = PINK;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 30:
                                    CurrentFColor = PURPLE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 32:
                                    CurrentFColor = OLIVE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 34:
                                    CurrentFColor = WHITE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 36:
                                    CurrentFColor = BLACK;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 38:
                                    CurrentFColor = GRAY;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 40:
                                    CurrentFColor = DARK_GRAY;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 50:
                                    Brush = BrushPalette[0];
                                    break;
                                case 52:
                                    Brush = BrushPalette[1];
                                    break;
                                case 54:
                                    Brush = BrushPalette[2];
                                    break;
                                case 56:
                                    Brush = BrushPalette[3];
                                    break;
                                case 58:
                                    Brush = BrushPalette[4];
                                    break;
                                }
                                if((Buf.Event.MouseEvent.dwMousePosition.X>88)&&(Buf.Event.MouseEvent.dwMousePosition.X<95))
                                    run = false;
                                if((Buf.Event.MouseEvent.dwMousePosition.X>141)&&(Buf.Event.MouseEvent.dwMousePosition.X<148))
                                {
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
                                    SetCursorAt(100,55); cout<<"Name : ";getline(cin,path);
                                    Save(cbuf,path+".afi");
                                    ClearLog();
                                }
                                if((Buf.Event.MouseEvent.dwMousePosition.X>78)&&(Buf.Event.MouseEvent.dwMousePosition.X<85))
                                {
                                    cin.clear();
                                    fflush(stdin);
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
                                    if(path != "") SaveinExisting(cbuf,path+".afi");
                                    else
                                    {
                                        SetCursorAt(100,55);
                                        cout<<"Nothing Recently Saved or Loaded!";
                                        Sleep(1000);
                                        ClearLog();
                                    }
                                    ClearLog();
                                }
                                break;
                            }
                        case RIGHTMOST_BUTTON_PRESSED:
                            {
                                switch(Buf.Event.MouseEvent.dwMousePosition.X)
                                {
                                case 10:
                                    CurrentBColor = BGRED;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 12:
                                    CurrentBColor = BGBROWN;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 14:
                                    CurrentBColor = BGGREEN;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 16:
                                    CurrentBColor = BGBLUE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 18:
                                    CurrentBColor = BGYELLOW;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 20:
                                    CurrentBColor = BGDARK_GREEN;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 22:
                                    CurrentBColor = BGDARK_BLUE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 24:
                                    CurrentBColor = BGDARK_TURQUOISE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 26:
                                    CurrentBColor = BGTURQUOISE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 28:
                                    CurrentBColor = BGPINK;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 30:
                                    CurrentBColor = BGPURPLE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 32:
                                    CurrentBColor = BGOLIVE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 34:
                                    CurrentBColor = BGWHITE;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 36:
                                    CurrentBColor = 0;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 38:
                                    CurrentBColor = BGGRAY;
                                    PrintBrushes(CurrentFColor,CurrentBColor);
                                    break;
                                case 40:
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
                        int coordpos = Buf.Event.MouseEvent.dwMousePosition.X+(168*Buf.Event.MouseEvent.dwMousePosition.Y);
                        switch(Buf.Event.MouseEvent.dwButtonState)
                        {
                        case FROM_LEFT_1ST_BUTTON_PRESSED:
                            ClearLog();
                            cbuf[coordpos].Char.AsciiChar=Brush;
                            cbuf[coordpos].Attributes=CurrentFColor|CurrentBColor;
                            WriteConsoleOutputA(out,cbuf, charBufSize, characterPos, &writeArea);
                            SetCursorAt(100,55);
                            cout<<Buf.Event.MouseEvent.dwMousePosition.X<<" "<<Buf.Event.MouseEvent.dwMousePosition.Y;
                            break;
                        case RIGHTMOST_BUTTON_PRESSED:
                            cbuf[coordpos].Char.AsciiChar=char(32);
                            cbuf[coordpos].Attributes=CurrentBColor;
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
int main()
{
    thread t1(Play);
    thread t2(Paint);
    t1.join(); t2.join();
}
