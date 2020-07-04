cmake_minimum_required(VERSION 3.16)
project(p3)

set(CMAKE_CXX_STANDARD 11)

add_executable(test1 card.cpp deck.cpp hand.cpp player.cpp blackjack.cpp rand.cpp)