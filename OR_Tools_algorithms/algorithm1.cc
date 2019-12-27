#include "../ortools/include/ortools/algorithms/knapsack_solver.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <chrono>


namespace operations_research{
   //=========================================================== main
std::vector<int> KnapsackExample(std::vector<int64> &values,std::vector<std::vector<int64>> &weights, std::vector<int64> &capacities ){
    KnapsackSolver solver(KnapsackSolver::KNAPSACK_DYNAMIC_PROGRAMMING_SOLVER, "SimpleKnapsackExample");
    solver.Init(values, weights, capacities);
    int64 computed_value = solver.Solve();
    std::cout << "Total value: " << computed_value << std::endl;

    std::vector<int> packed_items;
    for (std::size_t i = 0; i < values.size(); ++i)
    {
        if (solver.BestSolutionContains(i)) {
           // std::cout << "Item " << i + 1 << " is in the bag" << std::endl;
            packed_items.push_back(i);
            }
    }
    return packed_items;
}
} // namespace operations_research


//=========================================================== main


 int main(int argc, char *argv[]){
  std::cout << "arguments= "<<argc<<" \n";
  if (argc!=3)  {
      std::cout << "No correct arguments \n";
	    exit(0);
	}
  
  std::cout << "--- Dynamic Solver by or-tools)\n";
  char* inputFilename = argv[1];
  char* outputFilename = argv[2];
  std::cout <<"Input file: "<< inputFilename<<"\n";
  std::cout <<"Output file: "<< outputFilename<<"\n";

   std::ifstream fin(inputFilename);  
   if (!fin.good()) {    
        std::cerr << "Error opening file " << inputFilename << std::endl; 
        system("pause");
        exit(-1);  
    }

    int items_number;
    fin >> items_number; 
    std::cout<<"items_number= "<<items_number<<"\n";
    std::vector<int64> values;
    std::vector<int64> weights;
    int id;    
    for (int i = 0; i < items_number; i++){
        fin >> id;  
        int v;
        fin >> v;
        values.push_back(v);
        int w;
        fin >> w;
        weights.push_back(w);
       // std::cout<<id<<" "<<v<<" "<<w<<"\n";
    }
    int capacity;
    fin >> capacity;   
    std::cout<<capacity<<"\n";
    
   // std::cout<<"=================="<<"\n";
   // for (int i=0;i<items_number;i++){
  //    std::cout<<i<<" "<<values.at(i)<<" "<<weights.at(i)<<"\n";
 //   }
    
    std::vector<std::vector<int64>> weightsVectors;
    weightsVectors.push_back(weights);
    std::vector<int64> capacities;
    capacities.push_back(capacity);

    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<int> selectedItems = operations_research::KnapsackExample(values,weightsVectors,capacities);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    unsigned long lastSolutionTime = duration.count();
    
    int maxWeight=0;
    int maxProfit=0;
    std::cout<<"------ Item of solution\n";
    for (int i=0;i<selectedItems.size();i++){
      int selectedItem = selectedItems.at(i);
      int itemWeight = weights.at(selectedItem);
      int itemProfit = values.at(selectedItem);
      //std::cout<<itemWeight<<" " << itemWeight <<"\n";
      maxProfit+=itemProfit;
      maxWeight+=itemWeight;
      
    }
    std::cout<<"=====maxWeight="<<maxWeight<<"\n";
    std::cout<<"=====maxProfit="<<maxProfit<<"\n";
    std::cout<<"=====lastSolutionTime="<<lastSolutionTime<<"\n";
    
    
    std::fstream fout;
    //fout.open(outputFilename, std::ios::out);
    fout.open(outputFilename, std::ios::app);
    if (!fout.good()) {     
        std::cerr << "--- Error opening file " << outputFilename << std::endl;
        exit(-1);      
    }
    
    fout <<";"<<maxWeight<<";"<<maxProfit<<";"<<lastSolutionTime;
    
    fout.close();
  
  return EXIT_SUCCESS;
}
