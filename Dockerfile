FROM ubuntu:20.04
COPY CMakeLists.txt ./exec/CMakeLists.txt
COPY LightYearsEngine/ ./exec/LightYearsEngine
COPY LightYearsGame/ ./exec/LightYearsGame
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y tzdata
RUN ln -fs /usr/share/zoneinfo/Asia/Kolkata /etc/localtime && dpkg-reconfigure -f noninteractive tzdata
WORKDIR /exec
RUN apt-get install cmake -y \
    apt-utils \
    build-essential \
    git \
    libx11-dev \
    libxrandr-dev \
    libglu1-mesa-dev \
    libudev-dev \
    libfreetype6-dev \
    libopenal-dev \
    libvorbis-dev \
    libogg-dev \
    libflac-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release .. && make -j5
RUN rm -rf LightYearsGame/ LightYearsEngine/ CMakeLists.txt

WORKDIR build/LightYearsGame/
CMD ["/bin/bash", "-c", "export LIBGL_ALWAYS_SOFTWARE=1 && ./LightYearsGame"]
