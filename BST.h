#ifndef BST_BST_H
#define BST_BST_H

#include <utility>
#include <cstddef>

//! Дерево бинарного поиска
template <typename KeyType, typename ValueType>
class BST
{
public:
    //! Конструктор по умолчанию
    BST() = default;
    //! Копирование
    BST(const BST& other);
    BST& operator=(const BST& other);
    //! Перемещение
    BST(BST&& other) noexcept;
    BST& operator=(BST&& other) noexcept;

    //! Деструктор
    ~BST();

    //! Узел дерева бинароного поиска
    struct Node
    {
        KeyType key;        //!< ключ
        ValueType value;    //!< значение
        Node* left;         //!< указатель на элемент левого поддерева
        Node* right;        //!< указатель на элемент правого поддерева
        Node* parent;	    //!< указатель на родителя
    };
    //! Итератор бинарного дерева поиска
    class Iterator
    {
    public:
        explicit Iterator(Node* ptr);
        //! Разыменование
        std::pair<KeyType, ValueType>& operator*();
        const std::pair<KeyType, ValueType>& operator*() const;
        //!
        Node* operator->();
        const Node* operator->() const;
        //! Оперотор ++
        Iterator operator++();
        Iterator operator++(int);
        //! Оператор сравнения
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        Node* _ptr;
        std::pair<KeyType, ValueType> _pr; // ????
    };
    //! \brief Вставить элемент
    //! \details
    //! Алгоритм:
    //! Если дерево пусто, заменить его на дерево с одним корневым узлом ((K, V), null, null) и остановиться
    //! Иначе сравнить K со значением ключа корневого узла R:
    //! Если K > R, рекурсивно добавить (K, V) в правое поддерево ;
    //! Если K < R, рекурсивно добавить (K, V) в левое поддерево;
    //! Если K = R, заменить V текущего узла новым значением;
    //! \param key - ключ элемента
    //! \param value - значение
    void insert(KeyType key, ValueType value);
    //! \brief Удалить элемент
    //! \details
    //! Алгоритм:
    //! Если дерево T пусто, остановиться
    //! Иначе сравнить K с ключом X корневого узла R
    //! Если K > X, рекурсивно удалить K из правого поддерева;
    //! Если K < X, рекурсивно удалить K из левого поддерева;
    //! Если K = X, то необходимо рассмотреть три случая:
    //! 1. Если обоих детей нет, то удаляем текущий узел и обнуляем ссылку на него у родительского узла
    //! 2. Если одного из детей нет, то значения полей ребёнка m ставим вместо соответствующих значений корневого узла, затирая его старые значения, и освобождаем память, занимаемую узлом m
    //! 3. Если оба ребёнка присутствуют, то
    //! Если левый узел m правого поддерева отсутствует (n->right->left)
    //!     Копируем из правого узла в удаляемый поля K, V и ссылку на правый узел правого потомка;
    //! Иначе
    //!     Возьмём самый левый узел m, правого поддерева n->right;
    //!     Скопируем данные (кроме ссылок на дочерние элементы) из m в n;
    //!     Рекурсивно удалим узел m;
    //! \param key - ключ элемента
    void remove(KeyType key);
    //! \brief Найти элемент в дереве
    //! \details
    //! Алгоритм:
    //! Если дерево пусто, сообщить, что узел не найден, и остановиться;
    //! Иначе сравнить K со значением ключа корневого узла R:
    //! Если K = R, выдать ссылку на этот узел и остановиться;
    //! Если K > R, рекурсивно искать ключ K в правом поддереве Т;
    //! Если K < R, рекурсивно искать ключ K в левом поддереве Т;
    //! \param key - ключ элемента
    //! \return указатель на искомый узел, nullptr - если такого узла нет
    Node* find(KeyType key) const;
    //! \brief Найти узел с минимальным значением ключа в поддереве
    //! \param key - ключ корневого узла поддерева
    //! \return указатель на искомый узел
    Node* min(KeyType key) const;
    //! \brief Найти узел с максимальным значением ключа в дереве
    //! \param key - ключ корневого узла поддерева
    //! \return указатель на искомый узел, nullptr - если такого узла нет
    Node* max(KeyType key) const;
    //! \brief Получить корень дерева
    //! \return Итератор на корень дерева
    Iterator root();
    //! \brief Получить крайний левый лист дерева
    //! \return Итератор
    Iterator begin();
    //! \brief Получить крайний правый лист дерева
    //! \return Итератор
    Iterator end();
    //! \brief Получить размер дерева
        //! \return размер дерева
    size_t size() const;

private:
    Node* insert(KeyType key, ValueType value, Node* node);

    Node* find(KeyType key, Node* node) const;

    void remove(KeyType key, Node* node);

    static Node* min(Node* node);
    static Node* max(Node* node);

    Node* copy(Node* node);

    void clear(Node* node);

    void toValid(BST::Node *node);

    size_t _size = 0;
    Node* _root = nullptr; //!< корневой узел дерева
};

template<typename KeyType, typename ValueType>
void BST<KeyType, ValueType>::insert(KeyType key, ValueType value) {
    _root = insert(key, value, _root);
}

template<typename KeyType, typename ValueType>
typename BST<KeyType, ValueType>::Node* BST<KeyType, ValueType>::insert(KeyType key, ValueType value, BST::Node *node)
{
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
    else if (key < node->key)
    {
        node->left = insert(key, value, node->left);
        node->left->parent = node;
    }
    else if (key > node->key)
    {
        node->right = insert(key, value, node->right);
        node->right->parent = node;

    }
    else if (key == node->key)
    {
        node->value = value;
    }
    return node;
}

template<typename KeyType, typename ValueType>
typename BST<KeyType, ValueType>::Node* BST<KeyType, ValueType>::find(KeyType key) const
{
    return find(key, _root);
}

template<typename KeyType, typename ValueType>
typename BST<KeyType, ValueType>::Node* BST<KeyType, ValueType>::find(KeyType key, BST::Node *node) const
{
    if (!node)
    {
        return nullptr;
    }
    else if (key == node->key)
    {
        return node;
    }
    else if (key < node->key)
    {
        return find(key, node->left);
    }
//    else if (key > node->key)
    else
    {
        return find(key, node->right);
    }
}

template<typename KeyType, typename ValueType>
void BST<KeyType, ValueType>::remove(KeyType key)
{
    remove(key, _root);
}

template<typename KeyType, typename ValueType>
void BST<KeyType, ValueType>::remove(KeyType key, BST::Node *node) {
    if (!node)
    {
        return;
    }
    else if (key < node->key)
    {
        remove(key, node->left);
    }
    else if (key > node->key)
    {
        remove(key, node->right);
    }
    else if (key == node->key)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            if (node->parent->key > node->key)
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
        else if (node->left && !node->right)
        {
            *node = {node->left->key, node->left->value, node->left->left, node->left->right};
            delete node->left;
            --_size;
        }
        else if (!node->left && node->right)
        {
            *node = {node->right->key, node->right->value, node->right->left, node->right->right};
            delete node->right;
            --_size;
        }
        else
        {
            Node* minNode = min(node->right);
            *node = {minNode->key, minNode->value, minNode->left, minNode->right};
            delete minNode;
            --_size;
        }
    }
}

template<typename KeyType, typename ValueType>
typename BST<KeyType, ValueType>::Node* BST<KeyType, ValueType>::min(BST::Node *node)
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

template<typename KeyType, typename ValueType>
typename BST<KeyType, ValueType>::Node* BST<KeyType, ValueType>::min(KeyType key) const
{
    return min(find(key));
}

template<typename KeyType, typename ValueType>
typename BST<KeyType, ValueType>::Node* BST<KeyType, ValueType>::max(BST::Node *node)
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

template<typename KeyType, typename ValueType>
typename BST<KeyType, ValueType>::Node* BST<KeyType, ValueType>::max(KeyType key) const
{
    return max(find(key));
}

template<typename KeyType, typename ValueType>
size_t BST<KeyType, ValueType>::size() const {
    return _size;
}

template<typename KeyType, typename ValueType>
BST<KeyType, ValueType>::~BST() {
    clear(_root);
    _root = nullptr;
    _size = 0;
}

template<typename KeyType, typename ValueType>
void BST<KeyType, ValueType>::clear(BST::Node *node)
{
    if (node)
    {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template<typename KeyType, typename ValueType>
BST<KeyType, ValueType>&  BST<KeyType, ValueType>::operator=(const BST& other)
{
    if (this == &other)
    {
        return *this;
    }
    _root = copy(other._root);
    _size = other._size;
}

template<typename KeyType, typename ValueType>
typename BST<KeyType, ValueType>::Node* BST<KeyType, ValueType>::copy(BST::Node *node)
{
    if (node)
    {
        Node* nNode = new Node();
        *nNode = {node->key, node->value};

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

template<typename KeyType, typename ValueType>
BST<KeyType, ValueType>::BST(const BST& other)
{
    *this = other;
}

template<typename KeyType, typename ValueType>
BST<KeyType, ValueType>& BST<KeyType, ValueType>::operator=(BST&& other) noexcept
{
    std::swap(_root, other._root);
    toValid(other._root);
}

template<typename KeyType, typename ValueType>
BST<KeyType, ValueType>::BST(BST&& other) noexcept {
    *this = std::move(other);
}

template<typename KeyType, typename ValueType>
BST<KeyType, ValueType>::Iterator::Iterator(BST::Node *ptr) : _ptr(ptr) { }

template<typename KeyType, typename ValueType>
typename BST<KeyType, ValueType>::Node* BST<KeyType, ValueType>::Iterator::operator->()
{
    return _ptr;
}

template<typename KeyType, typename ValueType>
const typename BST<KeyType, ValueType>::Node* BST<KeyType, ValueType>::Iterator::operator->() const
{
    return _ptr;
}

template<typename KeyType, typename ValueType>
std::pair<KeyType, ValueType>& BST<KeyType, ValueType>::Iterator::operator*()
{
    _pr = std::make_pair(_ptr->key, _ptr->value);
    return _pr;
}

template<typename KeyType, typename ValueType>
const std::pair<KeyType, ValueType> &BST<KeyType, ValueType>::Iterator::operator*() const {
    _pr = std::make_pair(_ptr->key, _ptr->value);
    return _pr;
}

template<typename KeyType, typename ValueType>
bool BST<KeyType, ValueType>::Iterator::operator==(const BST::Iterator &other) const {
    return _ptr == other._ptr;
}

template<typename KeyType, typename ValueType>
bool BST<KeyType, ValueType>::Iterator::operator!=(const BST::Iterator &other) const {
    return _ptr != other._ptr;
}

template<typename KeyType, typename ValueType>
typename BST<KeyType, ValueType>::Iterator BST<KeyType, ValueType>::Iterator::operator++()
{
    if (_ptr == nullptr)
    {
        return * this;
    }
    if (_ptr->right)
    {
        _ptr = BST::min(_ptr->right);
    }
    else
    {
        auto parent = _ptr->parent;
        while (parent && _ptr == parent->right)
        {
            _ptr = parent;
            parent = parent->parent;
        }
        _ptr = parent;
    }
    return *this;
}

template<typename KeyType, typename ValueType>
typename BST<KeyType, ValueType>::Iterator BST<KeyType, ValueType>::Iterator::operator++(int)
{
    Node* bufPtr = _ptr;
    ++(*this);
    return Iterator(bufPtr);
}

template<typename KeyType, typename ValueType>
typename BST<KeyType, ValueType>::Iterator BST<KeyType, ValueType>::root()
{
    return BST::Iterator(_root);
}

template<typename KeyType, typename ValueType>
typename BST<KeyType, ValueType>::Iterator BST<KeyType, ValueType>::begin()
{
    return BST::Iterator(min(_root));
}

template<typename KeyType, typename ValueType>
typename BST<KeyType, ValueType>::Iterator BST<KeyType, ValueType>::end()
{
    return BST::Iterator(max(_root)->right);
}

template<typename KeyType, typename ValueType>
void BST<KeyType, ValueType>::toValid(BST::Node *node) {
    if (node)
    {
        toValid(node->left);
        toValid(node->right);
        node->key = 0;
        node->value = 0;
    }
}

#endif //BST_BST_H
