#ifndef TREE_HPP
#define TREE_HPP

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include "type_traits.hpp"
#include "utility.hpp"

namespace ft
{
    template <class T>
    class rb_node_
    {
    public:
        rb_node_ *parent;
        rb_node_ *left;
        rb_node_ *right;
        bool color;
        T value;

        static const bool BLACK = true;
        static const bool RED = false;

        rb_node_() : parent(NULL), left(NULL), right(NULL), color(BLACK) {}
        rb_node_(rb_node_ *nil, const T &value)
            : parent(nil), left(nil), right(nil), color(RED), value(value) {}
    };

    // Functions
    // nodeを頂点とした木から最小のノードを返す
    template <class T>
    rb_node_<T> *search_tree_min_(rb_node_<T> *node, rb_node_<T> *nil)
    {
        while (node->left != nil)
        {
            node = node->left;
        }
        return node;
    }

    // nodeを頂点とした木から最大のノードを返す
    template <class T>
    rb_node_<T> *search_tree_max_(rb_node_<T> *node, rb_node_<T> *nil)
    {
        while (node->right != nil)
        {
            node = node->right;
        }
        return node;
    }

    // nodeが親の左の子ならtrueを、そうでないならfalseを返す
    template <class T>
    bool is_left_child_(rb_node_<T> *node)
    {
        return node == node->parent->left;
    }

    // nodeが親の右の子ならtrueを、そうでないならfalseを返す
    template <class T>
    bool is_right_child_(rb_node_<T> *node)
    {
        return node == node->parent->right;
    }

    // nodeを始点に次に大きいノードを返す
    template <class T>
    rb_node_<T> *search_next_node_(rb_node_<T> *node, rb_node_<T> *nil)
    {
        if (node->right != nil)
        {
            return search_tree_min_(node->right, nil);
        }
        while (!is_left_child_(node))
        {
            node = node->parent;
        }
        return node->parent;
    }

    // nodeを始点にnodeの一つ小さいノードを返す
    template <class T>
    rb_node_<T> *search_prev_node_(rb_node_<T> *node, rb_node_<T> *nil)
    {
        if (node->left != nil)
        {
            return search_tree_max_(node->left, nil);
        }
        while (!is_right_child_(node))
        {
            node = node->parent;
        }
        return node->parent;
    }

    template <class T>
    class tree_iterator_ : public std::iterator<std::bidirectional_iterator_tag, T>
    {
    public:
        // Types
        typedef typename iterator_traits<T>::iterator_category iterator_category;
        typedef typename iterator_traits<T>::value_type value_type;
        typedef typename iterator_traits<T>::difference_type difference_type;
        typedef typename iterator_traits<T>::pointer pointer;
        typedef typename iterator_traits<T>::reference reference;

    private:
        typedef rb_node_<value_type> *link_type;

    public:
        // Member functions
        // constructor
        tree_iterator_() : current(NULL) {}
        explicit tree_iterator_(link_type ptr, link_type nil)
            : current(ptr), nil(nil) {}

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
            nil = other.get_nil();
            return *this;
        }

        // dereference operator
        reference operator*() const
        {
            return current->value;
        }
        pointer operator->() const
        {
            return &current->value;
        }

        // prefix/postfix increment
        tree_iterator_ &operator++()
        {
            current = search_next_node_(current, nil);
            return *this;
        }
        tree_iterator_ operator++(int)
        {
            tree_iterator_ tmp(*this);
            ++(*this);
            return tmp;
        }

        // prefix/postfix decrement
        tree_iterator_ &operator--()
        {
            current = search_prev_node_(current, nil);
            return *this;
        }
        tree_iterator_ operator--(int)
        {
            tree_iterator_ tmp(*this);
            --(*this);
            return tmp;
        }

        link_type base() const
        {
            return current;
        }

        link_type get_nil() const
        {
            return nil;
        }

    private:
        link_type current;
        link_type nil;
    };

    // Non-member functions
    template <class Iterator1, class Iterator2>
    bool operator==(const ft::tree_iterator_<Iterator1> &lhs,
                    const ft::tree_iterator_<Iterator2> &rhs)
    {
        return lhs.base() == rhs.base();
    }
    template <class Iterator1, class Iterator2>
    bool operator!=(const ft::tree_iterator_<Iterator1> &lhs,
                    const ft::tree_iterator_<Iterator2> &rhs)
    {
        return lhs.base() != rhs.base();
    }
    template <class Iterator1, class Iterator2>
    bool operator<(const ft::tree_iterator_<Iterator1> &lhs,
                   const ft::tree_iterator_<Iterator2> &rhs)
    {
        return lhs.base() < rhs.base();
    }
    template <class Iterator1, class Iterator2>
    bool operator<=(const ft::tree_iterator_<Iterator1> &lhs,
                    const ft::tree_iterator_<Iterator2> &rhs)
    {
        return lhs.base() <= rhs.base();
    }
    template <class Iterator1, class Iterator2>
    bool operator>(const ft::tree_iterator_<Iterator1> &lhs,
                   const ft::tree_iterator_<Iterator2> &rhs)
    {
        return lhs.base() > rhs.base();
    }
    template <class Iterator1, class Iterator2>
    bool operator>=(const ft::tree_iterator_<Iterator1> &lhs,
                    const ft::tree_iterator_<Iterator2> &rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <class Key, class T, class Compare, class Allocator = std::allocator<T> >
    class rb_tree_
    {
    public:
        // Types
        typedef tree_iterator_<T *> iterator;
        typedef tree_iterator_<const T *> const_iterator;

    private:
        typedef Key key_type;
        typedef T value_type;
        typedef rb_node_<T> *link_type;
        typedef const rb_node_<T> *const_link_type;
        typedef typename Allocator::size_type size_type;
        typedef typename Allocator::template rebind<rb_node_<T> >::other
            node_allocator_type;
        typedef typename node_allocator_type::difference_type difference_type;

    public:
        rb_tree_(const Compare &compare, const Allocator &allocator)
            : compare_(compare), alloc_(node_allocator_type(allocator)), size_(0)
        {
            initialize();
        }

        rb_tree_(const rb_tree_ &tree)
            : compare_(tree.compare_), alloc_(tree.alloc_), size_(0)
        {
            initialize();
        }

        ~rb_tree_()
        {
            destroy(get_root());
            delete_node(nil_);
            delete_node(end_);
        }

        rb_tree_ &operator=(const rb_tree_ &other)
        {
            if (this != &other)
            {
                clear();
                compare_ = other.compare_;
                for (iterator iter = other.begin(); iter != other.end(); ++iter)
                {
                    insert(*iter);
                }
            }
            return *this;
        }

        // Iterators
        iterator begin()
        {
            return iterator(begin_, nil_);
        }
        const_iterator begin() const
        {
            return const_iterator(begin_, nil_);
        }

        iterator end()
        {
            return iterator(end_, nil_);
        }
        const_iterator end() const
        {
            return const_iterator(end_, nil_);
        }

        // Capacity
        size_type size() const
        {
            return size_;
        }
        size_type max_size() const
        {
            return std::min(
                static_cast<size_type>(std::numeric_limits<difference_type>::max()),
                alloc_.max_size());
        }

        // Modifiers
        pair<iterator, bool> insert(const value_type &value)
        {
            link_type insert_place = search_insert_place(value);
            return insert_node(value, insert_place);
        }

        iterator insert(iterator position, const value_type &value)
        {
            if (position == end())
            {
                iterator max = end();
                if (size_ > 0 && compare_(*(--max), value))
                    return insert_node(value, max.base()).first;
                else
                    return insert(value).first;
            }
            if (compare_(value, *position)) // value < pos
            {
                if (position == begin())
                    return insert_node(value, begin_).first;
                iterator prev = position;
                --prev;
                if (compare_(*prev, value))
                {
                    if (prev.base()->right == nil_)
                        return insert_node(value, prev.base()).first;
                    else
                        return insert_node(value, position.base()).first;
                }
                return insert(value).first;
            }
            if (compare_(*position, value)) // pos < value
            {
                iterator max = end();
                --max;
                if (position == max)
                    return insert_node(value, max.base()).first;
                iterator next = position;
                ++next;
                if (compare_(value, *next))
                {
                    if (position.base()->right == nil_)
                        return insert_node(value, position.base()).first;
                    else
                        return insert_node(value, next.base()).first;
                }
                return insert(value).first;
            }
            return position;
        }

        void erase(iterator position)
        {
            if (position == end())
                return;

            if (position == begin())
                begin_ = search_next_node_(begin_, nil_);

            bool deleted_color;
            link_type replaced = replace_node(position.base(), deleted_color);
            if (deleted_color == rb_node_<T>::BLACK)
                delete_fixup(replaced);
            delete_node(position.base());
            size_--;
        }
        size_type erase(const key_type &key)
        {
            iterator iter = find(key);
            if (iter == end())
                return 0;
            erase(iter);
            return 1;
        }
        void erase(iterator first, iterator last)
        {
            while (first != last)
            {
                erase(first++);
            }
        }

        void clear()
        {
            destroy(get_root());
            begin_ = end_;
            end_->left = nil_;
            size_ = 0;
        }

        void swap(rb_tree_ &tree)
        {
            std::swap(nil_, tree.nil_);
            std::swap(begin_, tree.begin_);
            std::swap(end_, tree.end_);
            std::swap(compare_, tree.compare_);
            std::swap(alloc_, tree.alloc_);
            std::swap(size_, tree.size_);
        }

        // Operations
        iterator lower_bound(const key_type &key)
        {
            link_type node = search_lower_bound_node(key);
            return iterator(node, nil_);
        }

        const_iterator lower_bound(const key_type &key) const
        {
            link_type node = search_lower_bound_node(key);
            return const_iterator(node, nil_);
        }

        iterator upper_bound(const key_type &key)
        {
            link_type node = search_upper_bound_node(key);
            return iterator(node, nil_);
        }

        const_iterator upper_bound(const key_type &key) const
        {
            link_type node = search_upper_bound_node(key);
            return const_iterator(node, nil_);
        }

        pair<const_iterator, const_iterator> equal_range(const key_type &key) const
        {
            pair<link_type, link_type> range = search_equal_range_node(key);
            return ft::make_pair(const_iterator(range.first, nil_),
                             const_iterator(range.second, nil_));
        }
        pair<iterator, iterator> equal_range(const key_type &key)
        {
            pair<link_type, link_type> range = search_equal_range_node(key);
            return ft::make_pair(iterator(range.first, nil_),
                             iterator(range.second, nil_));
        }

        iterator find(const key_type &key)
        {
            link_type node = find_node(key);
            return iterator(node, nil_);
        }
        const_iterator find(const key_type &key) const
        {
            link_type node = find_node(key);
            return const_iterator(node, nil_);
        }

        size_type count(const key_type &k) const
        {
            if (find(k) != end())
                return 1;
            return 0;
        }

        node_allocator_type get_allocator() const
        {
            return alloc_;
        }

    private:
        link_type nil_;
        link_type begin_;
        link_type end_;

        Compare compare_;
        node_allocator_type alloc_;

        size_type size_;

        void initialize()
        {
            nil_ = alloc_.allocate(1);
            alloc_.construct(nil_);
            nil_->left = nil_;
            nil_->right = nil_;

            end_ = alloc_.allocate(1);
            alloc_.construct(end_);
            end_->left = nil_;
            begin_ = end_;
        }

        void destroy(link_type node)
        {
            if (node != nil_)
            {
                destroy(node->left);
                destroy(node->right);
                delete_node(node);
            }
        }

        link_type get_root() const
        {
            return end_->left;
        }

        void set_root(link_type node)
        {
            node->parent = end_;
            end_->left = node;
        }

        link_type create_node(const value_type &value)
        {
            link_type new_node = alloc_.allocate(1);
            alloc_.construct(new_node, nil_, value);
            return new_node;
        }

        void delete_node(link_type node)
        {
            alloc_.destroy(node);
            alloc_.deallocate(node, 1);
        }

        void rotate_left(link_type node)
        {
            link_type y = node->right;
            node->right = y->left;
            if (y->left != nil_)
                y->left->parent = node;
            y->parent = node->parent;
            if (node->parent == nil_)
                set_root(y);
            else if (is_left_child_(node))
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
                set_root(y);
            else if (is_right_child_(node))
                node->parent->right = y;
            else
                node->parent->left = y;
            y->right = node;
            node->parent = y;
        }

        link_type search_insert_place(const value_type &value)
        {
            link_type prev_node = nil_;
            link_type now_node = get_root();
            while (now_node != nil_)
            {
                prev_node = now_node;
                if (compare_(value, now_node->value))
                    now_node = now_node->left;
                else if (compare_(now_node->value, value))
                    now_node = now_node->right;
                else
                    return now_node;
            }
            return prev_node;
        }

        pair<iterator, bool> insert_node(const value_type &value, link_type insert_place)
        {
            link_type node = create_node(value);
            node->parent = insert_place;
            if (insert_place == nil_)
                set_root(node);
            else if (compare_(node->value, insert_place->value))
                insert_place->left = node;
            else if (compare_(insert_place->value, node->value))
                insert_place->right = node;
            else // node->value == insert_place->value
            {
                delete_node(node);
                return ft::make_pair(iterator(insert_place, nil_), false);
            }
            insert_fixup(node);
            update_begin_node(node);
            size_++;
            return ft::make_pair(iterator(node, nil_), true);
        }

        void insert_fixup(link_type node)
        {
            while (node->parent->color == rb_node_<T>::RED)
            {
                if (is_left_child_(node->parent))
                {
                    insert_fixup_left(node);
                }
                else
                {
                    insert_fixup_right(node);
                }
            }
            get_root()->color = rb_node_<T>::BLACK;
        }

        void insert_fixup_left(link_type &node)
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
                if (is_right_child_(node))
                {
                    node = node->parent;
                    rotate_left(node);
                }
                node->parent->color = rb_node_<T>::BLACK;
                node->parent->parent->color = rb_node_<T>::RED;
                rotate_right(node->parent->parent);
            }
        }

        void insert_fixup_right(link_type &node)
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
                if (is_left_child_(node))
                {
                    node = node->parent;
                    rotate_right(node);
                }
                node->parent->color = rb_node_<T>::BLACK;
                node->parent->parent->color = rb_node_<T>::RED;
                rotate_left(node->parent->parent);
            }
        }

        void delete_fixup(link_type node)
        {
            while (node != get_root() && node->color == rb_node_<T>::BLACK)
            {
                if (is_right_child_(node))
                {
                    delete_fixup_right(node);
                }
                else
                {
                    delete_fixup_left(node);
                }
            }
            node->color = rb_node_<T>::BLACK;
        }

        void delete_fixup_right(link_type &node)
        {
            link_type sibling = node->parent->right;
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
                node = get_root();
            }
        }

        void delete_fixup_left(link_type &node)
        {
            link_type sibling = node->parent->left;
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
                node = get_root();
            }
        }

        link_type find_node(const value_type &value) const
        {
            link_type node = get_root();
            while (node != nil_)
            {
                if (compare_(value, node->value))
                    node = node->left;
                else if (compare_(node->value, value))
                    node = node->right;
                else
                    return node;
            }
            return nil_;
        }

        void transplant(link_type x, link_type y)
        {
            if (x->parent == nil_)
                set_root(y);
            else if (is_left_child_(x))
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
                link_type y = search_tree_min_(node->right, nil_);
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

        void update_begin_node(link_type insert_node)
        {
            if (begin_ == end_ || compare_(insert_node->value, begin_->value))
            {
                begin_ = insert_node;
            }
        }

        link_type search_lower_bound_node(const key_type &key) const
        {
            link_type result = end_;
            link_type node = get_root();
            while (node != nil_)
            {
                if (!compare_(node->value, key)) // node >= key
                {
                    result = node;
                    node = node->left;
                }
                else
                    node = node->right;
            }
            return result;
        }

        link_type search_upper_bound_node(const key_type &key) const
        {
            link_type result = end_;
            link_type node = get_root();
            while (node != nil_)
            {
                if (compare_(key, node->value)) // key < node
                {
                    result = node;
                    node = node->left;
                }
                else
                    node = node->right;
            }
            return result;
        }

        pair<link_type, link_type> search_equal_range_node(const key_type &key) const
        {
            link_type lower = get_root();
            link_type upper = end_;
            while (lower != nil_)
            {
                if (compare_(key, lower->value))
                {
                    upper = lower;
                    lower = lower->left;
                }
                else if (compare_(lower->value, key))
                {
                    lower = lower->right;
                }
                else
                {
                    if (lower->right != nil_)
                        upper = search_tree_min_(lower->right, nil_);
                    return ft::make_pair(lower, upper);
                }
            }
            return ft::make_pair(upper, upper);
        }

        link_type find_node(const key_type &key) const
        {
            link_type node = search_lower_bound_node(key);
            if (node != end_ && !compare_(key, node->value))
                return node;
            return end_;
        }
    };

} /* namespace ft */

#endif /* TREE_HPP */
