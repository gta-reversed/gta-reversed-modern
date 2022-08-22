# Coding Guidelines


### General Coding Guidelines

Don't touch old code unless it's related to your PR and you must absolutely do it to make your code work. Modifying spaces/tabs or even types will simply bloat your PR, and this will make your PR difficult to review. Instead, you can create a new PR and refactor the code your heart desires. This is not a strict rule, but please try your best.

Instead of `int`, `short`, `unsigned char`, etc. you should use `int32_t`, `int16_t` `int8_t`, `uint32_t`, `uint16_t`, etc.

The function prototypes should look exactly like the [android IDB](https://discord.com/channels/479682870047408139/669671263995822087/698034230722035762). If you see `CEntity& const` in the android IDB, then please don't change it to `CEntity*`, however, you can change `int` to `int32_t`, short to `int16_t`, etc.

### Keeping the code close to the original source

GTA SA is written in C++03 and compiled with VS2003. Please refrain from using templates unless R* used them for the classes you're reversing.

Think of yourself as a R* dev in 2003 and now imagine how you should be writing the code. R* didn't use the standard library, so don't use anything from `std` namespace. Modern C++ should be avoided at all costs. C++11 and later is NOT allowed, so the `auto` keyword, lambdas, modern for loops should be avoided. Also, don't put the `const` keyword after function declaration, you can use it for variables (globals included), members, and arguments.

```
    // NOT ALLOWED
    for (const CPlayer& player : players)  {
    }
```
```
    // OK, GOOD
    for (int32_t i = 0; i < MAX_PLAYERS; i++)  {
        CPlayer& player = players[i];
        
    }
```

However, there are a few exceptions, you can use these functions/keywords: `std::min` `std::max` `std::pow/std::powf` `constexpr` `override`

### Testing your code

Once you're done writing your code, then please make sure to test it before you open a PR. The best way to test your code is to open the debug panel (F7), play missions, and fly across the map in hydra. You should play at least 3 different missions before you submit your PR. If there are any bugs or crashes, then try fixing them, otherwise you can always ask for help in discord. You can still open a PR but make sure to mention the issues that you need help with.
