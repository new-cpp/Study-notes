client-server model:
  - physical implementation (seperate client and server)
  - software implementation (cliet and sever 2 piece of software on the same maching.
  

  - there is diffrent type of servers( depend on the service they provide) :
    - file transer server, web server, display server, mail server
      cloud server , IRC server ... 
      


 - wayland and X11 are display server :
   - client are the graphical applications communicate  for requests( display , get input , ... ) with wayland or X11 server  through protocol .

 - X11 have and extra seprate entity caller windows manager responsibale for window decoration, resising, moving ... which act as a middle man bettwen clients and X11 server (overhead) 

 - whereas wayland act as display server and window manager in one .



 # credit : julia frank youtube channel : https://www.youtube.com/watch?v=FksHyTvBUNs
            

   
