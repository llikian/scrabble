# Project Scrabble
## Description
The goal of this project is to program an automatic Scrabble player, 
which will determine the move that scores the most points given a game board, 
the player's set of letters, and a dictionary.

## Setup
### Dependencies
On a Debian system you can install the needed dependencies using:
```shell
sudo apt install g++ cmake make
```

### Clone Repository
```shell
git clone GIT_LINK
cd Template
```

### Build
To build you can simply run the `release.sh` script at the root of the project using:
```shell
bash release.sh
```

You can also manually build it using:
```shell
cmake -B build && \
cmake --build build -j
```

Then you can run it using:
```shell
bin/Template
```
## Usage



## Credits
Killian POULETTE 12200001<br/>
Samuel BIBAS 12102474

This project has been made in the context of LIFAPC : https://forge.univ-lyon1.fr/lifap6/scrabble-etu