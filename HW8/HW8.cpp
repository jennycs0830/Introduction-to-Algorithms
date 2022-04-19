#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <utility>
#include <vector>
#include <list>
#include <math.h>
#include <algorithm>

using namespace std;

int main() {
    ifstream Input;
    ofstream Output;
    Input.open("input.txt");
    Output.open("output.txt");

    int n, l, w, p, r, ans_count;
    double pos_l, pos_r, temp, cur_Lmost, cur_Rmost; //clm: current left most; clr: current largest right
    bool gap;
    list<pair<double, double> > segments;
    list<pair<double, double> >::iterator iter;
    while (!Input.eof()) {
        Input >> n >> l >> w;
        //input the circles, calculate the segments, build up the list
        for (int i = 0; i < n; i++) {
            Input >> p >> r;
            if (double(r) > double(w) / 2.0) {
                //calculate the pos_l & pos_r
                temp = sqrt(r * r - double(double(w) / 2.0) * double(double(w) / 2.0));
                pos_l = p - temp;
                pos_r = p + temp;
                //insert the segment to the list according to the pos_l
                if (segments.empty()) {
                    segments.push_back(make_pair(pos_l, pos_r));
                }
                else {
                    iter = segments.begin();
                    while (pos_l > iter->first && iter != segments.end()) iter++;
                    segments.insert(iter, make_pair(pos_l, pos_r));
                }
            }
        }
        //count the minimal # of circle(segments) required
        ans_count = 0;
        cur_Lmost = 0;
        cur_Rmost = 0;
        gap = false;
        iter = segments.begin();
        while (iter != segments.end() && cur_Rmost < l) {
            // cout << "clm: " << clm << "; clr: " << clr << "\n";   
            if (iter->second > cur_Rmost && iter->first <= cur_Lmost) {
                cur_Rmost = iter->second;
            }
            else if (iter->first > cur_Lmost && cur_Lmost == cur_Rmost) {
                gap = true;
            }
            else if (iter->first > cur_Lmost) {
                cur_Lmost = cur_Rmost;
                ans_count++;
                iter--;
            }
            iter++;
        }
        if (cur_Rmost < l || gap) {
            Output << -1 << "\n";
        }
        else if (n == 0) {
            Output << 0 << "\n";
        }
        else {
            Output << ans_count + 1 << "\n";  // + 1: left the loop when clr >= l, 
                                            //      but the final segment is not counted
        }
        
        // for (auto x : segments) fout << "left: " << x.first << "; right: " << x.second << "\n";

        segments.clear();
    }

    Input.close();
    Output.close();

    return 0;
}