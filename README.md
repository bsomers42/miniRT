# miniRT: a mini raytracer
by [jaberkro](https://github.com/jaberkro) and [bsomers](https://github.com/bsomers42).

miniRT is the 11th project of the Codam core curriculum, and the last one entirely written in C. 
Using raytracing, various scenes can be rendered.

## Running:

`make && ./miniRT <map_name>.rt`

Example scenes can be found in the folder "maps".

## Adjustable raytracer settings

Change `AA` in include/minirt.h to a higher number for increased anti-aliasing. 
Change `WIDTH` and `HEIGHT` in include/minirt.h for a different screen size.

## Examples

maps/cones.rt (with AA=1)
<img width="1594" alt="image" src="https://user-images.githubusercontent.com/77967616/211013439-14ddc763-0d47-4bd5-852e-2b3a11cf1664.png">

maps/mickey.rt (with AA=4)
<img width="1596" alt="image" src="https://user-images.githubusercontent.com/77967616/211013729-ae1c14ae-71dd-4133-a78e-bf3915fbd6d5.png">

