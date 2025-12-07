#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include<vector>


bool isRussianChar(char& c)
{
    return (c >= -64 && c <= -1) || (c == -88 || c == -72);
}

std::string nowMaxSubStr(std::string& s)
{
    if (s.empty()) return ""; 

    int i = 0;
    std::string max_substr = "";

    while (i < s.size())
    {
        bool flag = false;
        std::string tmp_max_substr = "";
        while (true)
        {
            if (i == s.size() - 1)
            {

                if (s[i] == s[i - 1] && isRussianChar(s[i]))
                {
                    tmp_max_substr += s[i];
                    flag = true;
                    break;
                }
                flag = true;
                break;
            }
            if (isRussianChar(s[i]))
                tmp_max_substr += s[i];
            //    std::cout << tmp_max_s << ' ' << i << '\n';
            if (s[i] != s[i + 1] || !isRussianChar(s[i])) {
                i++;
                break;
            }
            i++;


        }
        
        
        if (tmp_max_substr.length() > max_substr.length())
        {
            max_substr = tmp_max_substr;
        }

        if (flag)
            break;
    }

    return max_substr;
}

void printStr(int com_max_substrSize, std::vector <std::pair<std::string, int>>& str_substrSize)
{

    int cnt = 0;
    
    for (auto i : str_substrSize) {
        if (i.second == com_max_substrSize) {
            std::cout << i.first << '\n';
            cnt++;
        }
       if (cnt > 10)
         break;
        
    }
}


int main()
{
    try {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);

        const std::string FILE = "input.txt";
        std::ifstream fin(FILE);
        if (fin.is_open())
        {
            if (fin.peek() == EOF)
                throw "Файл пуст";
            std::cout << "файл октрыт!\n";
            std::string s, com_m_substr = "";
            std::vector <std::pair<std::string, int>> str_substr;
            while (std::getline(fin, s)) {
                std::string now_m_substr = nowMaxSubStr(s);
                //std::cout << now_m_substr << std::endl;
                str_substr.push_back({ s,now_m_substr.size() });
                if (now_m_substr.size() > com_m_substr.size())
                    com_m_substr = now_m_substr;




            }
            if (com_m_substr.empty())
                throw "Файл не содержит ни одного русского символа!";
            printStr(com_m_substr.size(), str_substr);
        }
        else if (!fin.is_open())
            throw "Не удалось открыть файл!";

        fin.close();
    }
    catch (const char* error)
    {
        std::cout << "ERROR - " << error;
    }
    std::cout << "\nПрограмма завершена";
    
    return 0;
}