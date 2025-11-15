#ifndef CUSTOM_HASH_TABLE_HPP
#define CUSTOM_HASH_TABLE_HPP

#include <vector>
#include <list>
#include <utility>  // for std::pair
#include <string>
#include <iostream>
#include <functional>  // for std::hash
#include <optional>
#include <stdexcept>



template<typename K, typename V>


class CustomHashTable 
{


private:

    bool _verbose {false};

    // Starting capacity of hash table
    static const int _DEFAULT_CAPACITY {16};

    // Maximum table size before rehashing
    static constexpr double MAX_LOAD_FACTOR {0.75};

    // Vector of lists that makes up the hash table
    std::vector<std::list<std::pair<K, V>>> _table;
    std::size_t _num_elements;
    std::hash<K> _hasher;


public:

    // Constructor
    CustomHashTable() : _table(_DEFAULT_CAPACITY), _num_elements(0) {}

    void set_verbose(const bool verbose) { _verbose = verbose; }

    // Insert or update key-value pair
    void insert(const K& key, const V& value) 
    {
        if(_verbose) std::cout << "Inserting " << key << ":  " << value << std::endl;

        // Rehash if needed
        if ((double)(_num_elements + 1) / _table.size() > MAX_LOAD_FACTOR) 
        {
            if(_verbose) std::cout << "  need to resize" << std::endl;
            rehash();
        }


        std::size_t index = get_bucket(key);
        auto& bucket = _table[index];

        if(_verbose) std::cout << "  insert into bucket " << index << std::endl;

        // Check if an existing key
        for (auto& pair : bucket) 
        {
            if (pair.first == key) 
            {

                if(_verbose) std::cout << "  insert updated existing " << index << std::endl;
                pair.second = value;  // Update existing
                return;
            }
        }

        bucket.push_back({key, value});
        _num_elements++;

        if(_verbose) std::cout << "  insert added new " << index << std::endl;
    }

    // Find value by key (returns std::optional - type V or nullopt)
    std::optional<V> find(const K& key) const 
    {        
        if(_verbose) std::cout << "Finding " << key << std::endl;

        // Get the bucket
        std::size_t index = get_bucket(key);
        const auto& bucket = _table[index];

        if(_verbose) std::cout << "  searching in " << key << " (index: " << index << ")" << std::endl;

        // Loop over items in bucket
        for (const auto& pair : bucket) 
        {
            if (pair.first == key) 
            {
                return pair.second;
            }
        }
        if(_verbose) std::cout << "  (not found)" << std::endl;
        return std::nullopt;
    }

    // Remove key (returns true if removed)
    bool erase(const K& key) 
    {
        std::size_t index = get_bucket(key);
        auto& bucket = _table[index];

        for (auto it = bucket.begin(); it != bucket.end(); it++) 
        {
            if (it->first == key) 
            {
                bucket.erase(it);
                _num_elements--;
                return true;
            }
        }
        return false;
    }

    // Debug: print _table structure
    void print() const 
    {
        for (std::size_t i = 0; i < _table.size(); i++) 
        {
            std::cout << "[" << i << "]: ";
            for (const auto& pair : _table[i]) 
            {
                std::cout << "(\"" << pair.first << "\", " << pair.second << ") ";
            }
            std::cout << "\n";
        }
        std::cout << "Elements: " << _num_elements << ", Buckets: " << _table.size() << "\n" << std::endl;
    }

private:

    // Get bucket index
    std::size_t get_bucket(const K& key) const 
    {
        auto hash = _hasher(key);
        auto bucket = hash % _table.size();
        if(_verbose)
        {
            std::cout << "key:        " << key << std::endl;
            std::cout << "  hash:     " << hash << std::endl;
            std::cout << "  bucket:   " << bucket << std::endl;
        }
        return bucket;
    }


    // Rehash when load factor is too high
    void rehash() 
    {
        std::size_t old_capacity = _table.size();
        std::size_t new_capacity = 2 * old_capacity;
        if(_verbose)
        {
            std::cout << "Rehashing" <<std::endl;
            std::cout << "Old capacity:     " << old_capacity <<std::endl;
            std::cout << "New capacity:     " << new_capacity <<std::endl;
        }

        std::vector<std::list<std::pair<K, V>>> new_table(new_capacity);

        for (const auto& bucket : _table) 
        {
            for (const auto& pair : bucket) 
            {
                std::size_t new_index = _hasher(pair.first) % new_capacity;
                new_table[new_index].push_back(pair);
            }
        }

        _table = std::move(new_table);
    }



public:

    // Ease of life - set up [] to write and read

    V& operator[](const K& key)
    {

        const std::size_t h = _hasher(key);
        std::size_t index = h % _table.size();
        auto& bucket = _table[index];

        // Update
        // return without rehashing
        for (auto& kv : bucket) 
        {
            if (kv.first == key) 
            {                
                return kv.second;
            }
        }

        // Insert
        // rehash *only if* adding one would exceed the load factor
        if (static_cast<double>(_num_elements + 1) / static_cast<double>(_table.size()) > MAX_LOAD_FACTOR) 
        {
            rehash();          // or next_prime(_table.size()*2)
            index = h % _table.size();          // recompute index after rehash
        }

        // Get the bucket to insert into
        auto& insert_bucket = _table[index];

        // Insert - default-construct V
        insert_bucket.emplace_back( 
                                        std::piecewise_construct,
                                        std::forward_as_tuple(key),
                                        std::forward_as_tuple()
                                    );

        // Increment counter
        ++_num_elements;
        return insert_bucket.back().second;
    }

    // Const version (for read-only access)
    const V& operator[](const K& key) const 
    {
        std::size_t index = get_bucket(key);
        const auto& bucket = _table[index];
        for (const auto& pair : bucket) 
        {
            if (pair.first == key) 
            {
                return pair.second; // reference into storage: safe
            }
        }
        throw std::out_of_range("Key not found");
    }


    

public:
    
    // Iterator

    class iterator 
    {

        using OuterTable = std::vector<std::list<std::pair<K, V>>>;
        using BucketIter = typename std::list<std::pair<K, V>>::iterator;

        OuterTable* _table_ptr;
        std::size_t _bucket_index;
        BucketIter  _bucket_iter;

        // Advance to next non-empty bucket
        void advance_to_nonempty() 
        {
            // Loop over buckets
            while (_bucket_index < _table_ptr->size() && _bucket_iter == (*_table_ptr)[_bucket_index].end()) 
            {
                ++_bucket_index;
                if (_bucket_index < _table_ptr->size())
                {
                    _bucket_iter = (*_table_ptr)[_bucket_index].begin();
                }
            }
        }

    public:

        // Iterator traits
        using iterator_category = std::forward_iterator_tag;
        using value_type        = std::pair<K, V>;
        using difference_type   = std::ptrdiff_t;
        using pointer           = value_type*;
        using reference         = value_type&;
        // Initializes an iterator at the given bucket and element position.
        // Automatically advances to the next non-empty bucket if needed.
        iterator(OuterTable* table_ptr, std::size_t bucket_index, BucketIter bucket_iter)
            : _table_ptr(table_ptr), _bucket_index(bucket_index), _bucket_iter(bucket_iter)
        {
            if (_table_ptr)
            {
                advance_to_nonempty();
            }
        }

        // Returns a reference to the current key–value pair.
        // Example: auto& kv = *it;
        reference operator*() const 
        { 
            return *_bucket_iter; 
        }

        // Returns a pointer to the current key–value pair.
        // Example: auto& k = it->first;
        pointer operator->() const 
        { 
            return &(*_bucket_iter); 
        }

        // Advances iterator to the next element in the hash table (pre-increment).
        iterator& operator++() 
        {
            ++_bucket_iter;
            advance_to_nonempty();
            return *this;
        }

        // Advances iterator to the next element in the hash table (post-increment).
        iterator operator++(int) 
        {            
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        // Returns true if both iterators point to the same element.
        bool operator==(const iterator& other) const 
        {
            return _table_ptr == other._table_ptr &&
                   _bucket_index == other._bucket_index &&
                   (_bucket_index == _table_ptr->size() || _bucket_iter == other._bucket_iter);
        }

        // Returns true if iterators point to different elements.
        bool operator!=(const iterator& other) const 
        {
            return !(*this == other);
        }

    };



    // Const iterator

    class const_iterator 
    {

        using OuterTable = const std::vector<std::list<std::pair<K, V>>>;
        using BucketIter = typename std::list<std::pair<K, V>>::const_iterator;

        OuterTable* _table_ptr;
        std::size_t _bucket_index;
        BucketIter  _bucket_iter;

        void advance_to_nonempty() 
        {
            // Loop over buckets
            while (_bucket_index < _table_ptr->size() && _bucket_iter == (*_table_ptr)[_bucket_index].end()) 
            {
                ++_bucket_index;
                if (_bucket_index < _table_ptr->size())
                {
                    _bucket_iter = (*_table_ptr)[_bucket_index].begin();
                }
            }
        }

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = const std::pair<K, V>;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const value_type*;
        using reference         = const value_type&;

        // Initializes a const_iterator at the given bucket and element position.
        // Automatically advances to the next non-empty bucket if needed.
        const_iterator(OuterTable* table_ptr, std::size_t bucket_index, BucketIter bucket_iter)
            : _table_ptr(table_ptr), _bucket_index(bucket_index), _bucket_iter(bucket_iter)
        {
            if (_table_ptr)
            {
                advance_to_nonempty();
            }
        }

        // Returns a reference to the current key–value pair.
        reference operator*() const 
        { 
            return *_bucket_iter; 
        }

        // Returns a pointer to the current key–value pair.
        pointer operator->() const 
        { 
            return &(*_bucket_iter); 
        }

        // Advances iterator to the next element in the hash table (pre-increment).
        const_iterator& operator++() 
        {
            ++_bucket_iter;
            advance_to_nonempty();
            return *this;
        }

        // Advances iterator to the next element in the hash table (post-increment).
        const_iterator operator++(int) 
        {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        // Returns true if both iterators point to the same element.
        bool operator==(const const_iterator& other) const 
        {
            return _table_ptr == other._table_ptr &&
                   _bucket_index == other._bucket_index &&
                   (_bucket_index == _table_ptr->size() || _bucket_iter == other._bucket_iter);
        }

        // Returns true if iterators point to different elements.
        bool operator!=(const const_iterator& other) const 
        {
            return !(*this == other);
        }


    };

    // begin() / end()
    iterator begin() {
        return iterator(&_table, 0, _table[0].begin());
    }

    iterator end() {
        return iterator(&_table, _table.size(), {});
    }

    const_iterator begin() const {
        return const_iterator(&_table, 0, _table[0].begin());
    }

    const_iterator end() const {
        return const_iterator(&_table, _table.size(), {});
    }

    const_iterator cbegin() const 
    { 
        return begin(); 
    }

    const_iterator cend() const 
    { 
        return end(); 
    }





    
};




#endif