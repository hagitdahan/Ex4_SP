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
    T value;
    std::vector<Node<T>*> children;
    /**
     * @brief Constructor to initialize the node with a value.
     * 
     * @param val The value to be stored in the node.
     */
    Node(T val) : value(val) {}
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
};

#endif // NODE_HPP
