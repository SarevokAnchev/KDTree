//
// Created by Louis on 24/09/2021.
//

#pragma once

#include <memory>
#include <vector>

#include "KDNode.h"

template <typename T>
class KDTree {
private:
    std::shared_ptr<KDNode<T>> m_root;

    size_t m_dim;

    std::shared_ptr<KDNode<T>> _explore_from_top(const std::vector<double>& coords, double* best_dist)
    {
        // TODO : DFS
    }

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
        if (!m_root) {
            return nullptr;
        }
        // descend in the tree
        std::vector<std::shared_ptr<KDNode<T>>> path;
        bool last_branch_right = true;
        auto ptr_next = m_root;
        while (ptr_next) {
            auto axis = ptr_next->get_axis();
            path.emplace_back(ptr_next);
            if (ptr_next->coord(axis) > coords_[axis]) {
                ptr_next = ptr_next->left();
                last_branch_right = false;
            }
            else {
                ptr_next = ptr_next->right();
                last_branch_right = true;
            }
        }

        // ascend and compare distances
        auto idx = path.size() - 1;
        std::shared_ptr<KDNode<T>> cur_node = path[idx];
        std::shared_ptr<KDNode<T>> cur_best = path.back();
        auto min_dist = cur_best->dist(coords_);
        auto found = false;
        while (!found && cur_node != m_root) {

        }
        return cur_best;
    }
};
