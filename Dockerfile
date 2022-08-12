FROM gcc:9.2

ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update && apt-get install -y cmake libgtest-dev libboost-test-dev && rm -rf /var/lib/apt/lists/* 

WORKDIR /genesys
COPY *.cpp .
COPY *.hpp .
COPY CMakeLists.txt .

RUN cmake -B ./build .
RUN make -C build

CMD ["./build/tests"]
