# space_invaders
![Space_Invaders](https://media.es.wired.com/photos/643859cbf381a957088482dc/master/w_1600,c_limit/space-invaders-atari-2600.png)

[Game information](https://es.wikipedia.org/wiki/Space_Invaders)

## ***Character_list***

* Tank
* Enemies
* Wall

### ***Character´s Description***

***A player will control a tank by means of a lever and a button, the tank's mission is to destroy the ships before they reach the ground, avoiding shots from the same ships. All enemies will be controlled by an AI whose mission is to eliminate the player, who will have 3 lives. Once there are few ships left, the remaining ships will increase their speed.***

#### ***SFML library***

***SFML, or Simple and Fast Multimedia Library, is a software development library for C++ that makes it easy to create multimedia applications and video games. Below are the main features and uses of SFML:***

* 2D Graphics: Provides functions for drawing shapes, text, images and sprites, allowing you to create 2D graphics easily and efficiently.

* Audio: Supports the playback of sounds and music in various formats. Includes functionality to manipulate volumes, loop play, and manage multiple sound effects simultaneously.

* Windows: Allows the creation and management of windows, and facilitates the integration of OpenGL for more advanced graphics. Supports management of window events such as closing, resizing, and changing focus.

* User input: Provides an interface to handle keyboard, mouse and joystick input, allowing the creation of rich and dynamic interactions.

* Network: Includes functions for network communication using TCP and UDP, making it easier to create applications that require connectivity, such as multiplayer games.

* System: Provides utilities for managing time, threads, and files, helping to create more complex and efficient applications.

***SFML is appreciated for its simplicity and ease of use, making it ideal for both beginner developers and those looking for a lightweight and powerful library for multimedia projects. The GitHub community actively contributes to the development of SFML, providing improvements, reporting bugs, and creating additional extensions and tools that enrich the library's functionality.***

***In summary, SFML is a versatile and efficient tool for developing multimedia applications and video games, providing a wide range of functionalities with an intuitive and easy-to-use interface.***

##### ***Game instructions.***

* The player will have to destroy each ship in order to win.

* The player will have 3 lives, which will decrease if the player is hit by the enemy bullet. Once the player is hit by 3 bullets, the game will end and the message will appear in the game terminal.

* Both the player and the enemy ships will only be able to move from right to left, the player's controls will be the arrows on their device's keyboard, to shoot will be the space key.

* If the player manages to shoot his enemy, he will be able to shoot another bullet. If the bullet does not attack an enemy, the player will have to wait for the bullet to disappear before being able to attack again.

###### ***How to compile the program.***

***If you want to compile the program you will only have to put in the terminal: make runmain***