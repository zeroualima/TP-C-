#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <chrono>
#include <random>
#include <array>
#include <string>

class Particule {
private:
    std::array<double, 3> position;
    std::array<double, 3> vitesse;
    std::array<double, 3> force;
    double masse;
    int identifiant;
    std::string categorie;

public:
    Particule(std::array<double, 3> p, std::array<double, 3> v, std::array<double, 3> f, double m, int id, std::string cat) {
        position = p; 
        vitesse = v; 
        force = f;
        masse = m; 
        identifiant = id; 
        categorie = cat;
    }
};

Particule creerParticuleAleatoire(std::mt19937& mt, std::uniform_real_distribution<double>& dist, int id) {
    std::array<double, 3> p = {dist(mt), dist(mt), dist(mt)};
    std::array<double, 3> v = {dist(mt), dist(mt), dist(mt)};
    std::array<double, 3> f = {dist(mt), dist(mt), dist(mt)};
    double m = dist(mt);
    return Particule(p, v, f, m, id, "Type_A");
}

void testerPerformances(int nbParticules) {
    std::cout << "--- Test pour " << nbParticules << " particules ---\n";

    // Initialisation du générateur aléatoire 
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    // std::vector
    {
        std::vector<Particule> collectionVector;
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < nbParticules; ++i) {
            collectionVector.push_back(creerParticuleAleatoire(mt, dist, i));
        }
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "std::vector : " << elapsed.count() << "s\n";
    }

    // std::list
    {
        std::list<Particule> collectionList;
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < nbParticules; ++i) {
            collectionList.push_back(creerParticuleAleatoire(mt, dist, i));
        }
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "std::list   : " << elapsed.count() << "s\n";
    }

    // std::deque
    {
        std::deque<Particule> collectionDeque;
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < nbParticules; ++i) {
            collectionDeque.push_back(creerParticuleAleatoire(mt, dist, i));
        }
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "std::deque  : " << elapsed.count() << "s\n";
    }
    std::cout << "\n";
}

// void SV(std::vector<Particule> Particules, double t_end, double delta_t) {
    
// }

int main() {
    // Test pour différentes tailles 
    std::vector<int> tailles = {64, 128, 256, 512, 1024, 2048, 10000, 100000, 1000000};
    
    for (int taille : tailles) {
        testerPerformances(taille);
    }

    return 0;
}