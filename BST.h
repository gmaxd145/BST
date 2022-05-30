#ifndef BST_BST_H
#define BST_BST_H

#include <utility>

/*!
    Имплементация бинарного дерева поиска
    Допускается дублирование ключей (аналог multimap)
*/
template <typename Key, typename Value>
class BinarySearchTree
{
    struct Node
    {
        Node() = default;

        Node(Key key,
             Value value,
             Node* parent = nullptr,
             Node* left = nullptr,
             Node* right = nullptr);

        std::pair<Key, Value> keyValuePair;
        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;
    };

public:
    //! Конструктор по умолчанию
    BinarySearchTree() = default;

    //! Копирование
    explicit BinarySearchTree(const BinarySearchTree& other);
    BinarySearchTree& operator=(const BinarySearchTree& other);
    //! Перемещение
    explicit BinarySearchTree(BinarySearchTree&& other) noexcept;
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;

    //! Деструктор
//    ~BinarySearchTree();

    /*!
        Итератор бинарного дерева поиска

        Обходит дерево последовательно от меньшего ключа к большему
    */
    class Iterator
    {
    public:
        explicit Iterator(Node* node);

        std::pair<Key, Value>& operator*();
        const std::pair<Key, Value>& operator*() const;

        std::pair<Key, Value>* operator->();
        const std::pair<Key, Value>* operator->() const;

        Iterator operator++();
        Iterator operator++(int);

        Iterator operator--();
        Iterator operator--(int);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        Node* _node;
    };

    /*!
        Константный итератор
    */
    class ConstIterator
    {
    public:
        explicit ConstIterator(const Node* node);

        const std::pair<Key, Value>& operator*() const;

        const std::pair<Key, Value>* operator->() const;

        ConstIterator operator++();
        ConstIterator operator++(int);

        ConstIterator operator--();
        ConstIterator operator--(int);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        const Node* _node;
    };

    // вставить элемент с ключем key и значением value
    void insert(const Key& key, const Value& value);

    // удалить все элементы с ключем key
    void erase(const Key& key);

    // найти первый элемент в дереве, равный ключу key
    ConstIterator find(const Key& key) const;
    Iterator find(const Key& key);

    // найти все элементы, у которых ключ равен key
    // первый итератор пары - первый элемент в дереве, равный key
    // второй итератор пары - первый элемент в дереве больший, чем key
    // [pair.first, pair.second) - полуинтервал, содержащий все элементы с ключем key
    std::pair<Iterator, Iterator> equalRange(const Key& key);
    std::pair<ConstIterator, ConstIterator> equalRange(const Key& key) const;

    // получить итератор на минимальное значение в дереве
    ConstIterator min(const Key& key) const;
    // получить итератор на максимальное значение в дереве
    ConstIterator max(const Key& key) const;

    Iterator begin();
    Iterator end();

    ConstIterator cbegin() const;
    ConstIterator cend() const;

    std::size_t size() const;
//private:
    Node* insert(Key key, Value value, Node *node);

    Node* find(Key key, Node* node) const;

    static Node* min(Node *node);
    static Node* max(Node *node);

    std::size_t _size = 0;
    Node* _root = nullptr; //!< корневой узел дерева
};

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::ConstIterator::ConstIterator(const BinarySearchTree::Node *node)
: _node(node)
{
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::Iterator::Iterator(BinarySearchTree::Node *node)
: _node(node)
{
}

template<typename Key, typename Value>
std::pair<Key, Value>* BinarySearchTree<Key, Value>::Iterator::operator->()
{
    return &_node->keyValuePair;
}

template<typename Key, typename Value>
const std::pair<Key, Value> *BinarySearchTree<Key, Value>::Iterator::operator->() const
{
    return &_node->keyValuePair;
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::Iterator::operator==(const BinarySearchTree::Iterator &other) const
{
    return _node == other._node;
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::Iterator::operator!=(const BinarySearchTree::Iterator &other) const
{
    return _node != other._node;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator++()
{
    if (_node == nullptr)
    {
        return *this;
    }
    if (_node->right)
    {
        _node = BinarySearchTree::min(_node->right);
    }
    else
    {
        auto parent = _node->parent;
        while (parent && _node == parent->right)
        {
            _node = parent;
            parent = parent->parent;
        }
        _node = parent;
    }
    return *this;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator++(int)
{
    Node* bufPtr = _node;
    ++(*this);
    return Iterator(bufPtr);
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator--()
{
    if (_node == nullptr)
    {
        return *this;
    }
    if (_node->parent && _node->parent->keyValuePair.first <= _node->keyValuePair.first)
    {
        _node = _node->parent;
    }
    else
    {
        _node = BinarySearchTree::max(_node->left);
    }
    return *this;
}


template<typename Key, typename Value>
BinarySearchTree<Key, Value>::Node::Node(Key key, Value value, BinarySearchTree::Node *parent,
                                         BinarySearchTree::Node *left, BinarySearchTree::Node *right)
{
    keyValuePair.first = key;
    keyValuePair.second = value;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const Key &key, const Value &value)
{
    _root = insert(key, value, _root);
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node*
BinarySearchTree<Key, Value>::insert(Key key, Value value, BinarySearchTree::Node *node)
{
    auto& nodeKey = node->keyValuePair.first;
    auto& nodeValue = node->keyValuePair.second;

    if (!node)
    {
        node = new Node();
        *node = {key, value, nullptr, nullptr};
        if (_size == 0)
        {
            node->parent = nullptr;
        }
        ++_size;
    }
    else if (key <= nodeKey)
    {
        node->left = insert(key, value, node->left);
        node->left->parent = node;
    }
    else if (key >= nodeKey)
    {
        node->right = insert(key, value, node->right);
        node->right->parent = node;

    }
    else if (key == nodeKey)
    {
        nodeValue = value;
    }
    return node;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator
BinarySearchTree<Key, Value>::find(const Key &key)
{
    return Iterator(find(key, _root));
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node* BinarySearchTree<Key, Value>::find(Key key, BinarySearchTree::Node *node) const
{
    auto& nodeKey = node->keyValuePair.first;
    auto& nodeValue = node->keyValuePair.second;

    if (!node)
    {
        return nullptr;
    }
    else if (key == nodeKey)
    {
        return node;
    }
    else if (key < nodeKey)
    {
        return find(key, node->left);
    }
    else
    {
        return find(key, node->right);
    }
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node* BinarySearchTree<Key, Value>::min(BinarySearchTree::Node *node)
{
    if (!node)
    {
        return nullptr;
    }
    else if (!node->left)
    {
        return node;
    }
    else
    {
        return min(node->left);
    }
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node* BinarySearchTree<Key, Value>::max(BinarySearchTree::Node *node)
{
    if (!node)
    {
        return nullptr;
    }
    else if (!node->right)
    {
        return node;
    }
    else
    {
        return max(node->right);
    }
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::begin()
{
    return BinarySearchTree::Iterator(min(_root));
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::end()
{
    return BinarySearchTree::Iterator(max(_root)->right);
}


#endif //BST_BST_H
