# Bottle Puzzle Solver in C

## Project Overview

The **Bottle Puzzle Solver** is a game implemented in C, where the player has to rearrange colored liquid units inside bottles. The goal is to have all bottles filled with liquid of the same color, leaving the remaining bottles empty. The game allows the user to make moves by pouring liquid from one bottle into another, following predefined rules.

This project uses a tree structure to explore all possible game states and find valid solutions. The player interacts with the program via a text-based menu, which provides options for playing, getting hints, and viewing the solution tree.

## Features

1. **Game Setup**: 
   - The game starts with `n` bottles, out of which `k` bottles are empty. The rest contain liquid units of different colors.
   - The goal is to rearrange the liquids such that each bottle contains only one color, and the rest are empty.

2. **Random Initial State Generation**:
   - The program uses the **Linear Congruential Generator (LCG)** algorithm to generate a random initial configuration of liquids inside the bottles.

3. **Game Rules**:
   - Liquids can only be poured from one bottle into another if they meet specific criteria:
     - You can only pour liquid from the top of one bottle.
     - The top liquid in the target bottle must either be of the same color or the bottle must be empty.
     - Multiple units of the same color can be poured all at once if there is enough space in the target bottle.
   - The player has a limited number of moves to solve the puzzle.

4. **Decision Tree Formation**:
   - A decision tree is built to explore all possible moves. Each node represents a game state, and the edges represent the moves made between those states.

5. **Player Guidance**:
   - The player can ask for hints, and the program will guide them towards a valid move that leads to a solution.

6. **Tree Traversal**:
   - The program can display the tree of possible moves in a **preorder traversal** format, showing the sequence of moves.

7. **Menu-Based User Interaction**:
   - The player can interact with the game using a menu that provides options to:
     - Make a move
     - Get a hint
     - Display the solution step-by-step
     - Display the decision tree
     - Quit the game

## Game Rules

- The game follows specific rules for pouring liquid between bottles:
  - Liquids are poured only from the top of one bottle to another.
  - You can only pour into an empty bottle or onto a liquid of the same color.
  - If there is not enough space in the target bottle, only the amount that can fit will be poured.
  
## How to Play

1. **Start the Game**: 
   - After setting the number of bottles and empty bottles, the game generates a random initial configuration using the **Linear Congruential Generator (LCG)** algorithm.
   
2. **Make a Move**:
   - The player selects two bottles: one to pour from and one to pour into.
   - The program checks whether the move is valid and then performs the pour.

3. **Get a Hint**:
   - If the player is stuck, they can ask for a hint, and the program will suggest a valid move.

4. **Display Tree**:
   - The program can display all possible moves in a tree structure using preorder traversal.

5. **Solve the Puzzle**:
   - The objective is to have all bottles filled with the same color liquid within the allowed number of moves.

## Technologies Used

- **C Programming Language**: The game logic, decision tree, and random number generation are implemented in C.
- **Data Structures**: 
  - Decision tree structure (`knot`) used to represent game states and moves.
  - Stacks for depth-first traversal of the decision tree.
- **Linear Congruential Generator (LCG)**: Used for generating the random initial configuration of liquids.

## Future Improvements

- Implement a graphical user interface (GUI) to make the game more user-friendly.
- Add undo functionality to allow players to revert their moves.
- Introduce different difficulty levels by increasing the number of bottles and colors.

## How to Run

1. **Clone the Repository**:

    ```bash
    git clone https://github.com/ana147219/Bottle-Puzzle-Solver---Liquid-Sorting-Game.git
    ```

2. **Compile the Program**:

    ```bash
    gcc -o bottle_puzzle_solver main2.c -lm
    ```

3. **Run the Game**:

    ```bash
    ./bottle_puzzle_solver
    ```

## Conclusion

The **Bottle Puzzle Solver** is a fun and challenging game that tests the player’s ability to plan and solve puzzles. Implementing the game in C allowed for deep exploration of data structures such as decision trees and algorithms such as random number generation. This project provides an excellent platform for learning about game development and algorithm design.

