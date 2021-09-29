//
// Created by Louis on 24/09/2021.
//

#pragma once

#include <memory>

#include "KDNode.h"

template <typename T>
class KDTree {
private:
    std::shared_ptr<KDNode<T>> m_root;

    size_t m_dim;

public:
    KDTree()
        : m_root(nullptr), m_dim(0)
    {}

    void add_nodes(std::vector<std::vector<double>> coords_, std::vector<T> data_)
    {
        for (int i = 0; i < coords_.size(); i++) {
            add_node(coords_[i], data_[i]);
        }
    }

    void add_node(std::vector<double> coords_, T data_)
    {
        if (!m_root) {
            m_root = std::make_shared<KDNode<T>>(coords_, data_, 0);
            m_dim = coords_.size();
            return;
        }
        bool placed = false;
        std::shared_ptr<KDNode<T>> ptr_next = m_root;
        std::shared_ptr<KDNode<T>> ptr_prev;
        while (!placed) {
            auto axis = ptr_next->get_axis();
            ptr_prev = ptr_next;
            if (ptr_next->coord(axis) > coords_[axis]) {
                ptr_next = ptr_next->left();
                if (!ptr_next) {
                    ptr_prev->set_left(std::make_shared<KDNode<T>>(coords_, std::move(data_), ptr_prev->next_axis()));
                    placed = true;
                }
            }
            else {
                ptr_next = ptr_next->right();
                if (!ptr_next) {
                    ptr_prev->set_right(std::make_shared<KDNode<T>>(coords_, std::move(data_), ptr_prev->next_axis()));
                    placed = true;
                }
            }
        }
    }

    std::shared_ptr<KDNode<T>> get_closest_node(const std::vector<double>& coords_) const
    {

    }
};

