#include <string>
#include <iostream>
#ifndef ROLE_HPP
#define ROLE_HPP
namespace final{

    class Fighter;
    class Protector;
    class Caster;

    class Base{
        friend class Fighter;
        friend class Protector;
        friend class Caster;
    private:
        std::string name;
        int health, attack;
        bool alive, defensive;
        inline static int aliveNumber = 0;
    protected:
        Base(const std::string& n, const int h, const int a)
            : name(n), health(h), attack(a), alive(true), defensive(false) {
            ++aliveNumber;
        }
    public:
        virtual ~Base(){
            if (alive) --aliveNumber;
        }
        virtual void launch_attack(Base* target) = 0;
        virtual void defend(bool flag) = 0;
        static int getAliveNumber(){ return aliveNumber; }
        bool isAlive(){ return alive; }
        bool isDefensive(){ return defensive; }
    };

    class Fighter:public Base{
    public:
        Fighter (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 3;
                attack += 2;
            } else {
                defensive = 0;
            }
        }
    };

    class Protector:public Base{
    public:
        Protector (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 7;
                attack += 1;
            } else {
                defensive = 0;
            }
        }
    };

    class Caster:public Base{
    public:
        Caster (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 5;
            } else {
                defensive = 0;
            }
        }
    };

    inline int typeEffect(Base* atk, Base* def){
        if (dynamic_cast<Fighter*>(atk) && dynamic_cast<Caster*>(def)) return 2;
        if (dynamic_cast<Caster*>(atk) && dynamic_cast<Protector*>(def)) return 2;
        if (dynamic_cast<Protector*>(atk) && dynamic_cast<Fighter*>(def)) return 2;
        return 1;
    }

    void Fighter::launch_attack(Base *target) {
        int mult = typeEffect(this, target);
        int dmg_to_target = attack * mult;
        int dmg_to_self = target->attack; // reflected, unless caster
        if (target->defensive){
            int net = dmg_to_target - target->attack;
            if (net > 0) target->health -= net;
            this->health -= dmg_to_self;
        } else {
            target->health -= dmg_to_target;
        }
        // resolve deaths: target first, then self
        if (target->alive && target->health <= 0){
            target->alive = false;
            --Base::aliveNumber;
            const char* role = dynamic_cast<Fighter*>(target)?"Fighter":(dynamic_cast<Protector*>(target)?"Protector":"Caster");
            std::cout << role << ' ' << target->name << " is killed\n";
        }
        if (this->alive && this->health <= 0){
            this->alive = false;
            --Base::aliveNumber;
            std::cout << "Fighter" << ' ' << this->name << " is killed\n";
        }
    }

    void Protector::launch_attack(Base *target) {
        int mult = typeEffect(this, target);
        int dmg_to_target = attack * mult;
        int dmg_to_self = target->attack; // reflected, unless caster
        if (target->defensive){
            int net = dmg_to_target - target->attack;
            if (net > 0) target->health -= net;
            this->health -= dmg_to_self;
        } else {
            target->health -= dmg_to_target;
        }
        if (target->alive && target->health <= 0){
            target->alive = false;
            --Base::aliveNumber;
            const char* role = dynamic_cast<Fighter*>(target)?"Fighter":(dynamic_cast<Protector*>(target)?"Protector":"Caster");
            std::cout << role << ' ' << target->name << " is killed\n";
        }
        if (this->alive && this->health <= 0){
            this->alive = false;
            --Base::aliveNumber;
            std::cout << "Protector" << ' ' << this->name << " is killed\n";
        }
    }

    void Caster::launch_attack(Base *target) {
        int mult = typeEffect(this, target);
        int dmg_to_target = attack * mult;
        if (target->defensive){
            int net = dmg_to_target - target->attack;
            if (net > 0) target->health -= net;
            // caster takes no reflected damage
        } else {
            target->health -= dmg_to_target;
        }
        if (target->alive && target->health <= 0){
            target->alive = false;
            --Base::aliveNumber;
            const char* role = dynamic_cast<Fighter*>(target)?"Fighter":(dynamic_cast<Protector*>(target)?"Protector":"Caster");
            std::cout << role << ' ' << target->name << " is killed\n";
        }
        if (this->alive && this->health <= 0){
            this->alive = false;
            --Base::aliveNumber;
            std::cout << "Caster" << ' ' << this->name << " is killed\n";
        }
    }
}
#endif //ROLE_HPP
