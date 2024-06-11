######################
 SDL2 Minimal Example
######################

Just opening a window and drawing something to it in as little code as possible
while still using clean C++ with automatic cleanup.

I wrote this to test smart pointer destruction for C API objects.
While the code properly creates and destroys everything in the correct
order defined for SDL2, it could still be written more robustly by introducing
a wrapper class hierarchy that enforces the C API rules.

