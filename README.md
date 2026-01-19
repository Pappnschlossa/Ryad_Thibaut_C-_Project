# <img src="icon.png" width="32" style="image-rendering: pixelated;"/> スイカ Game (Watermelon Game)

スイカ Game, that you may know under the name Watermelon Game is a game where you drop fruits in a basket. If the same type of fruits touch each other, they merge into a bigger fruit.

Will you manage to get and combine two Watermelons ?

Clone the repo with ``git clone https://github.com/Pappnschlossa/Ryad_Thibaut_C-_Project.git``, and run the main file to try it!

This project was coded in C++ implementing a Qt interface.

## User Input

After running main, the user clicks on the screen wherever he wants to place his next fruit.\
The type of the next fruit is indicated on the top right of the screen.

## Elements of this project we are proud of

- The resizable window (yes it is resizable, try it yourself !)
- Stable physics for a game that is pretty demanding in terms of ball to ball collision. More specifically when balls are merging together.
- A simple yet satisfying UI
- A catchy gameplay loop.

## Problems we had while working on this project

- Printing with CLion did not work as intended, when running main. We later found out that launching the app in Debug mode fixes this.
- The equations as written in the paper led to a really unstable physic engine, we had to modify and test a lot to make it more stable.
- Setting up the compiler for Clion was tricky.
