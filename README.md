# God Of Wine

## Story

God of Wine is a game made in Unreal 5.1 for a collaborative challenge in CG Spectrum. 

The goal of the challenge was to create a low-poly level of maximum 20x20x20.
My team was formed by a programmer (me), a game designer and two modelers.

The game is set in Ancient Greece. You are in a temple dedicated to Dionysus, god of wine.
In order to receive his blessing and party all night long with your friends you have to sacrifice some grapes to his altar.

But you don't have any grapes. The altar is missing. And you hear a song even though nobody's playing the lyres.

Try solving this mystery so you can have fun with your friends!

[Showcase video](https://youtu.be/DXi3snd9ibQ)

## Code

The project inherits from the Third Person Shooter template of Unreal Engine. 

Main character has been extended to add functionality in order to interact with objects on the map.
An interactable object can also be an objective. This means that when the player interacts with an object he completes an objective.

Three main interactable objects has been created:

* Lattice, to collect grapes
* Lyre, to play a music
* Statue, to receive the blessing

Lyres can be grouped in a puzzle. You have to play the lyres in a certain order in order to solve the puzzle.

An ObjectiveSubsystem has been created in order to control the flow of the game and display info to the player about what has been done so far and what is the current objective.
When an objective is active a player can interact just with the interactable associated to the objective. 

Objectives have been implemented designer-friendly, so they can be easily modified by game designer. 
You can change the order of objectives and trigger additional actions when a single objective (or all objectives) has been completed by using Blueprint.
You can also bind to various events exposed by the system to display information on the HUD or trigger other actions.

You can create a new interactable object by implementing this interface:

```cpp
IInteractable
```

An interactable can be also an objective by implementing this interface:
```cpp
IObjective
```

You can also group objectives by instancing this class on the map and configuring it from Blueprint:
```cpp
AObjectiveGroup
```



## Credits

Game designing by [**Dimitrios Elaiotriviaris**](https://www.linkedin.com/in/dimitrios-elaiotriviaris-b42956137/) 

Modeling by **Tanguy Chennaux** and **Dominique Alzate**

