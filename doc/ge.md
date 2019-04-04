## Overview

"Game Engine" is an unimaginatively named set of bindings for [SDL2](https://www.libsdl.org/) with an embedded [v8 Javascript engine](https://v8.dev/docs). Its sole purpose for the moment is educational. It is not intened to be a competitor to other tools already available, such as [node-sdl](https://www.npmjs.com/package/sdl) or the many [Javascript game engines](https://github.com/collections/javascript-game-engines)

From the Javascript side, access to the Game Engine is provided through a global module called "GE":

```javascript
use strict;
const mod = GE.Modules();
mod.require("SDL");
```

Each call to mod.require() will initialize new modules within the global object. After `mod.require("SDL")` we can then say things like `const win = SDL.Window()`

```javasciprt
const init_flags = SDL.InitFlags();
const window_flags = SDL.WindowFlags();
const render_flags = SDL.RenderFlags();
const pixel_format = SDL.Pixelformat();
const texture_access = SDL.TextureAccess();
```


## Compiling and running

- read [the requirements](requirements.md) and edit `CmakeLists.txt` then do
```shell no-beautify
    mkdir build; cd build; cmake ..; make shell
```
- in the build directory run a test program with
```shell no-beautify
    ./shell ./js/init.js
```

