This is a C program that aims to help me watch what i eat.
I am working this out into a proper CLI application that i'll use on a daily basis.
Right now, you can use this program to:
- Store information about the food you ate. (Name, Description, Type of Meal (main meal, snack, etc), and calories), as well as the total calories for the day.
-- The time each entry is submitted is automatically stored. The program shows the food you ate during the current day automatically.
- Check all entries from previous days and their cumulative caloric value.
- Save your data and come back later.


WHAT I'VE LEARNED: (a whole lot.)
- pointers in practice, safe memory management
- dynamic memory allocation
- custom serialization, file persistance
- unix time, time.h functions
- header files / managing codebase
- CMake, gdb, tmux
- Git / Github


BUILD INSTRUCTIONS:
IF USING WINDOWS: - use Windows Subsystem for Linux to run the program: https://learn.microsoft.com/en-us/windows/wsl/install
- clone repository
- make 'build' directory within repo directory, enter said 'build' directory
- run command 'CMake ..'
- run command 'make'
- you can run the program using ./meal_tracker
