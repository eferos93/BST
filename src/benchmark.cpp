#include <iostream>
#include <bst.hxx>
#include <chrono>
#include <map>
#include <random>
#include <fstream>
#include <vector>


int main() {

    const int N{10000}; // Number of elements to be inserted and found 

    std::ofstream outFile;
    outFile.open("../benchmark/benchmark_times.txt");

    //For generating random numbers
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,100000); 

    std::vector<int> numbers;
    for(int j = 0; j <= N; ++j){
      numbers.push_back(dist(rng));
    }

    bst<int,std::string> b;   // unbalanced tree
    bst<int,std::string> balb; // balanced tree
    std::map<int,std::string> m; // maps


for (size_t i = 100; i <= N; i+=10)
{
    for(size_t k = 0; k < i; ++k){
        //std::cout << dist(rng) << std::endl;
        b.insert({numbers[k],std::to_string(numbers[k])});
        balb.insert({numbers[k],std::to_string(numbers[k])});
        m.insert({numbers[k],std::to_string(numbers[k])});
    }  

    //measuring time to find keys with std::map
  	auto t0_map = std::chrono::steady_clock::now();
   	for(size_t k = 0 ; k < i; ++k){
 		  m.find(numbers[k]);
  	}
	  auto t1_map = std::chrono::steady_clock::now();
	  auto elapsed_map = std::chrono::duration_cast<std::chrono::microseconds>(t1_map-t0_map);  

    
    //measuring time to find keys with unbalanced bst
  	auto t0_bst = std::chrono::steady_clock::now();
   	for(size_t k = 0; k < i; ++k){
 		  b.find(numbers[k]);
  	}
	  auto t1_bst = std::chrono::steady_clock::now();
	  auto elapsed_bst = std::chrono::duration_cast<std::chrono::microseconds>(t1_bst-t0_bst);

    //measuring time to find keys with balanced bst
        balb.balance();
  	auto t0_bst_bal = std::chrono::steady_clock::now();
   	for(size_t k{0}; k < i; ++k){
 		  balb.find(numbers[k]);
  	}
	  auto t1_bst_bal = std::chrono::steady_clock::now();
	  auto elapsed_bst_bal = std::chrono::duration_cast<std::chrono::microseconds>(t1_bst_bal-t0_bst_bal);

    // write results to file
    outFile << i << "\t" << (double(elapsed_map.count()))/((double)N) << "\t" << (double(elapsed_bst.count()))/((double)N) << "\t" << (double(elapsed_bst_bal.count()))/((double)N) << "\n";
}
	  outFile.close();
	  return 0; 

}