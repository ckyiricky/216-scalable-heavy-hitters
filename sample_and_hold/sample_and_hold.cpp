
#include "sample_and_hold.h"

using QType = SafeQueue<Oscar>;

void showResults(std::unordered_map<string, int>& stat) {
  // sort the map
  std::vector<std::pair<string, int>> stat_sorted(stat.begin(), stat.end());
  std::sort(stat_sorted.begin(), stat_sorted.end(), [](pair<string,int> a, pair<string,int> b) {
    return a.second > b.second;
  });
  for (int i = 0; i < stat_sorted.size(); i++) {
    printf("%s \t %d \n", stat_sorted[i].first.c_str(), stat_sorted[i].second);
  }
}

// read the source file, parse the Oscar objects and push to ostream
void getOscarStream(string file, QType& queue_out) {
  ifstream fin(file);
  if (fin.fail()) {
    printf("[getOscarStream] failed to open file!\n");
    exit(1);
  }

  string line, temp;
  while (!fin.eof()){
    getline(fin, line);
    if (line.length() > 0) {
      queue_out.push(Oscar(line));
    }
  }

  // mark the end of stream
  queue_out.push(Oscar("EOL, 0, 0, 0"));

  fin.close();  
}

// baseline
void countAll(float threshold_dummy, QType& queue_in, unordered_map<string, int>& stat) {
  while(1) {
    string cat = queue_in.pop().getCategory();
    if (cat == "EOL") {
      break;
    }

    if (stat.find(cat) != stat.end()) {
      stat[cat]++;
    }
    else {
      stat[cat] = 1;
    }
  }
}

void sampleAndHold(float threshold, QType& queue_in, unordered_map<string, int>& stat) {
  while(1) {
    string cat = queue_in.pop().getCategory();
    if (cat == "EOL") {
      break;
    }

    // if already in table, record
    if (stat.find(cat) != stat.end()) {
      stat[cat]++;
    }
    else {
      // with probability p add new entry
      if (rand() % 1000 < 1000 * threshold) {
        stat[cat] = 1;
      }
    }
  }
}

int main() {

  // string file = "../data/test.csv";
  // string file = "../data/oscar_small.csv";
  string file = "../data/oscar_large.csv";

  QType queue;
  unordered_map<string, int> stat;

  float threshold = 0.001; // probability of sampling new input

  std::thread producer(getOscarStream, file, std::ref(queue));
  std::thread consumer(sampleAndHold, threshold, std::ref(queue), std::ref(stat));

  producer.join();
  consumer.join();

  showResults(stat);

  return 0;
}