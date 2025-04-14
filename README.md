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
git clone https://github.com/llikian/scrabble
cd scrabble
```

### Build
To build you can simply run the `release.sh` script at the root of the project using:
```shell
bash release.sh
```

Then you can run it using:
```shell
bin/Scrabble
```

## Keybinds
- SPACE: Play one move
- A: Play moves until impossible
- L: Get link to Vincent Nivoliers's site to test the board
- ,: Get all moves who are as good as the best
- P: Print all possible moves
- R: Reset board and player
- S: Saves the current board to "data/saved_board.txt"
- V: Toggle verbose outputs (Whether debug info is print or not)

## Credits
Killian POULETTE 12200001<br/>
Samuel BIBAS 12102474

This project has been made in the context of [LIFAPC](https://forge.univ-lyon1.fr/lifap6/scrabble-etu).