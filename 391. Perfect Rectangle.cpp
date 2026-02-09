Thought process/Key points

A rectangle has 4 corners. All corners must appear even number of times(because if the figure is a proper rectangle then all the corners will be contiguous) except for the corners.
Sum of areas of all small rectangles must equal to the big rectangle.
The bottom-left and the top right corners of the rectangle can be found by looking at the min and max of all points. Use that to figure out all 4 corners of rectangle.
Then check if the corners left(after eliminating the corners that occur even number of times) are the ones that should be the corners (which can be figured out from the bottom-left and top-right corners).
