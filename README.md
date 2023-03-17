# Mandelbrot Viewer

I thought that rendering a mandelbrot set was a good way to learn more about compute shaders, so here we are.
I think I might have accidentaly fallen in love with the mandelbrot set slightly while making this.

You can use the left mouse button to pan, and the scroll wheel to zoom in and out.
The number of iterations that the compute shader goes through can be adjusted with u, i, o, j, k and, l buttons, where:
O = +1
l = -1
i = +10
k = -10
u = +100
j = -100
Iteration number over 500 is not recommended because it's slow.


Make sure that your graphics drivers are updated since this project uses OpenGL 4.6.

Have fun exploring!
