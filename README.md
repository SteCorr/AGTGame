Advanced Game Technology game Design

This document will have a description of the game I intend to make for my AGT assignment.
My game will be an action adventure rogue like game in which the player will have to find their way though 
mazes to gather artefact. These artefacts are then used to exit the maze and progress to the next level. 
The game will have enemies scattered throughout the maze that will attack the player as they travel through the maze.
The player will also have a basic combat system that can be used to attack the enemy objects. The player object will
have the ability to travel around the game environment and the enemy object will follow the player object when in range
of the player object. The player will also have the ability to pick up power ups; these will range from powerful weapon 
to speed up grades. The mazes for the game will be procedurally generated.

The collision will be processed using the OcTree method of collision detection. The game will include.
The collision will be used to determine if a player has hit and enemy and vice versa, when this had the 
player or enemy will lose health. Collision will also be used for the pickup of object, if the player collided 
with a packable object the player will pick this object up, this is only if the player has room for the object in
the inventory. The player will also only be allowed to attack an enemy when they have a weapon to do so. 

All object class (e.g. player, enemy and packable objects) will derive form a base object class. 
This is because all this class will have similar functionality.  
