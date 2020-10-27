# simple-glarea-example
Simple example of using GtkGLArea to draw a triangle.

I found existing glarea examples to complex so i decide to write my own.
It just a single `main.c` file that depends only on GTK+ and GTK+ dependencies
You have to ensure that you have `gtk-3-dev` installed.  
Then you can compile code with  
```gcc main.c `pkg-config --cflags gtk+-3.0 --libs epoxy` ```
and run with `./a.out`. 
It have to work, if it isn't open issue  and provide as more info as possible.  
I also wrote an short explanation so if you interested it is below 

__!!! IT NOT A PRODUCTION CODE !!!__  
In this example i do stuff that unacceptable in real code.
I don't check errors after openGL, i write all code in one file and i store shaders source in same file as C source.
It not good, but i did it for keeping example easy to understand.
So read this code understand it, and try to find some more realistic examples.  
_They will be more complex but i hope after this, you'll be able to understand them._

## How it works
Here im going to explain what this code mean.
I'm not going to explain GTK usage and i'm not going deep into openGL workflow
you can read it here:
* [GTK](https://developer.gnome.org/gtk3/stable/gtk-getting-started.html)
* [openGL](https://www.khronos.org/opengl/wiki/Getting_Started)  
note that you already have openGL context that provided by GtkGLArea

### Functions
#### main()
All that main() do in this code is creation GtkApplication, and binding activate function to it

#### activate()
Here we create a GtkGLArea instance and bind two signals to it
1. realize - it will run once? when window is appear to user
2. render - every time GTK updates the window this function will be runned  
_it is default behavior it possible to disable [auto-render](https://developer.gnome.org/gtk3/stable/GtkGLArea.html#GtkGLArea--auto-render)
and call update function manualy_

#### buildShaderProgram()
here we just compile shaders which source is stored as global variable.
It's bad, i know but this is just an example.
After comilation we link shaders to program and delete them.

#### on_realize()
here we do some magic.
First thing first we call `buildShaderProgram()`
and then we put our vertices in buffers, so openGL can read them
vertices is just cordinates op point in normalized space.
We take all our area put (0;0;0) in center and normalize all points to \[-1;1]
so top left corner is (-1;1;Z) top right (1;1;Z) and so on...

#### render()
This function set openGL context to current GLarea and call `draw_triangle()` function.
You can write function like `draw_triangle()` _(ex. `draw_rectangle()` :)_ and call it here.
it exist just for code organisation

#### draw_triangle()
The actual triangle!
First we clear glarea with normalized to \[0;1] RGBA color.
Then we tell openGL to use our shader program and vertex buffer.
And ask openGL to draw binded vertecies with `glDrawArrays()` and colorize it with binded shader program.
After that we can bind nulls to clear context
and flush changes to screen

### shaders
Aim of shaders is tell us color of pixel based on it position, 
to keep thing simple we just always return light orange color RGBA(1.0;0.5;0.2;1.0)

## Give thanks
If you like this example.
Or it helps you
fell free to star this repo or contact me in [LinkedIn](https://www.linkedin.com/in/mihail-shinder-6794531b5)
