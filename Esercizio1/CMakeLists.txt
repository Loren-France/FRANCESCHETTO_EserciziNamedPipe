cmake_minimum_required(VERSION 4.2)
project(Esercizio1 C)

set(CMAKE_C_STANDARD 11)

add_executable(client client.c
        ../Esercizio2/client2.c
        ../Esercizio2/server2.c
        ../Esercizio3/program2.c
        ../Esercizio3/program1.c)
add_executable(server server.c)
