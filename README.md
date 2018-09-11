# ASCII-Paint
ASCII Paint-Windows is a simple Paint Program which allows you to draw images using a character as a Brush. Just draw images like you do in any other paint program. You may change Colors, Set a Shade, Save Your Sketch, And Load it any other Time! There are Buttons for the Same, accessible by clicking.

## Program Details :

```
Made By         -    Kinshuk Vasisht
Version         -    1.2
Status          -    0xFFFFFF (No Existing Bugs known)
Features        -    Draw 8-Bit Images, Save them to .afi (ASCII Format Image)
                     Files, and Load Them Later. Make Images Colorful with 
                     16 Predefined Colors and Shade characters.
Overloads       -    None
Functions       -    SetCursorAt(), SetConsoleColor(),SetConsoleSize(), GetDefault(),
                     ClearLog(), Exist(), Load(), PrintBrushes(), 
                     SaveinExisting(), PrintButtons(),PrintPalette(), Save(), 
Main Data Type  -    WORD (In COLORS) & CHAR_INFO 
Templates       -    None.
Macros          -    None.
#defines        -    FOREGROUND and BACKGROUND Colors
Headers         -    <iostream>, <cstdlib>, <fstream>, <utility>, <vector>,
                     <windows.h>, <string>
```

## ASCII FORMATTED IMAGES : '.afi' 
ASCII Formatted Images are nothing but binary files containing the logical color values of the units at the screen. These are specific
to the ASCII Paint Program.

## Features :
- **Drawing using a Set Brush** -  The default Brush is char 219 (FULL BLOCK), but can be changed by Pressing 's' (without CAPS, just the key) and entering a new character or its ASCII Number.
- **Using an Eraser**           -  The eraser is accessible by simply right-clicking on the area where you wish to erase the pixel from. The default color of the eraser is the color of the Background, and is changeable.
- **Changing Colors**           -  The Colors can be changed by left clicking any color in the Color Palette. To change the eraser's color, Right Click on the color instead. Note that changing the eraser's color will change the background color when you Clear the Screen.
- **Clearing the Screen**       -  The screen can be cleared by simply pressing the 'c' key or Pressing the Clear Button Displayed alongside the Save As Button. If you Right-Click on a Color, that color will be set as the default Background Color and using the clear option will then change the background Color - for the eraser to work as it should.
- **Changing the Rubber Size**  - The size of the Rubber is alterable, and can be changed by Pressing + or – Buttons on the Screen. The Current Size, in Blocks, is displayed alongside in the middle. The max size is 9 and the min size is 1.
- **Changing Shades**           -  The shades of the Pixel can be changed to a lighter BLOCK character. To change the color, simply click of the shade in the box. The First and the Last boxes indicate The Current Foreground and Background Color Respectively.
- **Saving a Picture**          -  The Picture can be saved as a .afi image by clicking on the SAVE AS Button. After clicking on the button, enter a valid name and Press enter. The SAVE Button is just for saving the current file loaded or recently saved to the system. If you haven't used the SAVE AS or LOAD operations before, you can't use SAVE (As is doesn't require PATH, nor asks for overwrite).
- **Loading a Picture**         -  The Picture can be loaded by pressing the LOAD Button, and entering a Valid Filename. If the file does not exist, It will return an error.
- **Exiting from the Program**  -  The Program can be closed by pressing QUIT, or pressing ESC Key. The User then has to confirm the quit() operation by pressing Y.


## Prerequisites:

Before using the program, the user must create a new directory - 'Saved ASCII Images' - in the directory where the program is being stored & used. A sample directory is Supplied with the Program.

