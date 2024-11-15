#include "absl/container/flat_hash_map.h"
#include <chrono>
#include <iostream>
#include <tsl/hopscotch_map.h>

template <class SomeHash> void fill_data(SomeHash &hmap, int num_pairs) {
  for (int i = 0; i < num_pairs; i++) {
    hmap[uint64_t(i)] = double(i);
  }
}

template <class SomeHash> void query_data(SomeHash &hmap, int num_pairs) {
  // make a vector of 0 to num_pairs
  std::vector<uint64_t> keys(num_pairs);
  std::iota(keys.begin(), keys.end(), 0);
  // shuffle the vector
  std::random_shuffle(keys.begin(), keys.end());
  for (auto key : keys) {
    auto it = hmap.find(key);
    assert(it != hmap.end());
    if constexpr (std::is_same<SomeHash,
                               tsl::hopscotch_map<uint64_t, double>>()) {
      it.value() += 1.0;
    } else {
      it->second += 1.0;
    }
  }
}

int main() {
  absl::flat_hash_map<uint64_t, double> a_map;
  std::vector<int> sizes({10000, 40000, 160000, 640000});
  for (auto size : sizes) {
    std::cout << "Size of map: " << size << std::endl;
    std::cout << "Benchmarking absl::flat_hash_map" << std::endl;
    std::chrono::high_resolution_clock::time_point t1 =
        std::chrono::high_resolution_clock::now();
    fill_data<absl::flat_hash_map<uint64_t, double>>(a_map, size);
    std::chrono::high_resolution_clock::time_point t2 =
        std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span =
        std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
    std::cout << "Insertion time: " << time_span.count() << " mus" << std::endl;
    t1 = std::chrono::high_resolution_clock::now();
    query_data<absl::flat_hash_map<uint64_t, double>>(a_map, size);
    t2 = std::chrono::high_resolution_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
    std::cout << "Query time: " << time_span.count() << " mus" << std::endl;

    tsl::hopscotch_map<uint64_t, double> h_map;
    std::cout << "Benchmarking tsl::hopscotch_map" << std::endl;
    t1 = std::chrono::high_resolution_clock::now();
    fill_data<tsl::hopscotch_map<uint64_t, double>>(h_map, size);
    t2 = std::chrono::high_resolution_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
    std::cout << "Insertion time: " << time_span.count() << " mus" << std::endl;
    t1 = std::chrono::high_resolution_clock::now();
    query_data<tsl::hopscotch_map<uint64_t, double>>(h_map, size);
    t2 = std::chrono::high_resolution_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
    std::cout << "Query time: " << time_span.count() << " mus" << std::endl;
  }
  return 0;
}
