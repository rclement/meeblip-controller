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

```
    python3 build.py
```


# License

GNU General Public License v3.0

Copyright (c) 2018 Romain Clement

