molto-allegro
=============

Aims of the project
-------------------

The molto allegro library aims to provide a reasonably fast and simple to implement GUI drawing addon for Allegro 5. At the cost of lack of customization (no skins, no color editing, no-nonsense approach all around), it takes just a couple minutes to implement in your existing Allegro project.

Practical example
-----------------

This is what it takes to use molto allegro:

Creating a menu object is easy.

```c++
Menu *m = new Menu(display);
```

Adding some top-level categories is easy, too:

```c++
m->addElem(string("Test element 1"));
m->addElem(string("Test element 2"));	
m->addElem(string("Another"));
m->addElem(string("Keep going!"));
```
Let's add some options to our categories. For that, we reference the category we want by name (Test element 1, here) and call it's addElem providing a name for the button, a callback function - any function at all that will take a single void* as a parameter - and the parameter, cast to void*.

```c++
m->element("Test element 1")->addElem("Test element's button", some_callback_function, (void*)parameter);
```

The void* cast helps us weasel any type of parameter we want into the callback function - we simply cast our original parameter to void*, and then - within the callback function - we cast it back to it's original/needed type.

See the example folder for a bit of code which will help you understand the concept of callbacks.


