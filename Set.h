#ifndef BST_SET_H
#define BST_SET_H

/*!
    Имплементация множества
    Не допускается дублирование ключей (аналог std::set)
*/
template <typename Value>
class Set
{
    Map<Value, Value> _map;

public:
    using SetIterator = Map::MapIterator;
    using ConstSetIterator = Map::ConstMapIterator;

    Set() = default;

    explicit Set(const Set& other);
    Set& operator=(const Set& other);

    explicit Set(Set&& other) noexcept;
    Set& operator=(Set&& other) noexcept;

    ~Set() = default;

    void insert(const Value& value);

    void erase(const Value& value);

    ConstSetIterator find(const Value& value) const;
    SetIterator find(const Value& key);

    bool contains(const Value& value) const;
};

#endif //BST_SET_H
