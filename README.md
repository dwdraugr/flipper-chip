# Flipper Zero Firmware community repo

![](https://github.com/Flipper-Zero/flipperzero-firmware-community/raw/master/wiki_static/firmware-wiki-header.gif)

Welcome to [Flipper Zero](https://flipperzero.one/zero)'s Firmware repo! Our goal is to create nice and clean code along with good documentation, to make it a pleasure for everyone to work with. This repo will become completely public closer to the device shipping date. 

**We are open for changes!** You can suggest changes for any part of the code, wiki, guidelines, workflow, automation, etc.

If you are deary to start, please read [contribution guide](https://github.com/Flipper-Zero/flipperzero-firmware-community/wiki/Contributing) about creating issue, editing wiki, improving codebase and configuring environment.

# Developer blog

You can read project updates in our developer blog:

**[Developer blog index](https://github.com/Flipper-Zero/flipperzero-firmware-community/wiki/Developer-blog)**

# Firmware

**[Firmware page](https://github.com/Flipper-Zero/flipperzero-firmware-community/wiki/Firmware)**

## Build and run:

You can run firmware locally (with HAL stub).

* `docker-compose exec dev make -C target_lo` for build
* `docker-compose exec dev target_lo/build/target_lo` for run

## Architecture and components

Flipper consists of the two main parts:

* Core: OS, HAL, FS, bootloader, FURI
* Applications: features like RFID or Tamagotchi, and also background tasks like button debouncing and backlight control.

### UI

Common UI feature (menu, screens...) at [UI page](https://github.com/Flipper-Zero/flipperzero-firmware-community/wiki/UI)

### Features

* [Basic Features](https://github.com/Flipper-Zero/flipperzero-firmware-community/wiki/Basic-features)
* [Sub-1 GHz radio](https://github.com/Flipper-Zero/flipperzero-firmware-community/wiki/Sub-1-GHz-radio) (Transceiver Based on CC1101 chip for 315/433/868 MHz)
* [125 kHz RFID](https://github.com/Flipper-Zero/flipperzero-firmware-community/wiki/125-kHz-RFID)
* [Infrared](https://github.com/Flipper-Zero/flipperzero-firmware-community/wiki/Infrared)
* [iButton contact keys](https://github.com/Flipper-Zero/flipperzero-firmware-community/wiki/iButton-contact-keys)
* [USB](https://github.com/Flipper-Zero/flipperzero-firmware-community/wiki/USB)
* [Bluetooth](https://github.com/Flipper-Zero/flipperzero-firmware-community/wiki/Bluetooth)
* [GPIO/HW Modules](https://github.com/Flipper-Zero/flipperzero-firmware-community/wiki/GPIO)
* [NFC](https://github.com/Flipper-Zero/flipperzero-firmware-community/wiki/NFC)
* [U2F](https://github.com/Flipper-Zero/flipperzero-firmware-community/wiki/U2F)
* [Tamagotchi](https://github.com/Flipper-Zero/flipperzero-firmware-community/wiki/Tamagotchi)
* [USB](https://github.com/Flipper-Zero/flipperzero-firmware-community/wiki/USB)
* [Plugins](https://github.com/Flipper-Zero/flipperzero-firmware-community/wiki/Plugins)

# Hardware

**[Hardware page](https://github.com/Flipper-Zero/flipperzero-firmware-community/wiki/Hardware)**

# Links

* Discord server: [flipperzero.one/discord](https://flipperzero.one/discord)
* Project website: [flipperzero.one](https://flipperzero.one)
* Kickstarter page: [kickstarter.com](https://www.kickstarter.com/projects/flipper-devices/flipper-zero-tamagochi-for-hackers)
* Forum: [forum.flipperzero.one](https://forum.flipperzero.one/)
