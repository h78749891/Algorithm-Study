#include <iostream>
#include <vector>

using namespace std;

struct Group {
    long long index;
    long long member_count;
    long long candy_count;
    Group():
        index(0LL),
        member_count(0LL),
        candy_count(0LL)
    {}
    Group(long long index, long long member_count, long long candy_count):
        index(index),
        member_count(member_count),
        candy_count(candy_count)
    {}
    Group& operator+=(const Group& rhs) {
        member_count += rhs.member_count;
        candy_count += rhs.candy_count;
        return *this;
    }
};

class Town {
private:
    long long children_count_;
    long long children_alart_count_;
    vector<Group> groups_;
public:
    Town(long long children_count, long long children_alart_count):
        children_count_(children_count),
        children_alart_count_(children_alart_count),
        groups_(vector<Group>{})
    {
        groups_.reserve(children_count_ + 1LL);
        groups_.emplace_back();
    }
    void read(long long relations) {
        for(long long childeren_index = 1LL; childeren_index <= children_count_; ++childeren_index) {
            long long candy{};
            cin >> candy;
            groups_.emplace_back(childeren_index, 1, candy);
        }
        for(long long relation_it = 0LL; relation_it < relations; ++relation_it) {
            long long left_group{};
            long long right_group{};
            cin >> left_group >> right_group;
            merge(groups_[left_group], groups_[right_group]);
        }
    }
    void merge(Group& lhs, Group& rhs) {
        Group& super_lhs = groups_[find(lhs.index)];
        Group& super_rhs = groups_[find(rhs.index)];
        if(super_lhs.index == super_rhs.index) {return;}
        super_lhs += super_rhs;
        super_rhs = super_lhs;
    }
    long long find(long long index) {
        if(groups_[index].index != index) {
            long long top_index = find(groups_[index].index);
            groups_[index] = groups_[top_index];
            return top_index;
        }
        return index;
    }
    long long findMaxCandy() {
        vector<long long> max_candy(children_alart_count_, 0LL);
        for(long long it = 1LL; it <= children_count_; ++it) {
            if(groups_[it].index != it) {continue;}
            long long& member_count = groups_[it].member_count;
            long long& candy_count = groups_[it].candy_count;
            for(long long robbed_it = children_alart_count_ - 1LL; member_count <= robbed_it; --robbed_it) {
                long long added_candy_count = max_candy[robbed_it - member_count] + candy_count;
                if(added_candy_count < max_candy[robbed_it]) {continue;}
                max_candy[robbed_it] = added_candy_count; 
            }
        }
        return max_candy[children_alart_count_ - 1];
    }
};

int main() {
    // initiate fast io
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    long long children, relation, alart;
    cin >> children >> relation >> alart;
    Town town{children, alart};
    town.read(relation);
    cout << town.findMaxCandy();
    return 0;
}