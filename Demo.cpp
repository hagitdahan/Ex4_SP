#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include <SFML/Graphics.hpp> // SFML header for graphics
using namespace std;

int main() {
    Node<double> root_node =Node(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1 = Node(1.2);
    Node<double> n2 = Node(1.3);
    Node<double> n3 = Node(1.4);
    Node<double> n4 = Node(1.5);
    Node<double> n5 = Node(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    //The tree should look like:
    /**
    *       root = 1.1
    *     /       \
    *    1.2      1.3
    *   /  \      /
    *  1.4  1.5  1.6
    */
    tree.handle_window();
  
    cout << "Pre-order traversal:" << endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << endl;
    } //prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
        
    cout << "Post-order traversal:" << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node->get_value() << endl;
    } //prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1

    cout << "In-order traversal:" << endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_value() << endl;
    } //prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

    cout << "BFS traversal:" << endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << node->get_value() << endl;
    } //prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout << "DFS traversal:" << endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
        cout << node->get_value() << endl;
    } //prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
        
    cout << "same as BFS traversal:" << endl;
    for (auto node : tree)
    {
        cout << node.get_value() << endl;
    } //same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
        
    cout << "Min-Heap:" << endl;
    for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node) {
        cout << node->get_value() << endl;
    }

    Tree<double,3> three_ary_tree; //3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    //The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */
    
    three_ary_tree.handle_window();
    
    cout << "run pre-order traversal on three ary tree:" << endl;
    for (auto node = three_ary_tree.begin_pre_order(); node != three_ary_tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << endl;
    } //prints like dfs: 1.1, 1.2, 1.5, 1.3, 1.6, 1.4

    cout << "run post-order traversal on three ary tree:" << endl;
    for (auto node = three_ary_tree.begin_post_order(); node != three_ary_tree.end_post_order(); ++node)
    {
        cout << node->get_value() << endl;
    } //prints like dfs: 1.1, 1.2, 1.5, 1.3, 1.6, 1.4
        
    cout << "run in-order traversal on three ary tree:" << endl;
    for (auto node = three_ary_tree.begin_in_order(); node != three_ary_tree.end_in_order(); ++node)
    {
        cout << node->get_value() << endl;
    } //prints like dfs: 1.1, 1.2, 1.5, 1.3, 1.6, 1.4

    Node<std::string> rootStr("hello");
    Tree<std::string> treeStr; // Binary tree that contains doubles.
    treeStr.add_root(rootStr);
    Node<std::string> node1("my");
    Node<std::string> node2("name");
    Node<std::string> node3("is");
    Node<std::string> node4("hagit");
    Node<std::string> node5("dahan");
    Node<std::string> node6("bye");

    treeStr.add_sub_node(rootStr,node1);
    treeStr.add_sub_node(rootStr,node2);
    treeStr.add_sub_node(node1,node3);
    treeStr.add_sub_node(node1,node4);
    treeStr.add_sub_node(node2,node5);
    treeStr.add_sub_node(node2,node6);
    
    treeStr.handle_window();
    
    cout << "Min-Heap:" << endl;
    for (auto node = treeStr.begin_heap(); node != treeStr.end_heap(); ++node) {
        cout << node->get_value() << endl;
    }// bye dahan hagit hello is my name

    Tree<Complex> tree_complex;
    tree_complex.add_root(Node<Complex>(Complex(1.0, 2.0)));
    tree_complex.add_sub_node(Node<Complex>(Complex(1.0, 2.0)), Node<Complex>(Complex(3.0, 4.0)));
    tree_complex.add_sub_node(Node<Complex>(Complex(1.0, 2.0)), Node<Complex>(Complex(5.0, 6.0)));

    
    tree_complex.handle_window();

    Node<int> root_node_int=Node(1);
    Tree<int> tree_int; // Binary tree that contains doubles.
    tree_int.add_root(root_node_int);
    Node<int> n1_ = Node(2);
    Node<int> n2_ = Node(3);
    

    tree_int.add_sub_node(root_node_int, n1_);
    tree_int.add_sub_node(root_node_int, n2_);
     
    tree_int.handle_window();




    return 0;
    }
