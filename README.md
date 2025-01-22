![logo-3](https://github.com/user-attachments/assets/339e4c1e-3688-4155-af72-30ee97d5ac54)

This game was developed within the scope of an academic project for the subject of Computer Graphics. The goal was to create a similar version to an original retro game, being Q*bert the one I chose. 

Disclaimer
: The requirements for the project stated that the game must only resemble the original in some aspects, and other more intricate ones may not me implemented due to the amount of time available for completiion. Hence why my version is missing some key ingredients, such as the snake that follows the player around or the floating disks that allow it to return to the top of the pyramid.

## Instalation Guide

The language used was C++ along with the toolkit *OpenFrameworks*. The IDE I used was *Visual Studio*. However, I know that *VS Code* can be used, aswell as other IDE's, which I would recommend the use of considering the poor experience I has with VS.

1. Follow the instruction on the official website of [openframeworks](https://openframeworks.cc/download/)
   * Note 1: Choose version 0.12.0
   * Note 2: OF doesn't need to be installed on the computer, all you need is the ***of_v0.12.0_vs_release*** folder in your system (the vs part means Visual Studio, for anyone with Xcode or Linux that part will be different)
  
2. To create a new project go to ***of_v0.12.0_vs_release\projectGenerator*** and execute the ***projectGenerator.exe*** file
3. Choose the path with ***\of_v0.12.0_vs_release\apps\myApps*** since that will be the folder in which all projects will be automatically stored
4. Choose the platform/IDE accordingly
5. To add pre-made code (such as the one I have in this repository) to a new project you must first open the **.sln** file inside the project folder
6. Inside the opened IDE (this instructions only apply to VS since I don't know how the others may work) delete all existing files in the **src** folder such as **ofApp.cpp**
7. Drag (in the file explorer) the source code into the **src** folder
8. Again, inside the IDE, right click inside the **src** folder and select ***add existing item*** and choose all the code added before in step 7.
