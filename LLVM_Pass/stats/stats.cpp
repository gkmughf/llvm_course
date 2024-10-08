#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

std::string conc(const std::deque<std::string> &window, size_t start,
                 size_t end, const std::string &seporator = "|") {
  std::string result;
  for (size_t i = start; i < end; ++i) {
    if (i > start)
      result += seporator;
    result += window[i];
  }
  return result;
}

void stat_out(std::map<std::string, int> stats, std::ofstream &out) {
  std::vector<std::pair<std::string, int>> vec(stats.begin(), stats.end());
  std::sort(vec.begin(), vec.end(),
            [](const std::pair<std::string, int> &a,
               const std::pair<std::string, int> &b) {
              if (a.second != b.second)
                return a.second > b.second;
              return a.first < b.first;
            });

  for (const auto &[word, count] : vec) {
    out << word << " " << count << std::endl;
  }
}

int main() {
  std::ifstream in("track.stat");
  if (!in) {
    std::cout << "Не удалось открыть файл: \n";
    return 1;
  }

  std::map<std::string, int> line1;
  std::map<std::string, int> line2;
  std::map<std::string, int> line3;
  std::map<std::string, int> line4;
  std::map<std::string, int> line5;

  std::deque<std::string> lag;

  std::string line;
  while (std::getline(in, line)) {
    ++line1[line];

    lag.push_back(line);

    if (lag.size() >= 2) {
      std::string bg = conc(lag, lag.size() - 2, lag.size());
      ++line2[bg];
    }
    if (lag.size() >= 3) {
      std::string tg = conc(lag, lag.size() - 3, lag.size());
      ++line3[tg];
    }
    if (lag.size() >= 4) {
      std::string fg = conc(lag, lag.size() - 4, lag.size());
      ++line4[fg];
    }
    if (lag.size() >= 5) {
      std::string fvg = conc(lag, lag.size() - 5, lag.size());
      ++line5[fvg];
    }

    if (lag.size() > 5) {
      lag.pop_front();
    }
  }

  in.close();

  std::ofstream stat1("stats1.stat");
  std::ofstream stat2("stats2.stat");
  std::ofstream stat3("stats3.stat");
  std::ofstream stat4("stats4.stat");
  std::ofstream stat5("stats5.stat");
  stat_out(line1, stat1);
  stat_out(line2, stat2);
  stat_out(line3, stat3);
  stat_out(line4, stat4);
  stat_out(line5, stat5);
  stat1.close();
  stat2.close();
  stat3.close();
  stat4.close();
  stat5.close();

  return 0;
}
