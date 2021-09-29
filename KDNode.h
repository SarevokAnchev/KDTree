//
// Created by Louis on 24/09/2021.
//

#pragma once

#include <memory>
#include <vector>

template<typename T>
class KDNode {
private:
    std::shared_ptr<KDNode> m_left;
    std::shared_ptr<KDNode> m_right;

    size_t m_dim;
    std::vector<double> m_coords;

    T m_data;

    size_t m_axis;

public:
    KDNode(std::vector<double> coords_, T data_, size_t axis_)
        : m_coords(std::move(coords_)), m_axis(axis_), m_data(data_)
    {
        m_dim = m_coords.size();
        m_left = nullptr;
        m_right = nullptr;
    }

    inline std::shared_ptr<KDNode<T>> right() { return m_right; }
    inline std::shared_ptr<KDNode<T>> left() { return m_left; }

    inline void set_right(std::shared_ptr<KDNode<T>> node_) { m_right = node_; }
    inline void set_left(std::shared_ptr<KDNode<T>> node_) { m_left = node_; }

    [[nodiscard]] double coord(size_t axis_) const { return m_coords[axis_]; }

    [[nodiscard]] inline size_t get_dim() const noexcept { return m_dim; }

    [[nodiscard]] inline T get_data() const noexcept { return m_data; }

    [[nodiscard]] inline size_t get_axis() const noexcept { return m_axis; }

    [[nodiscard]] inline size_t next_axis() const noexcept
    {
        return (m_axis+1)%m_dim;
    }
};


