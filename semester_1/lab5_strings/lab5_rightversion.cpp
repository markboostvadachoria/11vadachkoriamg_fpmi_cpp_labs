#include<iostream>
#include<string>
#include<algorithm>
#include<cctype>

const int MAX_WORD_SIZE = 8;

struct MaxNumber
{
    std::string::iterator it;
    int max_number;
    size_t word_size;

};

bool stringIsNumber(std::string& s)
{
    //std::cout << s << '\n';
    if (s[0] == '0' && s.size() > 1)
        return false;
    if (s.empty())
        return false;
    for (auto i : s)
        if (!isdigit(static_cast<unsigned char>(i)))
            return false;
    return true;
}

void findPreMaxNumberString(std::string& s, const char& DELIMITER_CHAR, MaxNumber& maxNumber, MaxNumber& preMaxNumber)
{
    std::string::iterator start_w = s.begin();
    std::string::iterator end_w = s.begin();

    while (start_w != s.end())
    {
        
        end_w = std::find(start_w, s.end(), DELIMITER_CHAR);
        std::string word(start_w, end_w);
        if (stringIsNumber(word)){
            if (word.size() >= MAX_WORD_SIZE)
                throw "Error: A big number"; 
            int tmp_word = stoi(word);
            if (tmp_word >= maxNumber.max_number){
                preMaxNumber = maxNumber;
                maxNumber.max_number = tmp_word;
                maxNumber.it = start_w;
                maxNumber.word_size = word.size();
            }
        }
        if (end_w == s.end())
            break;

        start_w = std::find_if_not(end_w, s.end(), [DELIMITER_CHAR](char& c) -> bool{return c == DELIMITER_CHAR;});
        
    }

} 

void moveMaxWord(std::string& s, MaxNumber &maxNumber, const char& DELIMETER_CHAR)
{
    std::string new_string{""};
    new_string += std::string(maxNumber.it, maxNumber.it + maxNumber.word_size);

    s.erase(maxNumber.it, maxNumber.it + maxNumber.word_size);
    
    if (s[0] != DELIMETER_CHAR)
        new_string += DELIMETER_CHAR;
    new_string += s;
    s = new_string;
    

}

int main()
{
    try{
        const char DELIMITER_CHAR = ' ';
        std::string s;
        std::cout << "Input a string: ";
        std::getline(std::cin, s);
        if (s.empty())
            throw "Enter something!";
        MaxNumber preMaxNum{s.begin(), -1, 0}, maxNum{s.begin(), -1, 0};
        findPreMaxNumberString(s, DELIMITER_CHAR, maxNum, preMaxNum);
        if (maxNum.max_number == -1)
            throw "A number not find";
        //std::cout << static_cast<size_t>(n.it - s.begin()) << ' ' << n.max_number << ' ' << n.word_size;
        moveMaxWord(s, preMaxNum.max_number == maxNum.max_number ? preMaxNum : maxNum, DELIMITER_CHAR);
        preMaxNum.it = {};
        maxNum.it = {};
        
        std::cout << "New string: ";
    }
    catch(const char* error_message)
    {   
        std::cout << error_message;
        return 1;
    }

    return 0;

}