#include <bits/stdc++.h>
#include "Role.hpp"
using namespace std;
using final::Base;
using final::Fighter;
using final::Protector;
using final::Caster;

Base* baseptrArray[1005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, h, att, round=0, cnt=0;
    string roleInput, nameInput;
    if(!(cin>>n)) return 0;
    for (int i = 0; i < n; ++i) {
        cin >> roleInput >> nameInput >> h >> att;
        if (roleInput == "Fighter") baseptrArray[i] = new Fighter(nameInput, h, att);
        if (roleInput == "Protector") baseptrArray[i] = new Protector(nameInput, h, att);
        if (roleInput == "Caster") baseptrArray[i] = new Caster(nameInput, h, att);
    }
    while (final::Base::getAliveNumber() > 1) {
        ++round;
        for (int i = 0; i < n; ++i) {
            Base* &ptr = baseptrArray[i];
            if (ptr->isAlive()) {
                ++cnt;
                if (cnt == 7) { ptr->defend(true); cnt = 0; }
                else ptr->defend(false);
            }
        }
        for (int i = 0; i < n; ++i) {
            Base* &ptr = baseptrArray[i];
            if (ptr->isAlive() && !ptr->isDefensive()){
                for (int j = 0; j < n; ++j) {
                    if (j != i && baseptrArray[j]->isAlive()) { ptr->launch_attack(baseptrArray[j]); break; }
                }
            }
        }
    }
    cout << round << '\n';
    for (int i = 0; i < n; ++i) delete baseptrArray[i];
    return 0;
}

