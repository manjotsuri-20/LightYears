# Light Years

## Requirements
    1. OS supported: Ubuntu.
    2. OS version required: Ubuntu 20.04

## Run the Game
1. Clone the repository:

    `git clone https://github.com/manjotsuri-20/LightYears/tree/master `

2. Create a build folder:

    `cd LightYears && mkdir build`

3. Build the code inside the build folder

    `cd build/ && rm -rf * && cmake -DCMAKE_BUILD_TYPE=Release .. && make -j5 && cd -`

4. Run the Game

    `cd LightYearsGame && ./../build/LightYearsGame/LightYearsGame & cd -`