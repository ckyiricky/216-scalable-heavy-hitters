# 216-scalable-heavy-hitters
UCLA CS216 Project

We implemented a scalable heavy hitters scheme based off of the following paper:
http://pages.cs.wisc.edu/~estan/publications/elephantsandmice.pdf

Specifically we implemented the 'Multistage filter' and 'Sample and Hold'algorithms.
  Note: Both algorithms were implemented with and without the conservative update strategy.

We used a variety of data sets, with CSV files as input, and compared our results to a naive hashing algorithm.

# Evaluation

1) Oscars Real Dataset (10,396 lines)
  - The Oscars, AKA The Academy Awards, are awards for artistic and technical merit in the film industry
  - For example, Marlon Brando was nominated for Best Actor for his role in the film 'Julius Caesar', but he did not win.
  - This data set includes Oscar category, name of nominee, Film, and whether or not won
  - A) Multistage Filter WITHOUT Conservative Update
  - B) Multistage Filter WITH Conservative Update
  - C) Sample and Hold WITHOUT Conservative Update
  - D) Sample and Hold WITH Conservative Update
  - E) Standard Hashing
  
2) Oscars Transformed Dataset (103,960 lines)
  - Same as (1) except transformed to be 10 times larger (same data).
  - A) Multistage Filter WITHOUT Conservative Update
  - B) Multistage Filter WITH Conservative Update
  - C) Sample and Hold WITHOUT Conservative Update
  - D) Sample and Hold WITH Conservative Update
  - E) Standard Hashing

3) FilmTV Movies Dataset (~45,000 lines)
  - Movies dataset containing ~45,000 movies with Title, Year of Release, Duration, Country, Director, Lead Actor, and Rating
  - A) Multistage Filter WITHOUT Conservative Update
  - B) Multistage Filter WITH Conservative Update
  - C) Sample and Hold WITHOUT Conservative Update
  - D) Sample and Hold WITH Conservative Update
  - E) Standard Hashing

4) Fake Dataset (100,000 lines)
  - Randomly Generated dataset to simulate heavy hitters
  - 5 columns: ID, A, B, C, D
  - Columns A, B, C, and D are configured to be 1,2,3,4 80% of the time, and a random number 5-10 20% of the time
  - A) Multistage Filter WITHOUT Conservative Update
  - B) Multistage Filter WITH Conservative Update
  - C) Sample and Hold WITHOUT Conservative Update
  - D) Sample and Hold WITH Conservative Update
  - E) Standard Hashing

5) Larger Fake Dataset (1,000,000 lines)
  - Same as (4) but 10 times larger
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

# Instructions
TBD
