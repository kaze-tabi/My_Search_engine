#include "SplitToolCppJieba.h"
#include <iostream>
#include <vector>
#include <string>

const char *dict_path = "data/dict/jieba.dict.utf8";
const char *model_path = "data/dict/hmm_model.utf8";
const char *user_dict_path = "data/dict/user.dict.utf8";
const char *idf_path = "data/dict/idf.utf8";
const char *stop_word_path = "data/dict/stop_words.utf8";

SplitToolCppJieba::SplitToolCppJieba()
    : _jieba(dict_path, model_path, user_dict_path, idf_path, stop_word_path) // 初始化Jieba类对象
{
}

vector<string> SplitToolCppJieba::cut(const string &sentence)
{
    vector<string> words;
    _jieba.Cut(sentence, words);
    return words;
}