g++ -Wall -O3 -std=c++17 -ggdb3 src/main.cpp -o main.bin
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./main.bin 15 domains/gripper/
