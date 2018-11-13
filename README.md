# Meeblip Controller

[![Build Status Travis-CI](https://travis-ci.org/rclement/meeblip-controller.svg)](https://travis-ci.org/rclement/meeblip-controller)
[![Build status AppVeyor](https://ci.appveyor.com/api/projects/status/ub29w4jlrih593ox?svg=true)](https://ci.appveyor.com/project/rclement/meeblip-controller)

MIDI controller for the [Meeblip Anode](https://meeblip.com/products/meeblip-anode-synth) synthesizer,
available on MacOS and Windows as an audio plug-in (VST, VST3, AU) and a standalone app.

Inspired by [Meeblip Web Editor](https://editor.meeblip.com) and
[MyBlip Anode](http://www.dr-midik.fr/site/index.php?post/ticket_MyBlip-anode_2014-04-28).

Built using the [JUCE](https://juce.com) framework.

![Meeblip Controller Screenshot](ext/meeblip-controller-screenshot.png)


# Features

Currently supported features:

- Platforms: MacOS, Windows
- Plug-in format: VST2, VST3, AudioUnit
- Access to "hidden" (MIDI only) parameters
- Synth parameters exported at host level for real-time and offline automations
- Full-blown preset system


# Build

## Requirements

- `git`
- `python` >= 3.5
- `cmake` >= 3.4
- `Packages` (MacOS only)
- `XCode` >= 9.0 (MacOS only)
- `InnoSetup` (Windows only)
- `Visual Studio` >= 2017 (Windows only)

## Automated

```
    python build.py
```

## Manual

1. Checkout submodules

```
    git submodule update --init --recursive
```

2. Build `FRUT`

```
    mkdir -p sdks/frut/build
    cd sdks/frut/build
    cmake .. -DCMAKE_INSTALL_PREFIX=../prefix -DJUCE_ROOT=../../juce
    cmake --build . --target install
    cd -
```

3. Build the plugin

```
    mkdir -p build
    cd build
    cmake .. -G ["XCode" | "Visual Studio 15 2017"] -A ["Win32" | "x64"]
    cmake --build . --clean-first --config ["Debug" | "Release"]
```

4. Build the installer

- MacOS: `packagesbuild -v installer/meeblip-controller.pkgproj`
- Windows: `iscc "installer\meeblip-controller.iss"`


# License

GNU General Public License v3.0

Copyright (c) 2018 Romain Clement

