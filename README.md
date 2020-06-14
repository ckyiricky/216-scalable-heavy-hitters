# 216-scalable-heavy-hitters
UCLA CS216 Project

We implemented a scalable heavy hitters scheme based off of the following paper:
http://pages.cs.wisc.edu/~estan/publications/elephantsandmice.pdf

Specifically we implemented the 'Multistage filter' and 'Sample and Hold'algorithms.<br/>
  Note:  The Multistage Filter was implemented with and without the conservative update strategy.

We used a variety of data sets, with CSV files as input, and compared our results to a naive hashing algorithm.

# Evaluation

1) Oscars Real Dataset (10,396 lines)
  - The Oscars, AKA The Academy Awards, are awards for artistic and technical merit in the film industry
  - For example, Marlon Brando was nominated for Best Actor for his role in the film 'Julius Caesar', but he did not win.
  - This data set includes Oscar category, name of nominee, Film, and whether or not won
  - Filtering on Category
  - Threshold = 0.04
  - A) Multistage Filter WITH Conservative Update: 0.046000 seconds, 598 lines
  - B) Multistage Filter WITHOUT Conservative Update: 0.039024 seconds, 5398 lines
  - C) Sample and Hold: 0.067447 seconds, 582 lines
  - D) Standard Hashing: 0.068105 seconds, 598 lines
  
2) Oscars Transformed Dataset (103,960 lines)
  - Same as (1) except transformed to be 10 times larger (same data).
  - Filtering on Category
  - Threshold = 0.04
  - A) Multistage Filter WITH Conservative Update: 0.272999 seconds, 562 lines
  - B) Multistage Filter WITHOUT Conservative Update: 0.287293 seconds, 36115 lines
  - C) Sample and Hold: 0.358042 seconds, 555 lines
  - D) Standard Hashing: 0.355145 seconds, 562 lines

3) FilmTV Movies Dataset (~45,000 lines)
  - Movies dataset containing ~45,000 movies with Title, Year of Release, Duration, Country, Director, Lead Actor, and Rating
  - Filtering on Genre
  - Threshold = 0.8
  - A) Multistage Filter WITH Conservative Update: 0.114002 seconds, 9058 lines
  - B) Multistage Filter WITHOUT Conservative Update: 0.227852 seconds, 45749 lines
  - C) Sample and Hold: 0.112215 seconds, 9057 lines
  - D) Standard Hashing: 0.124344 seconds, 9058 lines

4) Fake Letters Dataset (100,000 lines)
  - Randomly Generated dataset to simulate heavy hitters
  - 4 columns: 1, 2, 3, 4
  - Columns 1, 2, 3, and 4 are configured to be A, B, C and D (respectively) 80% of the time, and a random letter E-Z 20% of the time
  - Filtering on 3 with threshold 0.7
  - A) Multistage Filter WITH Conservative Update: 0.299161 seconds, 10914 lines
  - B) Multistage Filter WITHOUT Conservative Update: 0.014146 seconds, 80913 lines
  - C) Sample and Hold: 0.007044 seconds, 10072 lines
  - D) Standard Hashing: 0.005851 seconds, 10074 lines

5) Larger Fake Dataset (1,000,000 lines)
  - Same idea as (4) but 10 times larger
  - Filtering on 3 with threshold 0.7
  - A) Multistage Filter WITH Conservative Update: 2.279764 seconds
  - B) Multistage Filter WITHOUT Conservative Update: 2.324747 seconds
  - C) Sample and Hold: 1.906021 seconds
  - D) Standard Hashing: 2.050334 seconds

Evaluations performed on an Asus Laptop with an Intel i7-10510U CPU @ 1.80GHz processor, 16GB RAM, on an Ubuntu terminal

# Architecture
[Architecture sketch](./architecture.pdf)<br/>
Preprocessor: preprocess data -- trasmit data from csv to project data structure<br/>
Queue: thread safe queue<br/>
Filter: heavy hitter detector -- sample and hold, multistage filter and naive filters<br/>
Reporter: report data<br/>
    

# Requirements:
std >= c++11<br/>
CMake >= 3.0

# Instructions
In the main directory:<br/>
cmake .<br/>
make<br/>
./heavy_hitters ./data/{Input File Dataset}.csv ./report {threshold}<br/>
For example, using the large Oscars with a threshold of 0.8:<br/>
    ./heavy_hitters ./data/oscar_large.csv ./report 0.8<br/>

Currently, we do have to pass a parameter in the code to indicate which columns in the CSV to filter on (which can be found in the heavy_hitter.cpp).<br/> 
By default, it will filter on the first column, one change the {0} to any combinations needed to be the UID.
