# MazeRetreat
## Table of content
<details>
  <summary>Table of Content</summary>
  <ol>
    <li>
      <a href="#summary">Summary</a>
    </li>
    <li>
    <a href="#maze-generation">Maze Generation</a>
    </li>
      <li>
    <a href="#core-features">Core Features</a>
    </li>
    <li>
    <a href="#gameplay">Gameplay</a>
    </li>
    <li>
    <a href="#Demo">Demo</a>
    </li>
    <li>
    <a href="#contact">Contact</a>
    </li>
  </ol>
</details>

# Summary
This is my last project of my first year of gme programming at ISART DIGITAL Montreal. The objective was to reproduce a game like "Spectrum Retreat". The hard skills objectives were : collisions, render opacity, win condition, fluidity, UI, sound, lights...

# Maze Generation
Every instance of the game will have a different maze generation. That's because i'm musing an algorithm that creates seed depending on the window clock. To create mazes i use an algorithm that goes through every cell and erase the right wall, the up wall or both depending on the path that it does. Here is a snippet of the code : 

```cpp

		///If we still have index
		if (!closeOne.empty())
		{
			int iteration = closeOne.size();

			///For all the index we have
			for (int i = 0; i < iteration; i++)
			{
				///Take a random number
				int indices = std::rand() % closeOne.size();

				///If the radom number is too big just -1
				if (indices == closeOne.size())
					indices--;

				///If the random index we had is in front of us, our upWall is set to false and we call back the function cause we're now on another cell
				if (closeOne[indices].first == iIndex + 1 && !CellArray[iIndex + 1][jIndex].visited)
				{
					CellArray[iIndex][jIndex].Up_Wall = false;
					create_Maze_r(closeOne[indices].first, closeOne[indices].second, 0, seed);
				}

				///If the random index we had is on our right, our RightWall is set to false and we call back the function cause we're now on another cell
				else if (closeOne[indices].second == jIndex + 1 && !CellArray[iIndex][jIndex + 1].visited)
				{
					CellArray[iIndex][jIndex].Right_Wall = false;
					create_Maze_r(closeOne[indices].first, closeOne[indices].second, 0, seed);
				}

				///If the random index we had is behind us  just call back the function because we're on another cell
				else if (closeOne[indices].first == iIndex - 1 && !CellArray[iIndex - 1][jIndex].visited)
				{
					create_Maze_r(closeOne[indices].first, closeOne[indices].second, 1, seed);
				}

				///If the random index we had is on our left just call back the function because we're on another cell
				else if (closeOne[indices].second == jIndex - 1 && !CellArray[iIndex][jIndex - 1].visited)
				{
					create_Maze_r(closeOne[indices].first, closeOne[indices].second, 2, seed);
				}

				///Get the iterator of our current index
				std::vector<std::pair<int, int>>::iterator it = (closeOne.begin() + indices);
				
				///Delete the index in the vector
				closeOne.erase(it);
			}
		}
```
# Core features
There's a lot of core features i'd like to talk about. Let's talk about the UI first.\
I used ImGui to create it and despite all the buttons and menus there's is in the game i'd like to talk about the crosshair.\
One particular thing i'm happy to have is the crosshair that changes form when hovering over a key or a "grappling stuff". In order to do that, we're just constantly throwing a raycast in front of the player. \
\
Another core feature is the collision.\
We used a classic AABB system that we created on our own. Moreover our collisions system allows us to do "box culling" rendering and optimize the rendering in a specific range.\
\
We also implemented sound with irrklang.\
The idea was to create a "spooky" ambiance and make the player stress. We added footstep, light turn on\off sound, grapple sound and background music. 

# Gameplay
The gameplay loop is easy. You'r in a maze trying to find the the exit. The only thing you find is a strange door with a strange color AND a strange light with the same color. Once you think a bit you find the solution and go through the four mazes of the first level you fall in the infinity and respawn but his time the maze in one cell longer.

# Demo

https://github.com/user-attachments/assets/98f8ff43-85c8-4f58-9319-2497e1aaf032

# Contact
<u>**Malo Sadoine**</u>
- [![Linkedin][LinkedIn]][LinkedIn-url]
- mal.sadoine@gmail.com

[LinkedIn]: https://img.shields.io/badge/linkedin-34a8eb?style=for-the-badge&logo=linkedin
[LinkedIn-url]: https://www.linkedin.com/in/malo-sadoine-098b7a254/

