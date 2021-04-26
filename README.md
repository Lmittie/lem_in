# Lem-in 42

School 42 project.

## Overview

Elementary algorithmic project aimed at finding optimal paths on a graph.

The goal of this project is to find the quickest way to get ```n``` ants across the farm.

Quickest way means the solution with the least number of lines, respecting the
output format requested below.
```
Lx-y Lz-w Lr-o ...
```
x, z, r represents the ants’ numbers (going from 1 to number_of_ants) and y,
w, o represents the rooms’ names.

At the beginning of the game, all the ants are in the room ```##start```. The goal is
to bring them to the room ```##end``` with as few turns as possible. Each room can
only contain one ant at a time. (except at ```##start``` and ```##end``` which can contain
as many ants as necessary.)

Program will receive the data describing the ant farm from the standard output
in the following format:
```
number_of_ants
the_rooms
the_links
```

The ant farm is defined by the following links:
```
##start
1 23 3
2 16 7
#comment
3 16 3
4 16 5
5 9 3
6 1 5
7 4 8
##end
0 9 5
0-4
0-6
1-3
4-3
5-2
3-5
#another comment
4-2
2-1
7-6
7-2
7-4
6-5
#another comment
```

Which corresponds to the following representation:
```
          _______________
         /               \
  ______[5]----[3]----[1] |
 /              |    /    |
[6]-----[0]----[4]  /     |
 \   _________/ |  /      |
  \ /          [2]/______/
  [7]__________/
```

There are two parts:

◦ The rooms, which are defined by: ```name coord_x coord_y```

◦ The links, which are defined by: ```name1-name2```

◦ All of it is broken by comments, which start with ```#```

For example, ```##start``` signals the ant farm’s entrance and ```##end``` its exit.

Any non compliant or empty lines will automatically stop the ant farm’s reading
as well as the orderly processing of the acquired data.

If there isn’t enough data to process normally the program displays ```ERROR```

## Algorithm

To achieve the goal of the project modificated Dinic algorithm was used.

## Usage

```make && make clean```

```./lem-in < [map file]```

To generate a random map use generator executable in the repository root or maps in ```visual/maps``` directory

Use --help option to learn more: ```./generator --help```

## Visualization

Usage:
```make -C visual```

```./visualizer < maps/map5```

![map1](https://github.com/Lmittie/lem_in/blob/master/examples/visualizer%20map1.png?raw=true)

![map5](https://github.com/Lmittie/lem_in/blob/master/examples/visualizer%20map5.png?raw=true)

![map7](https://github.com/Lmittie/lem_in/blob/master/examples/visualizer%20map7.png?raw=true)
