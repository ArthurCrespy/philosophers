<h1 align="center">
  <br>
  <a href="http://www.github.com/ArthurCrespy"><img src="https://42.fr/wp-content/uploads/2021/05/42-Final-sigle-seul.svg" alt="42" width="200"></a>
  <br><br>
  Philosophers
  <br>
</h1>

<h3 align="center">I never thought philosophy would be so deadly</h3>

<h4 align="center">In this project, you will learn the basics of threading a process.
You will see how to create threads and you will discover mutexes.</a></h4>

<p align="center">
    <a href="https://github.com/ArthurCrespy/philosophers/search?l=c"> <img alt="Language: C" src="https://img.shields.io/badge/language-C-orange"></a>
    <a href="https://github.com/ArthurCrespy/philosophers"> <img alt="Lines of code" src="https://img.shields.io/tokei/lines/github/ArthurCrespy/philosophers"></a>
    <a href="https://github.com/ArthurCrespy/philosophers/commits"> <img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/ArthurCrespy/philosophers?color=yellow"></a>
    <a href="https://github.com/ArthurCrespy/philosophers/watchers"> <img alt="GitHub watchers" src="https://img.shields.io/github/watchers/ArthurCrespy/philosophers?color=ff69b4""></a>
    <a href="https://projects.intra.42.fr/42cursus-philosophers/acrespy"> <img alt="Result: 100/100" src="https://img.shields.io/badge/result-100/100-brightgreen"></a>

</p>

<p align="center">
  <a href="#introduction">Introduction</a> •
  <a href="#how-to-use">How To Use</a> •
  <a href="#description">Description</a> •
  <a href="#about-42-cursus">About 42 Cursus</a> •
  <a href="#you-may-also-like">Related</a> •
  <a href="#license">License</a>
</p>

## Introduction


## How To Use

To clone and run this project, you'll need [Git](https://git-scm.com) and [Clang](https://clang.llvm.org/) installed on your computer. From your command line:

```bash
# Clone this repository via HTTPS
$ git clone https://github.com/ArthurCrespy/philosophers
# OR clone this repository via SSH
$ git clone git@github.com:ArthurCrespy/philosophers.git

# Go into the repository
$ cd philosophers

# Make the project
$ make

# Run the program
$ ./push_swap number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

## Description

In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.
It was originally formulated in 1965 by Edsger Dijkstra as a student exam exercise, presented in terms of computers competing for access to tape drive peripherals. Soon after, Tony Hoare gave the problem its present form.

Five philosophers dine together at the same table. Each philosopher has their own place at the table. There is a fork between each plate. The dish served is a kind of spaghetti which has to be eaten with two forks. Each philosopher can only alternately think and eat. Moreover, a philosopher can only eat their spaghetti when they have both a left and right fork. Thus two forks will only be available when their two nearest neighbors are thinking, not eating. After an individual philosopher finishes eating, they will put down both forks. The problem is how to design a regimen (a concurrent algorithm) such that no philosopher will starve; i.e., each can forever continue to alternate between eating and thinking, assuming that no philosopher can know when others may want to eat or think 

## About 42 Cursus

C project of Core03. The goal is to learn about mutexes.

## You may also like...

- [push_swap](https://github.com/ArthurCrespy/push_swap) - Because Swap_push isn’t as natural
- [so_long](https://github.com/ArthurCrespy/so_long) - And thanks for all the fish!

## License

For now, all rights are reserved.

---
<p align="center">
    <a href="https://github.com/ArthurCrespy"> <img alt="Made by ArthurCrespy" src="https://img.shields.io/badge/made%20by-ArthurCrespy-blue"></a>
    <a href="https://42.fr"><img alt="42 Website" src="https://img.shields.io/badge/website-42.fr-blue"></a>
    <br>
    Github <a href="https://github.com/ArthurCrespy" target="_blank">@Thur'</a> |
    LinkedIn<a href="https://fr.linkedin.com/in/crespyarthur" target="_blank"> @Arthur Crespy</a> |
    Instagram<a href="https://instagram.com/arthurcrespy" target="_blank"> @crespyarthur</a> 
</p>
