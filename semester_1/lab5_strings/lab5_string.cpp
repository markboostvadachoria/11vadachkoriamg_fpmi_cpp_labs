#include<iostream>
#include<string>
#include<vector>


void string_To_Words(std::vector <std::string>& w, std::string s)
{
	std::string wrd = "";
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] <= '9' && s[i] >= '0') {
			wrd.push_back(s[i]);
		}
		else
		{
			
			w.push_back(wrd);
			wrd = "";
		}
	}
	w.push_back(wrd);
	
}

bool isDigit(std::string s)
{
	for (int i = 0; i < s.size(); i++)
		if (!(s[i] >= '0' && s[i] <= '9'))
			return false;
	return true;
}

std::string maxWord(std::vector<std::string> w)
{
	std::string maxNow = "";

	for (int i = 0; i < w.size(); i++)
	{
		if (!isDigit(w[i]))
			exit(1);
		else
		{
			if (w[i] >= maxNow) {
				maxNow = w[i];

				
			}
		}
	}
	return maxNow;

}

void newString(std::vector <std::string> w, std::string& s)
{
	
	std::string newS, max = maxWord(w);
	newS += max;
	newS += ' ';
	int cntmax = 0;
	for (int i = 0; i < w.size(); i++)
		if (w[i] == max)
			cntmax++;
	int cnt = 0;
	for (int i = 0; i < w.size(); i++)
	{
		if (w[i] < max) {
			newS += w[i];
			newS += " ";

		}
		else if (w[i] == max ) {
			if (cnt != cntmax - 2) {
				newS += w[i];
				newS += " ";
				cnt++;
			}
			else
				cnt++;
		}
	}
	s = newS;
}

int main()
{
	std::string s;
	std::vector<std::string> words;
	std::getline(std::cin, s);
	string_To_Words(words, s);
	newString(words, s);
	std::cout << s;

	return 0;
}