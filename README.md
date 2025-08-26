# cphandbook

This repository contains code snippets from [cp handbook](https://cses.fi/book/book.pdf).

## How to build manually

```sh
clang -std=c++11 -O2 -Wall test.cpp -o test
```

## How to build using meson

- Setup build directory (add `--reconfigure` when `meson.build` is updated)

```sh
meson setup build
```

- Build a target, for example

```sh
meson compile -C build [target]
```

- Clean the build directory (using [ninja](https://github.com/ninja-build/ninja) or [samurai](https://github.com/michaelforney/samurai))

```sh
[ninja|samu] -C build clean
```
