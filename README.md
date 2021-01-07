# mmorpg
This is a mmorpg school project written in c++. It doesn't have that much features, as it was basically put together in a bit over a month.
It features 3D graphics done using low level OpenGL api and GLM maths library, with GLFW as a window creation tool and GLEW for fetching functions. 
It also features online "play" using asio networking library. (Not done by me. This includes the whole server functionality)

One can click a tile and move to that location using left click and holding the right click moves the camera. The character wont move, unless trhe server is on and the player is connected(can be done locally, of course)

And to add, the .obj file loader is taken from a tutorial by a Github user Headturna, so all credits to him on that one. (I have however done a .obj loader in my scala3D project)
