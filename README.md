# Light Years

## Requirements
    1. OS supported: Ubuntu.
    2. OS version required: Ubuntu 20.04

## Run the Game
1. Clone the repository:

    `git clone https://github.com/manjotsuri-20/LightYears/tree/master `
### Build the code locally
1. Create a build folder:

    `cd LightYears && mkdir build`

2. Build the code inside the build folder

    `cd build/ && rm -rf * && cmake -DCMAKE_BUILD_TYPE=Release .. && make -j5`

3. Run the Game

    `cd LightYearsGame && ./LightYearsGame`


### Build using docker

1. Install docker and add docker to the xserver group:

    `xhost +local:docker`

2. Go to the repository folder:
    
    ` cd LightYears `

3. Build the Image:

    `sudo docker build -t lightyears:latest .`

4. Run the Image:

    `sudo docker run -e DISPLAY=$DISPLAY --net=host lightyears`