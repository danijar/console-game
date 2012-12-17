Console Game
============

Terminal
--------

The games runs in the windows command promt.

![Screenshot](https://raw.github.com/ComputerGame/ConsoleGame/master/screenshot.gif)

Map
---

Maps are loaded from textfiles. When the application starts it asks you for the filename. Just type in the name without `.txt` extension. The map must be in the same folder as the executable.

All rows in a mapfile need to have the same length. Be aware of the maximum with of the windows command promt.

    ................1.WWW...........WWW.....................
    ....................WW..........WW..333333333333333333..
    .....WWWWWWW.........WW......A.WW...3.........2..11..3..
    ....WWWWWWWWWW..1......WWW....WW....3222=222222......3..
    ...WWWWWWWWWWW..1.........WWWW......3......2............
    ...WWWWWWWWWW..333333333............3................3..
    ....WWWWWWW....3..11...3..B......c..3......2..11111..3..
    ......WWW..A...3.......3............3333=3333333333333..
    .....WW........3333=3333....O...........................
    .....WW.........1...................c...................
    ...WWW..........1...c...................................
    WWW......................333333=3333333333333333333333..
    ................1........3.......B...2...............3..
    ................1111111113......................A....3..
    .......A.................3....2......2...............3..
    .........................33333333333333333333333333333..
    ........................................................

The following letters are supported.

- `1`, `2`, `3`: Static obstacles, different color.
- `W`: Water, is animated.
- `=`. Door, opens when player is near.
- `c`: Coin raising Score.
- `A`: Monster, walks left and right.
- `B`: Monster, changes direction on collision.
- Any other letter: Space.

Try it out!
-----------

Just download the executable `main.exe` and the map file `map.txt` and run the game. According to the instruction above you can simply create your own maps.