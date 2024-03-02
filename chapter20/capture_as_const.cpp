#include <iostream>

int main(void)
{
    int ammo{10};

    auto shoot{
        [ammo]() mutable {//// We're allowed to modify ammo now
            --ammo;//won’t compile, because ammo is treated as const within the lambda.
            std::cout << "Pew! " << ammo << " shot(s) left.\n";
        }
    };

    shoot();
    shoot();

    std::cout << ammo << " shot(s) left\n";

    return 0;
} 
