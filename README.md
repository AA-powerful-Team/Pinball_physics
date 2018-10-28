
# ROLLING X PINBALL

Project for Physics II subject. The goal is to recreate a pinball game with BoxD library. 

This project has been done by two students of CITM - UPC (Barcelona, Spain). 

* [Github repository](https://github.com/TheArzhel/Pinball_physics)  

## About the game 

The original pinball game can be found [here] (http://www.freewebarcade.com/game/rollin-x-pinball/index.php?act=Arcade&do=newscore).

 ## Installation instructions 

Download the Zip file and extract it. Open the folder and double click on the executable (.exe) 

_IMPORTANT: do not modify, change or add any folder or file, or else the game may not work correctly._ ## Controls Player controls: 

- RIGHT FLIPPER: Right arrow key 
- LEFT FLIPPER: Right left key 
- LAUNCH BALL: Down arrow key (hold to charge kicker)

General/developer controls: 

- EXIT GAME: ESC key or click close button in window 
- DEBUG MODE & DRAW OBJECTS: F1 key 
- CREATE BALL: 1 key 
- MOVE BALL: click and drag the ball around while on debug mode
- A: restart the game 

**CAUTION: the game is not thought to be played in debug mode. Some bugs may appear while on debug mode. 

## How to play 

The goal of the game is score as many points as you can before losing four balls. 

You may score by: 
* Impacting one of the two circle bouncers. 
* Impacting one of the two triangular bouncers. 
* Impacting the blue bouncer after the tunnel. 
* Going in the 2x or 4x entrance, multiplying your score by the  
same amount. 
* Entering the Ball lock ramp. 


# Combos 

* Going through large tunnel on the left part of the screen, activating all lights. 
* Touching the 3 sensor right of the circle bouncers. 
* Touching the 3 above sensors that lead to the bouncers. 
* Touching the 3 above sensors that lead to the bouncers, plus the uppermost sensor. 
* Touching the upper sensor and the one in the middle of the stage, connecting the upper and lower part. 
* Touching the 5 small sensors in the lower part of the board. 

**CAUTION: losing the ball and touching the sideways sensors will rest you points.

Score and balls left can be seen on window title.

## Game Differences 

* Ball doesn't disappear when entering the 2x and 4x ramps or add falling velocity. 
* Kickers when the ball tries to fall in the sideways rails. 
* No instructions shown. 
* Score differs from the original. 
* Lights do not disappear with time, just when ball falls or the combo is performed. 

## Team members 

_Adrian Font Romero Github account:_ 
* [Github account](https://github.com/AdrianFR99) 

_Andrés Ricardo Saladrigas Pérez Github account:_ 
* [Github account](https://github.com/TheArzhel) 


## Tools used 
* Microsoft Visual Studio 2017 
* Language: C++ * Graphics and audio: SDL
2.0.4 
* Physics: Box2D 
* Code repository: GitHub 
* Others: Adobe Photoshop and Audacity 


### Disclaimer

All sprites and sounds are property of the games creator