#include "tn_main.h"
#include <unistd.h>
string TextNorm(string& sentence) {
    if (sentence.empty())
        return "";
    vector<string> words_list_0 = Tokenize(sentence);
    string sentence_1 = "";
    for (auto word: words_list_0) {
        string word_1 = RemovePuncs(word);
        word_1 = SplitRuler(word_1);
        word_1 = Mail2Eng(word_1);
        word_1 = ProcessGreek(word_1);
        word_1 = Signal2Eng(word_1);
        sentence_1 += trim(word_1) + " ";
    }
    vector<string> words_list_1 = SplitString(trim(sentence_1), " ");
    string sentence_2 = "";
    for (auto word: words_list_1) {
        string word_2;
        if (IsRuler(word))
            word_2 = Ruler2Eng(word);
        else if (IsDollar(word))
            word_2 = ProcessDollar(word);
        else if (IsTime(word))
            word_2 = ProcessTime(word);
        else if (IsDate(word))
            word_2 = ProcessDate(word);
        else if (IsDigit(word) || IsDecimal(word) || IsDigitWithComma(word)
                || IsFraction(word) || IsOrdinal(word) || IsPercent(word))
            word_2 = ConvertNum2Eng(word);
        else
            word_2 = word;
        sentence_2 += trim(word_2)  + " ";
    }
    if (!sentence_2.empty())
        return sentence_2;
    return sentence;
}


int main(int argc, char* argv[]) {
    string input_file;
    string output_file;
    char ch;
    while ((ch = getopt(argc, argv, "i:o:")) != EOF) {
        switch (ch) {
            case 'i' : input_file = optarg;
            case 'o' : output_file = optarg;
            default: break;
        }
    }
    ifstream fin(input_file);
    ofstream fout(output_file);
    string input, id, text;
    int i = 0;
    while(getline(fin, text)) {
        i += 1;
        cout << i << std::endl;
        text = TextNorm(text);
        fout << text << std::endl;
    }
    fin.close();
    fout.close();
    return 0;
}
