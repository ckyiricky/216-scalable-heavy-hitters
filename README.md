# 216-scalable-heavy-hitters
UCLA CS216 Project

We implemented a scalable heavy hitters scheme based off of the following paper:
http://pages.cs.wisc.edu/~estan/publications/elephantsandmice.pdf

Specifically we implemented the 'Multistage filter' and 'Sample and Hold'algorithms.
  Note: Both algorithms were implemented with and without the conservative update strategy.

We used a variety of data sets, with CSV files as input, and compared our results to a naive hashing algorithm.

# Evaluation

1) Oscar
  - The Oscars, AKA The Academy Awards, are awards for artistic and technical merit in the film industry
  - For example, Marlon Brando was nominated for Best Actor for his role in the film 'Julius Caesar', but he did not win.
  - This data set includes Oscar category, name of nominee, Film, and whether or not won
  - A) Multistage Filter WITHOUT Conservative Update
  - B) Multistage Filter WITH Conservative Update
  - C) Sample and Hold WITHOUT Conservative Update
  - D) Sample and Hold WITH Conservative Update
  - E) Standard Hashing

# Architecture:
TBD

# Requirements:
std >= c++11
CMake >= 3.17
