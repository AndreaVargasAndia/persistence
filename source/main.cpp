// Copyright 2021 Roger Peralta Aranibar
#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>
#include <utility>

// TODO: Uncommend after implement the partial structure
#include "partial_directed_graph.h"
//#include "directed_graph.h"

void test_directed_graph() {
  std::cout << "Directed Graph"
            << "\n";
  ADE::Persistence::PartialDirectedGraph<int,ADE::Persistence::PartialNode<int>> my_graph(-1,2, 5);
  ADE::Persistence::PartialNode<int>* root_ptr = my_graph.get_root_ptr(0);
  std::cout << "Root Value: " << root_ptr->get_data(0) << "\n";  // 5

  my_graph.get_root(0).insert_vertex_p(0, 2);  // 5[0] -> 2

  //my_graph.get_root(0).update_edge(0,root_ptr);
  //----------------------------------
  std::pair<std::size_t, unsigned int> pos_version;
  pos_version.first=0;
  pos_version.second=0;
  std::cout << "Inserted Value: " << my_graph.get_root(0)[pos_version].get_data(0)
            << "\n";

  std::pair<std::size_t, unsigned int> pos_v;
  pos_v.first= 1;
  pos_v.second=0;
  //my_graph.get_root(0).print_(root_ptr);
  ADE::Persistence::PartialNode<int>* other_inserted_node_ptr = my_graph.get_root(0)[pos_version].insert_vertex_p(1,8);  // 5[0] -> 2[1] -> 3

  std::cout << "Inserted Value: " << my_graph.get_root(0)[pos_version][pos_v].get_data(0)
            << "\n{{{{{{{{{{{{{{{{{{{{ \n";
  //----------------------------------
  my_graph.get_root(0).update_edge(1,other_inserted_node_ptr);

///-----------------------------------
  std::pair<std::size_t, unsigned int> pos_;
  pos_.first= 1;
  pos_.second=0;
  //std::cout<<"hi "<<my_graph.get_root(0)[pos_].get_data(0)<<"\n";
  //my_graph.print_();
  ADE::Persistence::PartialNode<int>* other_node = my_graph.get_root(0)[pos_].insert_vertex_p(2,6);  // 5[0] -> 2[1] -> 3

  std::pair<std::size_t, unsigned int> pos_v2;
  pos_v2.first= 2;
  pos_v2.second=0;
  std::cout << "Inserted Value: " << my_graph.get_root(0)[pos_][pos_v2].get_data(0)
            << "\n";
///-----------------------------------
  //my_graph.get_root(0).print_();
  my_graph.get_root(0).update_edge(2,other_node); // 5[0] -> 2[1] ->
                                                             // 3 5[1]   -> 3
  std::cout << "Following other Edge: " << my_graph.get_root(0)[pos_v].get_data(0)
            << "\n";
  my_graph.print_();
}

int main() {
  test_directed_graph();

  return 0;
}

