# XV6 Systems Programming Assessment 2

## Stage 1
**Test Program**: `stage1demo` 
This is the example user program provided in the assessment spec, modified to support HDCs from [Stage 3](#stage-3).
## Stage 2
**Test Program**: `stage2demo` 
Program draws the screen with lines of colour, through the ranges of 0-63 in the red, green and blue channels. A rectangle is drawn in the center using the fillrect instruction in a solid colour.
## Stage 3
**Test Program**: `stage3demo` 
This program draws 4 lines, 2 in one process and 2 in the other. The ordering of the instructions mean it would not work without correct implementation of Device Contexts.
## Stage 4
**Test Program**: `None Provided, functionality implemented globally` 

## Other Programs
### colourdemo
Draws boxes from left to right changing the colour of each box. Demonstrates colour overwriting and Stage 4 batching. Each column of rectangles is drawn when the command buffer is full and pushes to the kernel.
### drawdemo
This was my testing program, currently just draws a red square with `fillrect`
