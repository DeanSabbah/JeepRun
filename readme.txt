Dean Sabbah
101199120

The game was developed in Windows 10

Part 1:
	Created new function in player_game_object called update_velocity(int) that takes an int that corresponds to direction
	This function then sets the dir variable based on the given int and then evaluates if the player is moving at max speed
	The velocity is used to update the player position in the player object's Update(float delta_time) function
Part 2/3:
	In game.cpp, the game checks if the 'F' key is pressed. If so, it starts a cooldown timer in the Player object and spawns a new ProjectileGameObject
	The Fireball sprite is used for the projectile
	On initialization of the projectile, a timer starts for 5 seconds. If the projectile still exits after the timer is over, it is removed from the game.
	Source/Header files for ProjectileGameObject class: projectile_game_object.cpp/h
Part 4:
	Implemented for assignment 2, updated to account for the larger game area
Part 5:
	Created a new ProjectileObject class that acts as an interface for game objects that collide.
	When new collidable game objects are spawned, they have a 'type' parameter that determines if they use ray-circle or circle-circle collision
	Projectiles use ray-circle collision.
	A general collide() function exists in the ProjectileObject class to handle all types of collision automatically.
	Source/Header files for CollisionObject class: collision_game_object.cpp/h
Part 6:
	In game.cpp, the game::SetupGameWorld() function is updated to spawn 9 tiles in a square pattern instead of 1.
	The Render() function has been updated to add a translation matrix to the view_matrix that takes into account the players position.
Part 7:
	In game_object.h, SetScale has been changed to take a vec2 instead of a float and the scale param has been changed to a vec2.
	In the render function, the scaling_matrix now uses scale_.x and scale_.y to build the matrix.
	The GameObject constructor uses a vec2 to initialize the scale_ variable.
	When spawning projectile game objects, the scale of those objects is set to (1.2f, 0.4f)
Part 8:
	In the GameObject class, a new variable, ghost_ has been added + setters and getters.
	A new shader fragment has been added to render a sprites pixels in grayscale.
	When ghostmode is active (ghost_ == true), the active_shader variable is updated to the grayscale shader.
	Items in ghost mode do not disappear.
	CollectableGameObjects that are collected now go into ghost mode instead of disappearing.

BUGS:
	Enemies will snap to their new elliptical patrol path because the center of it is it's current location (when intercepting)
	Can't strafe while pressing w at max speed, can't move forwards/backwards while strafing at max speed

SOURCES:
	Spaceship sprites: https://opengameart.org/content/spaceships-32x32
	Licence: CC-BY-40
	
	Explosion sprite: https://commons.wikimedia.org/wiki/File:Explosion-155624_icon.svg
	Licence: CC0

	Orbs sprite: https://opengameart.org/content/pixel-orbs
	Licence: CC0
	
	Fireball sprite: https://nyknck.itch.io/pixelarteffectfx017
	No licence

	Sun with shades: https://opengameart.org/content/sun-with-shades
	Licence: CC0