#include <iostream>
#include <vector>
#include <memory>
using namespace std;
class Herbivore {
public:
    virtual ~Herbivore() = default;
    virtual void EatGrass() = 0;
    virtual int GetWeight() const = 0;
    virtual bool IsAlive() const = 0;
};
class Carnivore {
public:
    virtual ~Carnivore() = default;
    virtual void Eat(shared_ptr<Herbivore> herbivore) = 0;
    virtual int GetPower() const = 0;
};
class Wildebeest : public Herbivore {
private:
    int weight;
    bool alive;
public:
    Wildebeest() : weight(50), alive(true) {}
    void EatGrass() override { 
        weight += 10; 
    }
    int GetWeight() const override { 
        return weight; 
    }
    bool IsAlive() const override { 
        return alive; 
    }
};
class Bison : public Herbivore {
private:
    int weight;
    bool alive;
public:
    Bison() : weight(60), alive(true) {}
    void EatGrass() override { 
        weight += 10; 
    }
    int GetWeight() const override { 
        return weight; 
    }
    bool IsAlive() const override { 
        return alive; 
    }
};
class Elk : public Herbivore {
private:
    int weight;
    bool alive;
public:
    Elk() : weight(55), alive(true) {}
    void EatGrass() override { 
        weight += 10; 
    }
    int GetWeight() const override { 
        return weight; 
    }
    bool IsAlive() const override { 
        return alive; 
    }
};
class Lion : public Carnivore {
private:
    int power;
public:
    Lion() : power(70) {}
    void Eat(shared_ptr<Herbivore> herbivore) override {
        if (power > herbivore->GetWeight()) {
            power += 10;
        }
        else {
            power -= 10;
        }
    }
    int GetPower() const override { 
        return power; 
    }
};
class Wolf : public Carnivore {
private:
    int power;
public:
    Wolf() : power(50) {}
    void Eat(shared_ptr<Herbivore> herbivore) override {
        if (power > herbivore->GetWeight()) {
            power += 10;
        }
        else {
            power -= 10;
        }
    }
    int GetPower() const override { 
        return power; 
    }
};
class Tiger : public Carnivore {
private:
    int power;
public:
    Tiger() : power(65) {}
    void Eat(shared_ptr<Herbivore> herbivore) override {
        if (power > herbivore->GetWeight()) {
            power += 10;
        }
        else {
            power -= 10;
        }
    }
    int GetPower() const override { 
        return power; 
    }
};
class Continent {
public:
    virtual ~Continent() = default;
    virtual shared_ptr<Herbivore> CreateHerbivore() = 0;
    virtual shared_ptr<Carnivore> CreateCarnivore() = 0;
};
class Africa : public Continent {
public:
    shared_ptr<Herbivore> CreateHerbivore() override {
        return make_shared<Wildebeest>();
    }
    shared_ptr<Carnivore> CreateCarnivore() override {
        return make_shared<Lion>();
    }
};
class NorthAmerica : public Continent {
public:
    shared_ptr<Herbivore> CreateHerbivore() override {
        return make_shared<Bison>();
    }
    shared_ptr<Carnivore> CreateCarnivore() override {
        return make_shared<Wolf>();
    }
};
class Eurasia : public Continent {
public:
    shared_ptr<Herbivore> CreateHerbivore() override {
        return make_shared<Elk>();
    }
    shared_ptr<Carnivore> CreateCarnivore() override {
        return make_shared<Tiger>();
    }
};
class AnimalWorld {
private:
    shared_ptr<Continent> continent;
    vector<shared_ptr<Herbivore>> herbivores;
    vector<shared_ptr<Carnivore>> carnivores;
public:
    AnimalWorld(shared_ptr<Continent> c) : continent(c) {
        herbivores.push_back(continent->CreateHerbivore());
        carnivores.push_back(continent->CreateCarnivore());
    }
    void MealsHerbivores() {
        for (auto& herbivore : herbivores) {
            herbivore->EatGrass();
        }
    }
    void NutritionCarnivores() {
        for (auto& carnivore : carnivores) {
            for (auto& herbivore : herbivores) {
                if (herbivore->IsAlive()) {
                    carnivore->Eat(herbivore);
                }
            }
        }
    }
    void ShowStatus() {
        for (const auto& herbivore : herbivores) {
            cout << "Herbivore Weight: " << herbivore->GetWeight() << ", Alive: " << herbivore->IsAlive() << endl;
        }
        for (const auto& carnivore : carnivores) {
            cout << "Carnivore Power: " << carnivore->GetPower() << endl;
        }
    }
};

int main() {
    shared_ptr<Continent> africa = make_shared<Africa>();
    shared_ptr<Continent> northAmerica = make_shared<NorthAmerica>();
    shared_ptr<Continent> eurasia = make_shared<Eurasia>();

    AnimalWorld worldAfrica(africa);
    AnimalWorld worldNorthAmerica(northAmerica);
    AnimalWorld worldEurasia(eurasia);

    cout << "Africa:" << endl;
    worldAfrica.MealsHerbivores();
    worldAfrica.NutritionCarnivores();
    worldAfrica.ShowStatus();

    cout << "\nNorth America:" << endl;
    worldNorthAmerica.MealsHerbivores();
    worldNorthAmerica.NutritionCarnivores();
    worldNorthAmerica.ShowStatus();

    cout << "\nEurasia:" << endl;
    worldEurasia.MealsHerbivores();
    worldEurasia.NutritionCarnivores();
    worldEurasia.ShowStatus();

    return 0;
}
