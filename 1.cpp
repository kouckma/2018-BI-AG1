/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: kouckma
 *
 * Created on October 13, 2018, 10:30 PM
 */

#include <cstdlib>

#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

bool compare(pair<int, int> a, pair<int, int> b) {
    return (a.second < b.second);
}

class Vrchol {
    int jidlo = 0;
    int sousedi_count = 0;
    int minimum = 0;
    int maximum = 0;
    pair<int, int> best [100];
public:
    vector <int> sousedi;

    Vrchol(int INjidlo, int INmin, int INmax) {
        jidlo = INjidlo;
        minimum = INmin;
        maximum = INmax;
        sousedi.reserve(100);
        //        best.resize(INmax);
        for (int i = 0; i < maximum; i++) {
            best[i] = make_pair(i, 999999);
            //            cout<<best[i].first;
        }
        best[INjidlo].second = 0;
    }

    ~Vrchol() {
        //        delete best;
    }

    void pridej_best(int typ_potraviny, int vzdalenost) {
        if (best[typ_potraviny].second > vzdalenost)
            best[typ_potraviny].second = vzdalenost;
    }

    void pridej_souseda(int cislo_souseda) {
        sousedi.push_back(cislo_souseda);
        sousedi_count++;
    }

    int get_food() {
        return jidlo;
    }

    int get_foodDepth(int food) {
        return best[food].second;
    }

    int get_sousedi_count() {
        return sousedi_count;
    }

    void sorti() {
        sort(best, best + maximum, compare);
    }

    int getcenu(int id) {
        int pic = 0;
        //        sort(best.begin(), best.end(), compare);
        for (int n = 0; n < minimum; n++) {
            pic += best[n].second;
        }
        return pic;

    }

    void output() {
        //        sort(best.begin(), best.end(), compare);
        for (int n = 0; n < minimum; n++) {
            cout << " " << best[n].first;
        }
        cout << endl;


        //        cout <<"hello ?>>>"<< pic << endl;


    }


};

int main(int argc, char** argv) {

    ios_base::sync_with_stdio(false);
    //    cout << "here we go again";

    int vrcholy = 0;
    int hrany = 0;
    int maximum_potravin = 0;
    int minimum_potravin = 0;
    cin >> vrcholy;
    cin >> hrany;
    cin >> maximum_potravin;
    cin >> minimum_potravin;
    //for output purposes

//    vector< vector<int> > mapicka(vrcholy);
//    vector<int> ceny(vrcholy);
//    vector<int> pouzite(100,0);
    vector< Vrchol > mapka;
    mapka.reserve(vrcholy);

    int tmp = 0;
    int tmp2 = 0;
    for (int i = 0; i < vrcholy; i++) {
        cin >> tmp;
        mapka[i] = Vrchol(tmp, minimum_potravin, maximum_potravin);
    }
    for (int i = 0; i < hrany; i++) {
        cin >> tmp;
        cin >> tmp2;
        mapka[tmp].pridej_souseda(tmp2);
        mapka[tmp2].pridej_souseda(tmp);
    }
    //BFS

    for (int i = 0; i < vrcholy; i++) {
        int food = mapka[i].get_food();

        queue < pair<int, int> > que;
        que.push(make_pair(i, 0));
        int depth = 0;

        int temp_sousedi_count = 0;
        temp_sousedi_count = mapka[i].get_sousedi_count();
//        if()
        for (int j = 0; j < temp_sousedi_count; j++) {
            int index = mapka[i].sousedi[j];
                        if (mapka[index].get_foodDepth(food) > depth + 1 ) {
            que.push(make_pair(mapka[i].sousedi[j], depth + 1));
                            }
        }

        while (!que.empty()) {
            int temp = que.front().first;
            temp_sousedi_count = mapka[temp].get_sousedi_count();
            depth = que.front().second;
            que.pop();
//            test current vertex
                        if (mapka[temp].get_foodDepth(food) <= depth) {
                            continue;
                        } else {
                            mapka[temp].pridej_best(food, depth);
                        }
//            if (mapka[temp].get_foodDepth(food) > depth)
//                mapka[temp].pridej_best(food, depth);
//            else
//                continue;
            for (int j = 0; j < temp_sousedi_count; j++) {
                int index = mapka[temp].sousedi[j];
                if (mapka[index].get_foodDepth(food) > depth + 1) {
                    que.push(make_pair(mapka[temp].sousedi[j], depth + 1));
                }
            }
        }
    }
    long int celkem = 0;

    for (int g = 0; g < vrcholy; g++) {
        mapka[g].sorti();
        celkem += mapka[g].getcenu(g);
    }
    cout << celkem << endl;
    for (int g = 0; g < vrcholy; g++) {
        cout << mapka[g].getcenu(g);
        mapka[g].output();
    }


    return 0;
}
