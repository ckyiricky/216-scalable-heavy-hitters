# Evaluation
Evaluations performed on Macbook with an Intel i7 CPU @ 2.80GHz processor, 16GB RAM

1) Oscars Real Dataset (10,396 lines)
  - The Oscars, AKA The Academy Awards, are awards for artistic and technical merit in the film industry
  - For example, Marlon Brando was nominated for Best Actor for his role in the film 'Julius Caesar', but he did not win.
  - This data set includes Oscar category, name of nominee, Film, and whether or not won
  - Filtering on Category
  - Threshold = 0.04
  - A) Multistage Filter WITH Conservative Update: 0.132353 seconds, 392 lines
  - B) Multistage Filter WITHOUT Conservative Update: 0.151210 seconds, 1146 lines
  - C) Sample and Hold: 0.145856 seconds, 385 lines
  - D) Standard Hashing: 0.148259 seconds, 392 lines
  
2) Oscars Transformed Dataset (103,960 lines)
  - Same as (1) except transformed to be 10 times larger (same data).
  - Filtering on Category
  - Threshold = 0.04
  - A) Multistage Filter WITH Conservative Update: 1.307085seconds, 3903 lines
  - B) Multistage Filter WITHOUT Conservative Update: 1.430850 seconds, 11407 lines
  - C) Sample and Hold: 1.442425 seconds, 3901 lines
  - D) Standard Hashing: 1.448990  seconds, 3903 lines

3) FilmTV Movies Dataset (~45,000 lines)
  - Movies dataset containing ~45,000 movies with Title, Year of Release, Duration, Country, Director, Lead Actor, and Rating
  - Filtering on Genre
  - Threshold = 0.1
  - A) Multistage Filter WITH Conservative Update: 0.567494 seconds, 13444 lines
  - B) Multistage Filter WITHOUT Conservative Update: 0.744559 seconds, 28210 lines
  - C) Sample and Hold: 0.659831 seconds, 13428 lines
  - D) Standard Hashing: 0.670959 seconds, 13444 lines

4) Fake Letters Dataset (100,000 lines)
  - Randomly Generated dataset to simulate heavy hitters
  - 4 columns: 1, 2, 3, 4
  - Columns 1, 2, 3, and 4 are configured to be A, B, C and D (respectively) 80% of the time, and a random letter E-Z 20% of the time
  - Filtering on 3 with threshold 0.7
  - A) Multistage Filter WITH Conservative Update: 0.928613 seconds, 10118 lines
  - B) Multistage Filter WITHOUT Conservative Update: 0.797658 seconds, 80117 lines
  - C) Sample and Hold: 1.025937 seconds, 10115 lines
  - D) Standard Hashing: 1.016725 seconds, 10118 lines

5) Larger Fake Dataset (1,000,000 lines)
  - Same idea as (4) but 10 times larger
  - Filtering on 3 with threshold 0.7
  - A) Multistage Filter WITH Conservative Update: 9.559641 seconds, 101767 lines
  - B) Multistage Filter WITHOUT Conservative Update: 8.226404 seconds, 801766 lines
  - C) Sample and Hold: 11.164059 seconds, 101765 lines
  - D) Standard Hashing: 11.407487 seconds, 101767 lines

