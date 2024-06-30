#ifndef NODE_HPP
#define NODE_HPP
#include "Complex.hpp"
#include <vector>

/**
 * @brief A class template representing a node in a tree structure.
 * 
 * @tparam T The type of value stored in the node.
 */
template <typename T>
class Node {
public:
    //explicit Node(T value){}
    /**
     * @brief Constructor to initialize the node with a value.
     * 
     * @param val The value to be stored in the node.
     */
    explicit Node(T val) : value(val) {}
    /**
     * @brief Destructor for the Node class.
     * 
     * This destructor does not perform any specific cleanup since children nodes
     * are managed separately.
     */
    ~Node() {}
     /**
     * @brief Getter function to retrieve the value stored in the node.
     * 
     * @return The value stored in the node.
     */
    T get_value() const { return value; }
     /**
     * @brief Getter function to retrieve the childrens of the node.
     * 
     * @return The value stored in the node.
     */
    std::vector<Node<T>*>&getChildrens(){return childrens;}
    void addChildren(const Node<T>& newNode){childrens.push_back(new Node<T>(newNode));}
private:
    T value;
    std::vector<Node<T>*> childrens;

};


#endif // NODE_HPP
