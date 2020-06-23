#include "tn_tokenizer.h"

vector<string> Tokenize(string& sentence) {
   vector<string> words_list = SplitString(sentence, " ");
   return words_list;
}

