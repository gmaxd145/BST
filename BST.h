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
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
    };

public:
    //! Конструктор по умолчанию
    BinarySearchTree() = default;

    //! Копирование
    BinarySearchTree(const BinarySearchTree& other); // with explicit it does not work
    BinarySearchTree& operator=(const BinarySearchTree& other);
    //! Перемещение
    BinarySearchTree(BinarySearchTree&& other) noexcept; // explicit move c-or?
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;

    //! Деструктор
    ~BinarySearchTree();

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

        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;

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
private:
    Node* insert(const Key& key, const Value& value, Node *node);

    Node* find(const Key& key, Node* node) const;

    Node* copy(Node* node);

    static Node* min(Node *node);
    static Node* max(Node *node);

    void erase (const Key& key, Node* node);
    void clear(Node* node);

    std::size_t _size = 0;
    Node* _root = nullptr; //!< корневой узел дерева
};

/*              C-ors and d-or                */
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree(const BinarySearchTree &other)
{
    *this = other;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value> &BinarySearchTree<Key, Value>::operator=(const BinarySearchTree &other)
{
    if (this == &other)
    {
        return *this;
    }
    _root = copy(other._root);
    _size = other._size;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree(BinarySearchTree &&other) noexcept
{
    *this = std::move(other);
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value> &BinarySearchTree<Key, Value>::operator=(BinarySearchTree &&other) noexcept
{
    std::swap(_root, other._root);
    std::swap(_size, other._size);
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    clear(_root);
    _root = nullptr;
    _size = 0;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node *BinarySearchTree<Key, Value>::copy(BinarySearchTree::Node *node)
{
    if (node)
    {
        auto& nodeKey = node->keyValuePair.first;
        auto& nodeValue = node->keyValuePair.second;

        Node* nNode = new Node(nodeKey, nodeValue);

        nNode->left = copy(node->left);
        if (node->left)
        {
            nNode->left->parent = node;
        }

        nNode->right = copy(node->right);
        if (node->right)
        {
            nNode->right->parent = node;
        }

        return nNode;
    }
    return nullptr;
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear(BinarySearchTree::Node *node)
{
    if (node)
    {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

/*              Iterator                */
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
std::pair<Key, Value>& BinarySearchTree<Key, Value>::Iterator::operator*()
{
    return _node->keyValuePair;
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
        _node = _node->right;
        while (_node->left)
        {
            _node = _node->left;
        }
    }
    else
    {
        while (_node->parent && _node == _node->parent->right)
        {
            _node = _node->parent;
        }
        _node = _node->parent;
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
    if (_node->left)
    {
        _node = _node->left;
        while (_node->right)
        {
            _node = _node->right;
        }
    }
    else
    {
        while (_node->parent && _node->parent->left == _node)
        {
            _node = _node->parent;
        }
        _node = _node->parent;
    }
    return *this;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator--(int)
{
    Node* bufPtr = _node;
    --(*this);
    return Iterator(bufPtr);
}

template<typename Key, typename Value>
const std::pair<Key, Value>& BinarySearchTree<Key, Value>::Iterator::operator*() const
{
    return _node->keyValuePair;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator
BinarySearchTree<Key, Value>::find(const Key &key)
{
    return Iterator(find(key, _root));
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::begin()
{
    return BinarySearchTree::Iterator(min(_root));
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::end()
{
    return BinarySearchTree::Iterator(nullptr);
}


/*              ConstIterator               */
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::ConstIterator::ConstIterator(const BinarySearchTree::Node *node)
        : _node(node)
{
}

template<typename Key, typename Value>
const std::pair<Key, Value> *BinarySearchTree<Key, Value>::ConstIterator::operator->() const
{
    return &_node->keyValuePair;
}

template<typename Key, typename Value>
const std::pair<Key, Value>& BinarySearchTree<Key, Value>::ConstIterator::operator*() const
{
    return _node->keyValuePair;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::ConstIterator::operator++()
{
    if (_node == nullptr)
    {
        return *this;
    }
    if (_node->right)
    {
        _node = _node->right;
        while (_node->left)
        {
            _node = _node->left;
        }
    }
    else
    {
        while (_node->parent && _node == _node->parent->right)
        {
            _node = _node->parent;
        }
        _node = _node->parent;
    }
    return *this;
}


template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::ConstIterator::operator++(int)
{
    Node* bufPtr = _node;
    ++(*this);
    return ConstIterator(bufPtr);
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::ConstIterator::operator--()
{
    if (_node == nullptr)
    {
        return *this;
    }
    if (_node->left)
    {
        _node = _node->left;
        while (_node->right)
        {
            _node = _node->right;
        }
    }
    else
    {
        while (_node->parent && _node->parent->left == _node)
        {
            _node = _node->parent;
        }
        _node = _node->parent;
    }
    return *this;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::ConstIterator::operator--(int)
{
    Node* bufPtr = _node;
    --(*this);
    return ConstIterator(bufPtr);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::ConstIterator::operator==(const BinarySearchTree::ConstIterator &other) const
{
    return _node == other._node;
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::ConstIterator::operator!=(const BinarySearchTree::ConstIterator &other) const
{
    return _node != other._node;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::cbegin() const
{
    return BinarySearchTree::ConstIterator(min(_root));

}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::cend() const
{
    return BinarySearchTree::ConstIterator(nullptr);
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator
BinarySearchTree<Key, Value>::find(const Key &key) const
{
    return ConstIterator(find(key, _root));
}


template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node* BinarySearchTree<Key, Value>::find(const Key& key, BinarySearchTree::Node *node) const
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


/*              insert               */
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const Key &key, const Value &value)
{
    _root = insert(key, value, _root);
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node*
BinarySearchTree<Key, Value>::insert(const Key& key, const Value& value, BinarySearchTree::Node *node) {
    auto &nodeKey = node->keyValuePair.first;
    auto &nodeValue = node->keyValuePair.second;

    if (!node) {
        node = new Node();
        *node = {key, value, nullptr, nullptr};
        if (_size == 0) {
            node->parent = nullptr;
        }
        ++_size;
    } else if (key < nodeKey) {
        node->left = insert(key, value, node->left);
        node->left->parent = node;
    } else if (key >= nodeKey) {
        node->right = insert(key, value, node->right);
        node->right->parent = node;

    } else if (key == nodeKey) {
        nodeValue = value;
    }
    return node;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::Node::Node(Key key, Value value, BinarySearchTree::Node *parent,
                                         BinarySearchTree::Node *left, BinarySearchTree::Node *right)
{
    keyValuePair.first = key;
    keyValuePair.second = value;
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
std::size_t BinarySearchTree<Key, Value>::size() const
{
    return _size;
}


/*              erase               */
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::erase(const Key &key)
{
    while (find(key) != Iterator(nullptr))
    {
        erase(key, _root);
    }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::erase(const Key& key, Node* node)
{
    auto& nodeKey = node->keyValuePair.first;

    if (_size == 1)
    {
        delete _root;
        --_size;
        _root = nullptr;
    }

    if (!node)
    {
        return;
    }
    else if (key < nodeKey)
    {
        erase(key, node->left);
    }
    else if (key > nodeKey)
    {
        erase(key, node->right);
    }
    else
    {
        if (!node->left && !node->right)
        {
            if (node->parent->keyValuePair.first > node->keyValuePair.first)
            {
                node->parent->left = nullptr;
            }
            else
            {
                node->parent->right = nullptr;
            }
            delete node;
            --_size;
        }
        else if (!node->right)
        {
            node->parent->left = node->left;
            node->left->parent = node->parent;
            delete node;
            --_size;
        }
        else if (!node->left && node->right)
        {
            node->parent->right = node->right;
            node->right->parent = node->parent;
            delete node;
            --_size;
        }
        else
        {
            Node* maxNode = max(node->left);

            if (maxNode->parent->keyValuePair.first <= maxNode->keyValuePair.first)
            {
                maxNode->parent->right = maxNode->left;
            }
            else
            {
                maxNode->parent->left = maxNode->left;
            }
            maxNode->left->parent = maxNode->parent;

            node->keyValuePair = maxNode->keyValuePair;

            delete maxNode;
            --_size;
        }
    }
}


/*              equalRange               */
template<typename Key, typename Value>
std::pair<typename BinarySearchTree<Key, Value>::Iterator, typename BinarySearchTree<Key, Value>::Iterator>
BinarySearchTree<Key, Value>::equalRange(const Key &key)
{
    Iterator start = find(key);
    Iterator stop(start);
    if (stop->second == max(_root)->keyValuePair.second)
    {
        return std::make_pair(start, Iterator(nullptr));
    }
    while (stop->first == key)
    {
        if (stop->second == max(_root)->keyValuePair.second)
        {
            stop = Iterator(nullptr);
            break;
        }
        ++stop;
    }
    return std::make_pair(start, stop);
}

template<typename Key, typename Value>
std::pair<typename BinarySearchTree<Key, Value>::ConstIterator, typename BinarySearchTree<Key, Value>::ConstIterator>
BinarySearchTree<Key, Value>::equalRange(const Key &key) const
{
    ConstIterator start = find(key);
    ConstIterator stop(start);
    if (stop->second == max(_root)->keyValuePair.second)
    {
        return std::make_pair(start, ConstIterator(nullptr));
    }
    while (stop->first == key)
    {
        if (stop->second == max(_root)->keyValuePair.second)
        {
            stop = ConstIterator(nullptr);
            break;
        }
        ++stop;
    }
    return std::make_pair(start, stop);
}


/*              min, max               */
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator
BinarySearchTree<Key, Value>::min(const Key &key) const
{
    std::pair<ConstIterator, ConstIterator> keyValues = equalRange(key);
    ConstIterator minPairIt = ConstIterator(keyValues.first);
    for (ConstIterator it = keyValues.first; it != keyValues.second; ++it)
    {
        if (it->second < minPairIt->second) {
            minPairIt = it;
        }
    }
    return minPairIt;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator
BinarySearchTree<Key, Value>::max(const Key &key) const
{
    std::pair<ConstIterator, ConstIterator> keyValues = equalRange(key);
    ConstIterator maxPairIt = ConstIterator(keyValues.first);
    for (ConstIterator it = keyValues.first; it != keyValues.second; ++it)
    {
        if (it->second > maxPairIt->second)
        {
            maxPairIt = it;
        }
    }
    return maxPairIt;
}



#endif //BST_BST_H
