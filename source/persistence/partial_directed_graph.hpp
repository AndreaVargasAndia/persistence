// Copyright 2021 Roger Peralta Aranibar
#ifndef SOURCE_PERSISTENCE_PARTIAL_DIRECTED_GRAPH_HPP_
#define SOURCE_PERSISTENCE_PARTIAL_DIRECTED_GRAPH_HPP_

#include <utility>
#include <vector>
//unsigned namespace std;

namespace ADE {
namespace Persistence {


template <typename Type>
class PartialNode {
public:

  typedef Type data_type;

  PartialNode() {}

  PartialNode(data_type const& data, std::size_t const& out_ptrs_size,std::size_t const& in_ptrs_size)
  {
    data_= new data_type(data);
    out_ptrs_size_=out_ptrs_size;
    in_ptrs_size_=in_ptrs_size;
    backward_ = new PartialNode<Type>*[in_ptrs_size]();
    forward_ = new PartialNode<Type>*[out_ptrs_size]();
  }

  data_type get_data(unsigned int version)
  {
      return *data_;
  }

  bool set_data(data_type const& data)
  {
      return true;
  }

  PartialNode* insert_vertex_p(std::size_t const& position,data_type const& data)
  {
    if (out_ptrs_size_ < position){
            throw std::out_of_range("Insert position is out of edges range.");
    }
    std::cout<<"---->"<<data<<"--- "<<position<<" \n";
    PartialNode* next_node_ptr = forward_[position];
    //std::cout<<"weee"<<get_data(0)<<"\n";
    PartialNode* new_node = new PartialNode(data,out_ptrs_size_,in_ptrs_size_);
    new_node->forward_[position] = next_node_ptr;
    //backward_[position]=new_node;
    //std::cout<<"weee"<<forward_[position]->get_data(0)<<"\n";
    //next_node_ptr->backward_[position-1] = new_node;

    forward_[position] = new_node;
    return forward_[position];
    //return nullptr;
  }

  bool update_edge(std::size_t const& position, PartialNode* v)
  {
    if (out_ptrs_size_ < position) {
            throw std::out_of_range("Position out of first argument node.");
    }
    //std::cout<<"ant"<<forward_[position-1]->get_data(0)<<"\n";
    //std::cout<<"actual"<<v->get_data(0)<<"\n";

    std::cout<<"actualll: "<<get_data(0)<<"\n";
    forward_[position] = v;
    backward_[position]=forward_[position-1];
    //std::cout<<"ant-> "<<v->backward_[position]->get_data(0)<<"\n";
    //backward_[position-1]=v;
    return true;
  }

  PartialNode& operator[](std::pair<std::size_t, unsigned int> const& position_version) const {
                                   //posicion     //version
    if (out_ptrs_size_ < position_version.second) {
            throw std::out_of_range("Index out of node edges range.");
    }
    if (!forward_[position_version.first]) {
            throw std::logic_error("Access to null reference.");
    }
    //std::cout<<"**ps "<<position_version.first<<"\n";
    return *forward_[position_version.first];
    //return;
  }

  data_type* data_;
  std::size_t out_ptrs_size_;
  std::size_t in_ptrs_size_;

  std::size_t current_modifications_size_;
  std::size_t current_back_pointer_size_;

  PartialNode** backward_;
  PartialNode** forward_;
  //std::vector<int> mod(2*in_ptrs_size_);
  // TODO: Table mods, 2 * in_ptrs_size_
};


template <typename Type, typename Node>
class PartialDirectedGraph {
public:

  typedef Type data_type;

  PartialDirectedGraph(data_type const data, std::size_t const& out_ptrs_size,std::size_t const& in_ptrs_size)
  {
      root_ptr_=new Node(data,out_ptrs_size,in_ptrs_size);
      out_ptrs_size_=out_ptrs_size;
      in_ptrs_size_=in_ptrs_size;
  }

  Node* get_root_ptr(unsigned int const& version)
  {
      return root_ptr_;//+version
  }

  Node get_root(unsigned int const& version)
  {
      return *root_ptr_; //[version]
  }

  bool add_edge(Node* u, Node* v, std::size_t position)
  {
    if (u->out_ptrs_size_ < position) {
      throw std::out_of_range("Position out of first argument node.");
    }
    u->forward_[position] = v;
    v->backward_[position]=u;
    ++(*current_version_);
    //std::cout<<*current_version_<<"\n";
    //new_version()
    return true;
  }
  void print_()
  {
      Node* a=get_root_ptr(0);
      std::cout<<"root "<<a->get_data(0)<<"\n";
      std::cout<<"forward "<<a->forward_[0]->get_data(0)<<"-"<<a->forward_[1]->get_data(0)<<"- "<< a->forward_[2]->get_data(0)<<"\n";//<<a->forward_[2]->get_data(0)
      std::cout<<"backward "<<a->backward_[2]->get_data(0)<<"-"<<a->backward_[1]->get_data(0)<<"- "<< a->backward_[0]->get_data(0)<<"\n";
  }

 protected:
  unsigned int* current_version_;

  std::size_t in_ptrs_size_;
  std::size_t out_ptrs_size_;

  Node* root_ptr_;

};

}  // namespace Persistence
}  // namespace ADE

#endif  // SOURCE_PERSISTENCE_PARTIAL_DIRECTED_GRAPH_HPP_
