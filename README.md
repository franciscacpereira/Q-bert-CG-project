![logo-3](https://github.com/user-attachments/assets/339e4c1e-3688-4155-af72-30ee97d5ac54)

This game was developed within the scope of an academic project for the subject of Computer Graphics. The goal was to create a similar version to an original retro game, being Q*bert the one I chose. 

Disclaimer
: The requirements for the project stated that the game must only resemble the original in some aspects, and other more intricate ones may not me implemented due to the amount of time available for completion. Hence why my version is missing some key ingredients, such as the snake that follows the player around or the floating disks that allow it to return to the top of the pyramid.

## Installation Guide

The language used was C++ along with the toolkit *OpenFrameworks*. The IDE I used was *Visual Studio*. However, I know that *VS Code* can be used, aswell as other IDE's, which I would recommend the use of considering the poor experience I has with VS.

1. Follow the instruction on the official website of [openframeworks](https://openframeworks.cc/download/)
   * Note 1: Choose version 0.12.0
   * Note 2: OF doesn't need to be installed on the computer, all you need is the ***of_v0.12.0_vs_release*** folder in your system (the vs part means Visual Studio, for anyone with Xcode that part will be different)
  
2. To create a new project go to ***of_v0.12.0_vs_release\projectGenerator*** and execute the ***projectGenerator.exe*** file
3. Choose the path with ***\of_v0.12.0_vs_release\apps\myApps*** since that will be the folder in which all projects will be automatically stored
4. Choose the platform/IDE accordingly
5. To add pre-made code (such as the one I have in this repository) to a new project you must first open the **.sln** file inside the project folder
6. Inside the opened IDE (this instructions only apply to VS since I don't know how the others may work) delete all existing files in the **src** folder such as **ofApp.cpp**
7. Drag (in the file explorer) the source code into the **src** folder
8. Again, inside the IDE, right click inside the **src** folder and select ***add existing item*** and choose all the code added before in step 7.


## Game Visuals

The game has a start screen explaining the basic key commands

![opening-screen](https://github.com/user-attachments/assets/7c50f2bf-8d40-4017-8ad6-4465ae1ee173)

It also has 3 different view points. Each one can be changed during run time via the 'V' key.

![game-start-v1](https://github.com/user-attachments/assets/984d5e17-f739-45dd-922e-a2c82754d61e)
![game-start-v2](https://github.com/user-attachments/assets/664f201e-0e24-4a4e-9d3e-05083138319d)
![game-start-v3](https://github.com/user-attachments/assets/16b486cd-e6ce-4fb7-9735-a76edd979c9f)

Here are some extra images of the game while being played.

![game-running-v1](https://github.com/user-attachments/assets/6cd8efce-fa00-4456-a0b3-d74db573df62)
![level1-v1](https://github.com/user-attachments/assets/942ffea4-b121-4a10-bd88-d8e14ca0aace)
![game-over-v1](https://github.com/user-attachments/assets/43b12d41-e4c9-4e4a-b27a-6e68b024b769)
![game-running-v3](https://github.com/user-attachments/assets/b141bcd5-848b-4b32-a8de-adc53de227d0)
![game-won-v2](https://github.com/user-attachments/assets/2ae77d8a-9dd7-4adb-a75e-1ac816d2d33a)




