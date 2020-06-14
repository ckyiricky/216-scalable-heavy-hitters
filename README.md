# 216-scalable-heavy-hitters
UCLA CS216 Project

We implemented a scalable heavy hitters scheme based off of the following paper:
http://pages.cs.wisc.edu/~estan/publications/elephantsandmice.pdf

Specifically we implemented the 'Multistage filter' and 'Sample and Hold'algorithms.
  Note: Both algorithms were implemented with and without the conservative update strategy.

We used a variety of data sets, with CSV files as input, and compared our results to a naive hashing algorithm.

# Evaluation

We used a threshold of 0.8 for evaluations.

1) Oscars Real Dataset (10,396 lines)
  - The Oscars, AKA The Academy Awards, are awards for artistic and technical merit in the film industry
  - For example, Marlon Brando was nominated for Best Actor for his role in the film 'Julius Caesar', but he did not win.
  - This data set includes Oscar category, name of nominee, Film, and whether or not won
  - Filtering on Category
  - A) Multistage Filter WITH Conservative Update: x seconds, y lines
  - B) Multistage Filter WITHOUT Conservative Update: x seconds, y lines
  - C) Sample and Hold: x seconds, y lines
  - D) Standard Hashing: x seconds, y lines
  
2) Oscars Transformed Dataset (103,960 lines)
  - Same as (1) except transformed to be 10 times larger (same data).
  - Filtering on Category
  - A) Multistage Filter WITH Conservative Update: x seconds, y lines
  - B) Multistage Filter WITHOUT Conservative Update: x seconds, y lines
  - C) Sample and Hold: x seconds, y lines
  - D) Standard Hashing: x seconds, y lines

3) FilmTV Movies Dataset (~45,000 lines)
  - Movies dataset containing ~45,000 movies with Title, Year of Release, Duration, Country, Director, Lead Actor, and Rating
  - Filtering on Genre
  - A) Multistage Filter WITH Conservative Update: x seconds, y lines
  - B) Multistage Filter WITHOUT Conservative Update: x seconds, y lines
  - C) Sample and Hold: x seconds, y lines
  - D) Standard Hashing: x seconds, y lines

4) Fake Dataset (100,000 lines)
  - Randomly Generated dataset to simulate heavy hitters
  - 5 columns: ID, A, B, C, D
  - Columns A, B, C, and D are configured to be 1,2,3,4 80% of the time, and a random number 5-10 20% of the time
  - Filtering on C
  - A) Multistage Filter WITH Conservative Update: x seconds, y lines
  - B) Multistage Filter WITHOUT Conservative Update: x seconds, y lines
  - C) Sample and Hold: x seconds, y lines
  - D) Standard Hashing

5) Larger Fake Dataset (1,000,000 lines)
  - Same idea as (4) but 10 times larger
  - Filtering on C
  - A) Multistage Filter WITH Conservative Update: x seconds, y lines
  - B) Multistage Filter WITHOUT Conservative Update: x seconds, y lines
  - C) Sample and Hold: x seconds, y lines
  - D) Standard Hashing: x seconds, y lines

# Architecture:
  [Architecture figure](./architecture.pdf)

# Requirements:
std >= c++11
CMake >= 3.0

# Instructions
In the main directory:
cmake .
make
./heavy_hitters ./data/{Input File Dataset}.csv ./report {threshold}
For example, using the large Oscars with a threshold of 0.8:
    ./heavy_hitters ./data/oscar_large.csv ./report 0.8

Currently, we hard-coded which column in the CSV to filter on.  By default, it will filter on the first column.
