# Coding Guidelines


### General Coding Guidelines

Don't touch old code unless it's related to your PR and you must absolutely do it to make your code work. Modifying spaces/tabs or even types will simply bloat your PR, and this will make your PR difficult to review. Instead, you can create a new PR and refactor the code your heart desires. This is not a strict rule, but please try your best.

Instead of `int`, `short`, `unsigned char`, etc. you should use `int32`, `int16` `int8`, `uint32`, `uint16`, etc.

The function prototypes should look exactly like the [Android IDB](https://www.youtube.com/watch?v=dQw4w9WgXcQ). If you see `const CEntity&` in the Android IDB, then please don't change it to `CEntity*`, however, you can change `int` to `int32`, short to `int16` and more:

```C++
uchar     -> bool
some type -> enum
char*     -> const char*
RwV3d     -> CVector
```

### Keeping the code close to the original source

GTA SA is written in C++03 and compiled with VS2003. Please refrain from using templates unless R* used them for the classes you're reversing.

### Testing your code

Once you're done writing your code, then please make sure to test it before you open a PR. The best way to test your code is to open the debug panel (F7), play missions, and fly across the map in hydra. You should play at least 3 different missions before you submit your PR. If there are any bugs or crashes, then try fixing them, otherwise you can always ask for help in discord. You can still open a PR but make sure to mention the issues that you need help with.
