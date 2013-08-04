#include <sstream>
#include <fstream>
#include <iomanip>
#include <map>

using namespace std;

const string my_email = "emailbeiyong@sina.com";

void length()
{
    ifstream fi("input.txt");
    ofstream fo("output.txt");

    fo << my_email << endl << endl;

    map<string, double> rate;

    string trans_rule;
    while (getline(fi, trans_rule)) {
        if (trans_rule.size() == 0)
            break;

        istringstream si(trans_rule);

        string unit_a, unit_b, equal_sign;
        double val_a,  val_b;

        si >> val_a >> unit_a >> equal_sign
           >> val_b >> unit_b;

        if (unit_a == "m") {
            rate[unit_b]      =
            rate[unit_b+"s"]  =
            rate[unit_b+"es"] = val_a / val_b;
        } else {
            rate[unit_a]      =
            rate[unit_a+"s"]  =
            rate[unit_a+"es"] = val_b / val_a;
        }
    }
    if (rate.find("feet") == rate.end() &&
        rate.find("foot") != rate.end()) {
        rate["feet"] = rate["foot"];
    } else if (rate.find("feet") != rate.end() &&
               rate.find("foot") == rate.end()) {
        rate["foot"] = rate["feet"];
    }

    string expression;
    while (getline(fi, expression)) {
        if (expression.size() == 0)
            continue;

        istringstream si(expression);

        string unit, eq;
        double ans = 0.0, val;
        double pos = 1.0;

        while (si >> val >> unit) {
            ans += pos * rate[unit] * val;
            si >> eq;
            if (eq == "+") {
                pos = 1.0;
            } else {
                pos = -1.0;
            }
        }
        fo << fixed << setprecision(2) << ans << " m" << endl;
    }
    fi.close();
    fo.close();
}

int main()
{
    length();
    return 0;
}
