# MMORPG

simple tile clicking simulator... for now


    ##        ##  ##       ##      ###     ####   ####       ####
    #  #     # #  # #     # #    #     #   #   #  #   #    #    
    #   #   #  #  #  #   #  #   #       #  #   #  # ###   #    ###
    #    # #   #  #   # #   #    #     #   ###    #        #     #
    #     #    #  #    #    #      ###     #  #   #          ###


###### INTRODUCTION ##############

This is a mmorpg school project written in c++. It doesn't have that much features seen in a traditional mmorpg, as it was basically put together in a bit over a month.
It features 3D graphics done using low level OpenGL api and GLM maths library, with GLFW as a window creation tool and GLEW for fetching functions. (These are required if one wishes to compile this.)
It also features online "play" using asio networking library. (Not done by me. This includes the whole server functionality)

I have done all of the graphics components and classes, including the mouse ray casting.

##### How does it work??  #######
One can click a tile and move to that location using left click and holding the right click moves the camera. The character wont move, unless the server is on and the player is connected(can be done locally, of course)

If one wishes to change resolution, use fullscreen, etc. it has to be done manually by changing variable values in the beginning of the main function in client.cpp file.

##### ADDITIONAL NOTES #########
-And to add, the .obj file loader is taken from a tutorial by a Github user Headturna, so all credits to him on that one. (I have however done a .obj loader in my scala3D project)

-Also I know that I didn't follow rule of three and the reason is honestly the time. There should be no excuses for this but the project is already over. I might add copy constructor and copy assignment operator in the future for the graphics classes if I have any extra time on my hands.
