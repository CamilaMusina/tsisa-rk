#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include <utility>

struct Individ
{
    long double x, y, fit;
};

double func(long double x, long double y) {
    return 1 / std::sqrt(0.01 + pow(x, 2) + pow(y, 2));
}

long double AvrValue(std::vector<Individ>& population) {
    long double res = 0.0;
    for (const auto& ind : population) {
        res += ind.fit;
    }
    return res / 6;
}

long double MaxValue(std::vector<Individ>& population) {
    long double maxp = 0.0;
    for (const auto& ind : population) {
        if (ind.fit > maxp)
            maxp = ind.fit;
    }
    return maxp;
}

bool SortIndivid(const Individ& ind1, const Individ& ind2) {
    return ind1.fit > ind2.fit;
};


void AvrMax(std::vector<Individ>population, int n)
{
    std::cout << "N: " << n << " Average value: " << AvrValue(population) << " Max value: " << MaxValue(population) << std::endl;
    for (const auto& ind : population) {
        std::cout << "x: " << ind.x << " y: " << ind.y << " fit: " << ind.fit << std::endl;
    }
    std::cout << std::endl;
}


int main()
{
    std::vector<Individ>Population(6);
    std::mt19937 gen(time(0));
    std::uniform_real_distribution<long double> urd(-1, 1);
    std::uniform_real_distribution<long double> pr(0, 1);
    int n = 100; 
    long double p_mut = 0.25;

    for (auto i = 0; i < Population.size(); i++) {
        Individ ind;
        ind.x = urd(gen);
        ind.y = urd(gen);
        ind.fit = func(ind.x, ind.y);
        Population[i] = ind;
    }
    AvrMax(Population, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < Population.size(); j++) {
            long double p = pr(gen);
            if (p < p_mut) {
                Population[j].x = urd(gen);
                Population[j].y = urd(gen);
                Population[j].fit = func(Population[j].x,Population[j].y);
            }
        }
        std::sort(Population.begin(), Population.end(), SortIndivid);
        std::vector<Individ>new_population(6);

        new_population[0].x = Population[0].x;
        new_population[0].y = Population[1].y;
        new_population[0].fit = func(new_population[0].x, new_population[0].y);

        new_population[1].x = Population[1].x;
        new_population[1].y = Population[0].y;
        new_population[1].fit = func(new_population[1].x, new_population[1].y);

        new_population[2].x = Population[0].x;
        new_population[2].y = Population[2].y;
        new_population[2].fit = func(new_population[2].x, new_population[2].y);

        new_population[3].x = Population[2].x;
        new_population[3].y = Population[0].y;
        new_population[3].fit = func(new_population[3].x, new_population[3].y);

        new_population[4].x = Population[0].x;
        new_population[4].y = Population[3].y;
        new_population[4].fit = func(new_population[2].x, new_population[2].y);

        new_population[5].x = Population[3].x;
        new_population[5].y = Population[0].y;
        new_population[5].fit = func(new_population[2].x, new_population[2].y);

        Population = new_population;
        AvrMax(Population, i);
    }
}

