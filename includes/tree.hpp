#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>
#include <iterator>
#include <memory>

namespace ft
{
    template <class T>
    class tree_iterator_ : public std::iterator<std::bidirectional_iterator_tag, T>
    {
    public:
        typedef T iterator_type;
        typedef typename iterator_traits<T>::iterator_category iterator_category;
        typedef typename iterator_traits<T>::value_type value_type;
        typedef typename iterator_traits<T>::difference_type difference_type;
        typedef typename iterator_traits<T>::pointer pointer;
        typedef typename iterator_traits<T>::reference reference;

        // Member functions
        // constructor
        tree_iterator_() : current(NULL) {}
        explicit tree_iterator_(iterator_type ptr) : current(ptr) {}
        // copy constructor
        template <class Iter>
        tree_iterator_(const tree_iterator_<Iter> &other)
        {
            *this = other;
        }
        // assignment operator
        template <class Iter>
        tree_iterator_ &operator=(const tree_iterator_<Iter> &other)
        {
            current = other.base();
            return *this;
        }

        iterator_type base() const
        {
            return current;
        }
        // dereference operator
        reference operator*() const
        {
            return *current;
        }
        pointer operator->() const
        {
            return current;
        }
        // prefix/postfix increment
        tree_iterator_ &operator++()
        {
            current++;
            return *this;
        }
        tree_iterator_ operator++(int)
        {
            tree_iterator_ tmp = *this;
            current++;
            return tmp;
        }
        // prefix/postfix decrement
        tree_iterator_ &operator--()
        {
            current--;
            return *this;
        }
        tree_iterator_ operator--(int)
        {
            tree_iterator_ tmp = *this;
            current--;
            return tmp;
        }

    private:
        iterator_type current;
    };

    template <class T>
    class rb_node_
    {
    public:
        rb_node_ *parent;
        rb_node_ *left;
        rb_node_ *right;
        bool color;
        T key;

        static const bool BLACK = true;
        static const bool RED = false;

        rb_node_() : parent(NULL), left(NULL), right(NULL), color(BLACK) {}
        rb_node_(rb_node_ *nil, const T &key)
            : parent(nil), left(nil), right(nil), color(RED), key(key) {}
    };

    template <class T, class Compare,
              class Allocator = std::allocator<rb_node_<T> > >
    class rb_tree_
    {
    private:
        typedef T key_type;
        typedef rb_node_<T> *link_type;
        typedef const rb_node_<T> *const_link_type;

        link_type nil_;
        link_type root_;
        Allocator alloc_;
        Compare compare_;

        link_type create_node(const key_type &key)
        {
            link_type new_node = alloc_.allocate(1);
            alloc_.construct(new_node, nil_, key);
            return new_node;
        }

        void rotate_left(link_type node)
        {
            link_type y = node->right;
            node->right = y->left;
            if (y->left != nil_)
                y->left->parent = node;
            y->parent = node->parent;
            if (node->parent == nil_)
                root_ = y;
            else if (node == node->parent->left)
                node->parent->left = y;
            else
                node->parent->right = y;
            y->left = node;
            node->parent = y;
        }

        void rotate_right(link_type node)
        {
            link_type y = node->left;
            node->left = y->right;
            if (y->right != nil_)
                y->right->parent = node;
            y->parent = node->parent;
            if (node->parent == nil_)
                root_ = y;
            else if (node == node->parent->right)
                node->parent->right = y;
            else
                node->parent->left = y;
            y->right = node;
            node->parent = y;
        }

        void insert_fixup(link_type node)
        {
            while (node->parent->color == rb_node_<T>::RED)
            {
                if (node->parent == node->parent->parent->left)
                {
                    link_type y = node->parent->parent->right;
                    if (y->color == rb_node_<T>::RED)
                    {
                        node->parent->color = rb_node_<T>::BLACK;
                        y->color = rb_node_<T>::BLACK;
                        node->parent->parent->color = rb_node_<T>::RED;
                        node = node->parent->parent;
                    }
                    else
                    {
                        if (node == node->parent->right)
                        {
                            node = node->parent;
                            rotate_left(node);
                        }
                        node->parent->color = rb_node_<T>::BLACK;
                        node->parent->parent->color = rb_node_<T>::RED;
                        rotate_right(node->parent->parent);
                    }
                }
                else
                {
                    link_type y = node->parent->parent->left;
                    if (y->color == rb_node_<T>::RED)
                    {
                        node->parent->color = rb_node_<T>::BLACK;
                        y->color = rb_node_<T>::BLACK;
                        node->parent->parent->color = rb_node_<T>::RED;
                        node = node->parent->parent;
                    }
                    else
                    {
                        if (node == node->parent->left)
                        {
                            node = node->parent;
                            rotate_right(node);
                        }
                        node->parent->color = rb_node_<T>::BLACK;
                        node->parent->parent->color = rb_node_<T>::RED;
                        rotate_left(node->parent->parent);
                    }
                }
            }
            root_->color = rb_node_<T>::BLACK;
        }

        void delete_fixup(link_type node)
        {
            link_type sibling;
            while (node != root_ && node->color == rb_node_<T>::BLACK)
            {
                if (node == node->parent->right)
                {
                    sibling = node->parent->right;
                    if (sibling->color == rb_node_<T>::RED)
                    {
                        sibling->color = rb_node_<T>::BLACK;
                        node->parent->color = rb_node_<T>::RED;
                        rotate_left(node->parent);
                        sibling = node->parent->right;
                    }
                    if (sibling->left->color == rb_node_<T>::BLACK &&
                        sibling->right->color == rb_node_<T>::BLACK)
                    {
                        sibling->color = rb_node_<T>::RED;
                        node = node->parent;
                    }
                    else
                    {
                        if (sibling->right->color == rb_node_<T>::BLACK)
                        {
                            sibling->left->color = rb_node_<T>::BLACK;
                            sibling->color = rb_node_<T>::RED;
                            rotate_right(sibling);
                            sibling = node->parent->right;
                        }
                        sibling->color = node->parent->color;
                        node->parent->color = rb_node_<T>::BLACK;
                        sibling->right->color = rb_node_<T>::BLACK;
                        rotate_left(node->parent);
                        node = root_;
                    }
                }
                else
                {
                    sibling = node->parent->left;
                    if (sibling->color == rb_node_<T>::RED)
                    {
                        sibling->color = rb_node_<T>::BLACK;
                        node->parent->color = rb_node_<T>::RED;
                        rotate_right(node->parent);
                        sibling = node->parent->left;
                    }
                    if (sibling->right->color == rb_node_<T>::BLACK &&
                        sibling->left->color == rb_node_<T>::BLACK)
                    {
                        sibling->color = rb_node_<T>::RED;
                        node = node->parent;
                    }
                    else
                    {
                        if (sibling->left->color == rb_node_<T>::BLACK)
                        {
                            sibling->right->color = rb_node_<T>::BLACK;
                            sibling->color = rb_node_<T>::RED;
                            rotate_left(sibling);
                            sibling = node->parent->left;
                        }
                        sibling->color = node->parent->color;
                        node->parent->color = rb_node_<T>::BLACK;
                        sibling->left->color = rb_node_<T>::BLACK;
                        rotate_right(node->parent);
                        node = root_;
                    }
                }
            }
            node->color = rb_node_<T>::BLACK;
        }

        link_type find_node(const key_type &key) const
        {
            link_type node = root_;
            while (node != nil_)
            {
                if (compare_(key, node->key))
                    node = node->left;
                else if (compare_(node->key, key))
                    node = node->right;
                else
                    return node;
            }
            return nil_;
        }

        link_type search_min_node(link_type node) const
        {
            while (node->left != nil_)
            {
                node = node->left;
            }
            return node;
        }

        void transplant(link_type x, link_type y)
        {
            if (x->parent == nil_)
                root_ = y;
            else if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
            y->parent = x->parent;
        }

        link_type replace_node(link_type node, bool &deleted_color)
        {
            deleted_color = node->color;
            link_type replaced_node;
            if (node->left == nil_)
            {
                replaced_node = node->right;
                transplant(node, node->right);
            }
            else if (node->right == nil_)
            {
                replaced_node = node->left;
                transplant(node, node->left);
            }
            else
            {
                link_type y = search_min_node(node->right);
                deleted_color = y->color;
                replaced_node = y->right;
                if (y->parent == node)
                {
                    replaced_node->parent = y;
                }
                else
                {
                    transplant(y, y->right);
                    y->right = node->right;
                    y->right->parent = y;
                }
                transplant(node, y);
                y->left = node->left;
                y->left->parent = y;
                y->color = node->color;
            }
            return replaced_node;
        }

    public:
        rb_tree_()
        {
            alloc_ = Allocator();
            nil_ = alloc_.allocate(1);
            alloc_.construct(nil_);
            nil_->left = nil_;
            nil_->right = nil_;
            root_ = nil;
            compare_ = Compare();
        }

        ~rb_tree_()
        {
            destroy(root_);
            alloc_.destroy(nil_);
            alloc_.deallocate(nil_, 1);
        }

        void destroy(link_type node)
        {
            if (node != nil_)
            {
                destroy(node->left);
                destroy(node->right);
                alloc_.destroy(node);
                alloc_.deallocate(node, 1);
            }
        }

        void insert_node(const key_type &key)
        {
            link_type new_node = create_node(key);
            link_type prev_node = nil_;
            link_type now_node = root_;
            while (now_node != nil_)
            {
                prev_node = now_node;
                if (compare_(key, now_node->key))
                    now_node = now_node->left;
                else
                    now_node = now_node->right;
            }
            new_node->parent = prev_node;
            if (prev_node == nil_)
                root_ = new_node;
            else if (compare_(key, prev_node->key))
                prev_node->left = new_node;
            else
                prev_node->right = new_node;
            insert_fixup(new_node);
        }

        void delete_node(const key_type &key)
        {
            link_type node = find_node(key);
            if (node == nil_)
                return;

            bool deleted_color;
            link_type replaced = replace_node(node, deleted_color);
            if (deleted_color == rb_node_<T>::BLACK)
                delete_fixup(replaced);
            alloc_.destroy(node);
            alloc_.deallocate(node, 1);
        }

    };

} /* namespace ft */

#endif /* TREE_HPP */
