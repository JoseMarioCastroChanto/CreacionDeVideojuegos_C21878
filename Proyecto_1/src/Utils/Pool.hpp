#ifndef POOL_HPP
#define POOL_HPP

#include <vector>

/**
 * @brief Interface for component pools.
 */
class IPool {
public:
    /**
     * @brief Virtual destructor for cleanup in derived classes.
     */
    virtual ~IPool() = default;
};

/**
 * @brief Template class managing a pool of components of type TComponent.
 * 
 * @tparam TComponent Type of component stored in the pool.
 */
template <typename TComponent>
class Pool : public IPool {
private:
    /// Internal storage for components.
    std::vector<TComponent> data;

public:
    /**
     * @brief Constructs a Pool with an optional initial size.
     * 
     * @param size Initial number of components in the pool (default 1000).
     */
    Pool(int size = 1000) {
        data.resize(size);
    }

    /**
     * @brief Default destructor.
     */
    virtual ~Pool() = default;

    /**
     * @brief Checks if the pool is empty.
     * 
     * @return true if the pool has no components, false otherwise.
     */
    bool IsEmpty() const {
        return data.empty();
    }

    /**
     * @brief Gets the current number of components in the pool.
     * 
     * @return Number of components.
     */
    int GetSize() const {
        return static_cast<int>(data.size());
    }

    /**
     * @brief Resizes the pool to hold a specified number of components.
     * 
     * @param n New size of the pool.
     */
    void Resize(int n) {
        data.resize(n);
    }

    /**
     * @brief Clears all components from the pool.
     */
    void Clear() {
        data.clear();
    }

    /**
     * @brief Adds a new component to the end of the pool.
     * 
     * @param object Component to add.
     */
    void Add(TComponent object) {
        data.push_back(object);
    }

    /**
     * @brief Sets the component at a given index.
     * 
     * @param index Index to set the component at.
     * @param object Component to set.
     */
    void Set(int index, TComponent object) {
        data[index] = object;
    }

    /**
     * @brief Accesses the component at a given index.
     * 
     * @param index Index of the component.
     * @return Reference to the component.
     */
    TComponent& Get(unsigned int index) {
        return static_cast<TComponent&>(data[index]);
    }

    /**
     * @brief Overloaded operator[] for component access.
     * 
     * @param index Index of the component.
     * @return Reference to the component.
     */
    TComponent& operator[](unsigned int index) {
        return static_cast<TComponent&>(data[index]);
    }
};

#endif
