# sudoku

Sudoku game through the terminal! Built with C++. CIS 1900 final project.

### Proposal
There will be three different modes of difficulty (easy, medium, and hard) that will each show a different amount of initial numbers. The [Sudoku games](https://www.printable-sudoku-puzzles.com/wfiles/) will be predetermined since randomly generating a puzzle could result in unsolvable games, but we will randomly generate which locations are shown on the initial board. We will load these games from text files based on the difficulty that the player chooses. After loading the game, the player can input both the location of the cell and the number (e.g. `2 3 5` would indicate that the player wants to place a 5 at location (2,3)) that they want to guess. At any point, the player can type in the command `check` to see if their current configuration of numbers is right. If the player wants to remove a number from the board that they’ve typed, they can type in the command `remove x y` to remove the number at the cell located at (x, y). 

We will use unique and shared pointers to represent the 2D board. We also expect to use vectors to randomly generate places on the board that will initially be visible to the user.

### Structure
- board.cpp: holds a 2D array of cells and will provide print functionality of the board
- cell.cpp: typical cell in Sudoku game, can be a digit from 1-9, will either be covered or uncovered at any point
- game.cpp: allows users to modify the board (e.g. place, remove, check) through the terminal
- random.cpp: randomly generate locations of the board to show

### Time and Work
We expect to spend the bulk of our time on implementing the basic structure/class hierarchy and the different commands to modify the board [9 hours combined]. The rest of our time will be spent creating random.cpp and other functions, like getters and setters [3 hours]. Lastly, we will need to spend some time figuring out how to read in text files and provide output [3 hours].  Time expectations are a guess :)

We plan to implement the basic structure and commands together via liveshare. Sara will create random.cpp and implement the other functions, and Hetvi will work on reading in text files and providing a design for the output.

### Authors
Sara Xin and Hetvi Shah
