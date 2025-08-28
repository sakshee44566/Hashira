#include <bits/stdc++.h>
#include "json.hpp"   // Include nlohmann/json header

using namespace std;
using json = nlohmann::json;

// Function to perform Lagrange interpolation at x=0
double lagrangeInterpolation(vector<int> &xs, vector<long long> &ys, int k) {
    double result = 0;
    for (int i = 0; i < k; i++) {
        double term = ys[i];
        for (int j = 0; j < k; j++) {
            if (i != j) {
                term *= (0.0 - xs[j]) / (xs[i] - xs[j]);
            }
        }
        result += term;
    }
    return result;
}

int main() {
    // Step 1: Read JSON from file
    ifstream file("input.json");
    json j;
    file >> j;

    int n = j["keys"]["n"];
    int k = j["keys"]["k"];

    vector<int> xs;
    vector<long long> ys;

    // Step 2: Decode y values
    for (auto& el : j.items()) {
        if (el.key() == "keys") continue;
        int x = stoi(el.key());
        int base = stoi(el.value()["base"].get<string>());
        string value = el.value()["value"];
        long long y = stoll(value, nullptr, base); // decode using base
        xs.push_back(x);
        ys.push_back(y);
    }

    // Step 3: Use first k points for interpolation
    double secret = lagrangeInterpolation(xs, ys, k);

    cout << "Secret (c) = " << llround(secret) << endl;

    return 0;
}