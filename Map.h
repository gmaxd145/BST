#ifndef BST_MAP_H
#define BST_MAP_H

/*!
    Имплементация словаря
    Не допускается дублирование ключей (аналог std::map)
*/
template <typename Key, typename Value>
class Map
{
    BinarySearchTree<Key, Value> _tree;
public:
    using MapIterator = BinarySearchTree::Iterator;
    using ConstMapIterator = BinarySearchTree::ConstIterator;

    Map() = default;

    explicit Map(const Map& other);
    Map& operator=(const Map& other);

    explicit Map(Map&& other) noexcept;
    Map& operator=(Map&& other) noexcept;

    ~Map() = default;

    // вставить элемент с ключем key и значением value
    // если узел с ключем key уже представлен, то заменить его значение на value
    void insert(const Key& key, const Value& value);

    // удалить элемент с ключем key
    void erase(const Key& key);

    // найти элемент, равный ключу key
    ConstMapIterator find(const Key& key) const;
    MapIterator find(const Key& key);

    // доступ к элементу по ключу
    // если в момент обращения элемента не существует, создать его,
    // ключ равен key, value равно дефолтному значению для типа Value
    const Value& operator[](const Key& key) const;
    Value& operator[](const Key& key);

    MapIterator begin();
    MapIterator end();

    ConstMapIterator cbegin() const;
    ConstMapIterator cend() const;

    size_t size() const;
};

#endif //BST_MAP_H
