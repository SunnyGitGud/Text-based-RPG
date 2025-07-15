#pragma once
#include "hitpointtypes.hpp"
   


class hp {
    public:
        hp() : CurrentHP(1), MaxHP(1), ShieldHP(0) {}
        hp(ui16 cHP, ui16 mHP, ui16 sHP)
                : CurrentHP(cHP), MaxHP(mHP), ShieldHP(sHP)
            {
                if (CurrentHP > MaxHP) {
                    CurrentHP = MaxHP;
                }
            }


        bool setMaxHP(ui16 new_max_hp){
            if (new_max_hp < 1)
                return false;
           
            MaxHP = new_max_hp;
            
            if (CurrentHP > MaxHP)
            CurrentHP = MaxHP;
                return true;
        }

        void TakeDamage(ui16 damage){
            if (damage <= 0){
            return;
            }

            ui16 shieldPart = damage/2;
            ui16 hpPart = damage - shieldPart;


            if (ShieldHP >= shieldPart) {
                ShieldHP -= shieldPart;
            }
            else
            {
                hpPart += (shieldPart - ShieldHP);
                ShieldHP = 0;
            }

            if(hpPart >= CurrentHP) {
                CurrentHP = 0;
            }else {
                CurrentHP -= hpPart;
            }
        }

        void heal(ui16 HealAmount) {
            if (HealAmount + CurrentHP > MaxHP){
            CurrentHP = MaxHP;
            return;
            }
            CurrentHP += HealAmount;
        }


        ui16 getHP() const { return CurrentHP; }
        ui16 getMaxHP() const { return MaxHP; }
        ui16 getShield() const { return ShieldHP; }


    private:
    ui16 ShieldHP;
    ui16 CurrentHP;
    ui16 MaxHP;
};