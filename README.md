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
  - A) Multistage Filter WITH Conservative Update: 0.033409 seconds, 63 lines
  - B) Multistage Filter WITHOUT Conservative Update: 0.028777 seconds, 3637 lines
  - C) Sample and Hold: 0.036813 seconds, 52 lines
  - D) Standard Hashing: 0.034507 seconds, 63 lines
  
2) Oscars Transformed Dataset (103,960 lines)
  - Same as (1) except transformed to be 10 times larger (same data).
  - Filtering on Category
  - Threshold = 0.04
  - A) Multistage Filter WITH Conservative Update: 0.261678 seconds, 562 lines
  - B) Multistage Filter WITHOUT Conservative Update: 0.291292 seconds, 36115 lines
  - C) Sample and Hold: 0.306713 seconds, 557 lines
  - D) Standard Hashing: 0.313752 seconds, 562 lines

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
  - A) Multistage Filter WITH Conservative Update: 0.259293 seconds, 10125 lines
  - B) Multistage Filter WITHOUT Conservative Update: 0.423100 seconds, 80124 lines
  - C) Sample and Hold: 0.261514 seconds, 10118 lines
  - D) Standard Hashing: 0.247077 seconds, 10125 lines

5) Larger Fake Dataset (1,000,000 lines)
  - Same idea as (4) but 10 times larger
  - Filtering on 3 with threshold 0.7
  - A) Multistage Filter WITH Conservative Update: 2.396238 seconds, 1950 lines
  - B) Multistage Filter WITHOUT Conservative Update: 4.158712 seconds, 801949 lines
  - C) Sample and Hold: 2.729222 seconds, 1947 lines
  - D) Standard Hashing: 2.983047 seconds, 1950 lines


Evaluations performed on an Asus Laptop with an Intel i7-10510U CPU @ 1.80GHz processor, 16GB RAM, on an Ubuntu terminal

# Analysis:

1) For the sample and hold method, since we are processing a whole dataset at once which has no concepts of 'time interval', the optimaztion update in the paper for sample and hold is not applicable in our case.

2) Based on the evaluation, we take standard hashing as benchmark.
    - Multistage Filter without conservative update always has a larger report output, that is caused by a number of false positive. Multistage filter with conservative update is doing much better.
    - Sample and hold always has a smaller report output, that is caused by a few cases of false negative. The false nagative is caused by the sampling method.
    - Multistage Filter runs faster than both sample and hold and naive hashing.

# Architecture
[Architecture sketch](./architecture.pdf)<br/>
Preprocessor: preprocess data -- trasmit data from csv to project data structure<br/>
Queue: thread safe queue<br/>
Filter: heavy hitter detector -- sample and hold, multistage filter and naive filters<br/>
Reporter: report data<br/>
    

# Requirements:
std >= c++11<br/>
CMake >= 3.0<br/>
Environment: Unix/Linux

# Instructions
In the main directory:<br/>
cmake .<br/>
make<br/>
./heavy_hitters ./data/{Input File Dataset}.csv ./report {threshold}<br/>
For example, using the large Oscars with a threshold of 0.8:<br/>
    ./heavy_hitters ./data/oscar_large.csv ./report 0.8<br/>

Currently, we do have to pass a parameter in the code to indicate which columns in the CSV to filter on (which can be found in the heavy_hitter.cpp).<br/> 
By default, it will filter on the first column, one change the {0} to any combinations needed to be the UID.
