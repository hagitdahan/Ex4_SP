// tree.hpp
#ifndef TREE_HPP
#define TREE_HPP
#include "node.hpp"
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <sstream>
#include <SFML/Graphics.hpp>
/**
 * @brief A generic Tree class template.
 * 
 * @tparam T The type of data stored in each node.
 * @tparam order The maximum number of children each node can have.
 */
template <typename T, int order = 2>
class Tree {
private:
    Node<T>* root;
    //function that get the first node and insert the nodes in the tree to pre_order vector
    void pre_order(Node<T>* node, std::vector<Node<T>*>& nodes) {
        if (!node) return;
        nodes.push_back(node);
        for (Node<T>* child : node->children) {
            pre_order(child, nodes);
        }
    }
    //function that get the first node and insert the nodes in the tree to pre_order vector
    void post_order(Node<T>* node, std::vector<Node<T>*>& nodes) {
        if (!node) return;
        for (Node<T>* child : node->children) {
            post_order(child, nodes);
        }
        nodes.push_back(node);
    }
    //function that get the first node and insert the nodes in the tree to pre_order vector
    void in_order(Node<T>* node, std::vector<Node<T>*>& nodes) {
        if (!node) return;
        if (!node->children.empty()) {
            in_order(node->children[0], nodes);
        }
        nodes.push_back(node);
        for (size_t i = 1; i < node->children.size(); ++i) {
            in_order(node->children[i], nodes);
        }
    }
    //function that get the first node and insert the nodes in the tree to pre_order vector
    void bfs(Node<T>* node, std::vector<Node<T>*>& nodes) {
        if (!node) return;
        std::queue<Node<T>*> queue;
        queue.push(node);
        while (!queue.empty()) {
            Node<T>* current = queue.front();
            queue.pop();
            nodes.push_back(current);
            for (Node<T>* child : current->children) {
                queue.push(child);
            }
        }
    }
    //function that get the first node and insert the nodes in the tree to pre_order vector
    void dfs(Node<T>* node, std::vector<Node<T>*>& nodes) {
        if (!node) return;
        std::stack<Node<T>*> stack;
        stack.push(node);
        while (!stack.empty()) {
            Node<T>* current = stack.top();
            stack.pop();
            nodes.push_back(current);
            for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                stack.push(*it);
            }
        }
    }
    // Heapify method to maintain min-heap property
    void heapify(Node<T>* node) {
        if (!node) return;
        Node<T>* smallest = node;
        for (Node<T>* child : node->children) {
            if (child && child->value < smallest->value) {
                smallest = child;
            }
        }
        if (smallest != node) {
            std::swap(node->value, smallest->value);
            heapify(smallest);
        }
    }

public:
    /**
     * @brief Constructor for Tree class.
     */
    Tree() : root(nullptr) {}
    /**
     * @brief Destructor for Tree class.
     */
    ~Tree() {
        delete_tree(root);
    }
    /**
     * @brief Draw the tree structure on an SFML window.
     * 
     * @param window Reference to the SFML RenderWindow object.
     * @param tree Reference to the Tree object.
     * @param node Current node to draw.
     * @param x X-coordinate for drawing.
     * @param y Y-coordinate for drawing.
     * @param horizontal_gap Horizontal gap between nodes.
     * @param font Font used for text rendering.
     */
    void draw_tree(sf::RenderWindow& window, Tree<T, order>& tree,Node<T>* node, int x, int y, int horizontal_gap, sf::Font& font){
         if (!node) return;

        // Drawing circle and lines...
        sf::Color circleColor = sf::Color::Blue; // Red color for circles
        sf::Color outlineColor = sf::Color::Black; // Black color for circle outline
        sf::Color textColor = sf::Color::Black; // Black color for text

        // Draw circle
        sf::CircleShape circle(30); // Circle radius
        circle.setFillColor(circleColor);
        circle.setOutlineThickness(2);
        circle.setOutlineColor(outlineColor);
        circle.setPosition(x, y);
        window.draw(circle);

        // Convert value to string with fixed precision
        T value = node->value;
        std::ostringstream oss;
        oss.precision(1);
        oss << std::fixed << value;
        std::string text = oss.str();

        // Draw text
        sf::Text textObject(text, font, 20);
        textObject.setFillColor(textColor);
        sf::FloatRect textBounds = textObject.getLocalBounds();
        textObject.setOrigin(textBounds.left + textBounds.width / 2.0f,
                            textBounds.top + textBounds.height / 2.0f);
        textObject.setPosition(x + circle.getRadius(), y + circle.getRadius());
        window.draw(textObject);

        // Draw lines to children
        auto children = node->children;
        int num_children = children.size();
        if (num_children > 0) {
            for (int i = 0; i < num_children; ++i) {
                int child_x = x - horizontal_gap / 2 + i * horizontal_gap;
                int child_y = y + 100;

                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x + circle.getRadius(), y + 2 * circle.getRadius())),
                    sf::Vertex(sf::Vector2f(child_x + circle.getRadius(), child_y))
                };
                line[0].color = sf::Color::Black;
                line[1].color = sf::Color::Black;
                window.draw(line, 2, sf::Lines);

                draw_tree(window, tree, children[i], child_x, child_y, horizontal_gap / 2, font);
            }
        }
    }
    /**
     * @brief Handle events in the SFML window.
     */
    void handle_window(){
        sf::RenderWindow window(sf::VideoMode(800, 600), "Binary Tree Display");
        // Load font
        sf::Font font;
        if (!font.loadFromFile("./Lato-BlackItalic.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
            //return -1;
        }
        window.clear(sf::Color::White); // Clear window with white color
        this->draw_tree(window, *this, this->get_root(), 400, 50, 200, font);
        window.display();
        //Draw the tree starting from the root node
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
        }
    }
    /**
     * @brief Add a root node to the tree.
     * 
     * @param node Node to set as the root.
     */
    void add_root(const Node<T>& node) {
        delete_tree(root); // Clean up any existing tree
        root = new Node<T>(node);
    }
    /**
     * @brief Add a child node to a parent node in the tree.
     * 
     * @param parent_node Parent node to which the child will be added.
     * @param child_node Child node to add.
     * @throws std::runtime_error if max children exceeded for parent node or parent node not found.
     */
    void add_sub_node(const Node<T>& parent_node, const Node<T>& child_node) {
        Node<T>* parent = find_node(root, parent_node.value);
        if (parent) {
            if (parent->children.size() < order) {
                parent->children.push_back(new Node<T>(child_node));
            } else {
                throw std::runtime_error("Max children exceeded for parent node.");
            }
        } else {
            throw std::runtime_error("Parent node not found in the tree.");
        }
    }
    /**
     * @brief Find a node in the tree by its value.
     * 
     * @param current Current node to start searching from.
     * @param value Value to search for.
     * @return Node pointer if found, nullptr otherwise.
     */
    Node<T>* find_node(Node<T>* current, T value) {
        if (!current) return nullptr;
        if (current->value == value) return current;
        for (Node<T>* child : current->children) {
            Node<T>* result = find_node(child, value);
            if (result) return result;
        }
        return nullptr;
    }
    /**
     * @brief Get the root node of the tree.
     * 
     * @return Node pointer to the root.
     */
    Node<T>* get_root() const {
        return root;
    }
    /**
     * @brief Iterator class for iterating over nodes in the tree.
     */
    class Iterator {
    private:
        typename std::vector<Node<T>*>::iterator it;
    public:
        /**
         * @brief Iterator constructor.
         * 
         * @param it Iterator pointing to a position in the vector of nodes.
         */
        Iterator(typename std::vector<Node<T>*>::iterator it) : it(it) {}
        /**
         * @brief Dereference operator.
         * @return Reference to the node pointed by the iterator.
         */
        Node<T>& operator*() { return **it; }
        /**
         * @brief Member access operator. 
         * @return Pointer to the node pointed by the iterator.
         */
        Node<T>* operator->() { return *it; }
        /**
         * @brief Pre-increment operator.
         * 
         * @return Reference to the iterator after increment.
         */
        Iterator& operator++() {
            ++it;
            return *this;
        }
        /**
         * @brief Post-increment operator.
         * 
         * @return Copy of the iterator before increment.
         */
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++it;
            return tmp;
        }
         /**
         * @brief Equality comparison operator.
         * 
         * @param other Another iterator to compare with.
         * @return true if both iterators are equal, false otherwise.
         */
        bool operator==(const Iterator& other) const { return it == other.it; }
        /**
         * @brief Inequality comparison operator.
         * 
         * @param other Another iterator to compare with.
         * @return true if iterators are not equal, false if they are.
         */
        bool operator!=(const Iterator& other) const { return it != other.it; }
    };

    Iterator begin_pre_order() {
        if(order==2){
            pre_order_nodes.clear();
            pre_order(root, pre_order_nodes);
            return Iterator(pre_order_nodes.begin());
        }
        return begin_dfs_scan();
        
    }

    Iterator end_pre_order() {
        if(order==2){
            return Iterator(pre_order_nodes.end());
        }
        return end_dfs_scan();
        
    }

    Iterator begin_post_order() {
        if(order==2){
            post_order_nodes.clear();
            post_order(root, post_order_nodes);
            return Iterator(post_order_nodes.begin());
        }
        return begin_dfs_scan();
       
    }

    Iterator end_post_order() {
        if(order==2){
            return Iterator(post_order_nodes.end());
        }
        return end_dfs_scan();
    }

    Iterator begin_in_order() {
        if(order==2){
            in_order_nodes.clear();
            in_order(root, in_order_nodes);
            return Iterator(in_order_nodes.begin());
        }
        return begin_dfs_scan();
    }

    Iterator end_in_order() {
        if(order==2){
            return Iterator(in_order_nodes.end());
        }
        return end_dfs_scan();
    }

    Iterator begin_bfs_scan() {
        bfs_nodes.clear();
        bfs(root, bfs_nodes);
        return Iterator(bfs_nodes.begin());
    }

    Iterator end_bfs_scan() {
        return Iterator(bfs_nodes.end());
    }

    Iterator begin_dfs_scan() {
        dfs_nodes.clear();
        dfs(root, dfs_nodes);
        return Iterator(dfs_nodes.begin());
    }

    Iterator end_dfs_scan() {
        return Iterator(dfs_nodes.end());
    }
    
    Iterator begin() {
        return begin_bfs_scan();
    }

    Iterator end() {
        return end_bfs_scan();
    }
    /**
     * @brief Delete the entire tree.
     * 
     * @param node Root node of the subtree to delete.
     */
    void delete_tree(Node<T>* node) {
        if (!node) return;
        for (Node<T>* child : node->children) {
            delete_tree(child);
        }
        delete node;
    }
    /**
     * @brief Convert the tree into a min-heap structure.
     */
    void myHeap() {
        if (!root) return;
        heap_nodes.clear();
        bfs(root, heap_nodes); // Collect nodes in BFS order

        // Custom comparator lambda for Node values
        auto node_value_comparator = [](Node<T>* a, Node<T>* b) {
        return a->value < b->value; // Min-heap: smallest value at the top
        };

        // Convert values to a min-heap
        std::make_heap(heap_nodes.begin(), heap_nodes.end(), node_value_comparator);
        
        // Sort the heap
        std::sort_heap(heap_nodes.begin(), heap_nodes.end(), node_value_comparator);
    }

    Iterator begin_heap() {
        this->myHeap();
        return Iterator(heap_nodes.begin());
    }

    Iterator end_heap() {
        return Iterator(heap_nodes.end());
    }

private:
    // Private member variables to store nodes in different orders
    std::vector<Node<T>*> pre_order_nodes;
    std::vector<Node<T>*> post_order_nodes;
    std::vector<Node<T>*> in_order_nodes;
    std::vector<Node<T>*> bfs_nodes;
    std::vector<Node<T>*> dfs_nodes;
    std::vector<Node<T>*> heap_nodes;
};

#endif // TREE_HPP