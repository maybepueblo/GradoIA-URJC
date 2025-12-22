cmake_minimum_required(VERSION 3.31)
project(Twitter C)

set(CMAKE_C_STANDARD 11)

add_executable(Twitter main.c
        tElemento.c
        tElemento.h
        tTweet.c
        tTweet.h
        tListaTweets.c
        tListaTweets.h
        tArbolTweets.c
        tArbolTweets.h
        tHashtag.c
        tHashtag.h
)
