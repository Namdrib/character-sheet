#include <bits/stdc++.h>
using namespace std;

// Used for sorting/organising/otherwise using pair<string, T> by the string's length
template <typename T>
struct pair_first_string_length
{
	bool operator()(const pair<string, T> &p1, const pair<string, T> &p2)
	{
		return p1.first.size() < p2.first.size();
	}
};

// Pretty print a single stat (two columns)
void print_stat(const string &stat, const int length, const int level, const int skill_cap)
{
	cout << left << setfill(' ') << setw(length) << stat << " ";
	cout << "|" << string(level, '+');
	cout << string(skill_cap - level, ' ') << "|";
}

// Print input map in four columns such that:
// left column shows stat name, right column shows number of attributes
// ^ do this twice with 3 spaces in the middle
// str1    int1   str4    int4
// str2    int2   string5 int5
// string3 int3   str6    int6
// If border is set, print a nice border around the outside :)
void column_print(vector<pair<string, int>> &stats, int skill_cap, bool border=false)
{
	size_t num = stats.size();
	size_t half = num/2;
	size_t mid_gap = 3;
	int longest_string_left = max_element(stats.begin(), stats.begin() + half, pair_first_string_length<int>())->first.size();
	int longest_string_right = max_element(stats.begin() + half, stats.end(), pair_first_string_length<int>())->first.size();
	size_t full_length = longest_string_left + mid_gap + longest_string_right + 2 * (2 + skill_cap + 3);
	if (border)
	{
		cout << "+" << string(full_length, '-') << "+" << endl;
		cout << "|" << string(full_length, ' ') << "|" << endl;
	}
	for (size_t i=0; i<half; i++)
	{
		if (border)
		{
			cout << "|  ";
		}
		print_stat(stats[i].first, longest_string_left, stats[i].second, skill_cap);
		if (num%2 == 0 || (num&1 && i < half))
		{
			cout << string(mid_gap, ' ');
			print_stat(stats[i + half].first, longest_string_right, stats[i + half].second, skill_cap);
		}
		else
		{
			if (border)
			{
				cout << string(mid_gap + longest_string_right + skill_cap + 3, ' ');
			}
		}
		if (border)
		{
			cout << "  |";
		}

		cout << endl;
	}
	if (border)
	{
		cout << "|" << string(full_length, ' ') << "|" << endl;
		cout << "+" << string(full_length, '-') << "+" << endl;
	}
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		cerr << "Usage: " << argv[0] << " stat_file [border]" << endl;
		exit(1);
	}

	ifstream ifs(argv[1]);
	if (!ifs.is_open())
	{
		cerr << "Could not open file " << argv[1] << endl;
		exit(2);
	}

	// How many points to spend and max points into a single skill
	int max_points, skill_cap;
	ifs >> max_points >> skill_cap;
	ifs.ignore();

	// Assume name is a single string (no spaces), and class can contain strings
	string name, role; // role should be class, but that's reserved
	ifs >> name;
	ifs.ignore(1); // Ignore the space after name
	getline(ifs, role);

	// Read stats from stat_file
	// Not a map because I need to know halfway whene printing
	vector<pair<string, int>> stats; // stat and the level
	int sum = 0;
	for (string temp; getline(ifs, temp);)
	{
		size_t split_pos = temp.find_last_of(" ");
		string temp1 = temp.substr(0, split_pos);
		int temp2 = stoi(temp.substr(split_pos+1));
		if (temp2 < 0 || temp2 > skill_cap)
		{
			cout << "Skipping " << temp1 << " " << temp2 << ": invalid number. Must be between 0 and " << skill_cap << " inclusive" << endl;
		}
		else if (sum + temp2 > max_points)
		{
			cout << "Skipping " << temp1 << " " << temp2 << ": exceeds " << max_points << " points" << endl;
		}
		else
		{
			stats.push_back(make_pair(temp1, temp2));
			sum += temp2;
		}
	}
	if (sum < max_points)
	{
		cout << "Still have " << max_points - sum << " points to invest" << endl;
	}

	// Pretty-print stats
	cout << "Name: " << name << "  Class: " << role << endl;
	column_print(stats, skill_cap, argc > 2);
}
