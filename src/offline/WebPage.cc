#include "WebPage.h"
#include "SplitToolCppJieba.h"

WebPage::WebPage(string &page)
    : _format_xml(page)
{
}

void WebPage::unrepeatedWebPageLibHelper(Simhasher *p_simhasher)
{
    extractWebPage();
    generateFigurePrint(p_simhasher);
}

void WebPage::invertIndexLibHelper(SplitTool *p_split_tool)
{

    extractWebPage();
    generateWordFrequenceMap(p_split_tool);
}

int WebPage::getID()
{
    return _id;
}

string WebPage::getTitle()
{
    return _title;
}

string WebPage::getURL()
{
    return _url;
}

string WebPage::getContent()
{
    return _content;
}

map<string, int> &WebPage::getWordFrequenceMap()
{
    return _word_frequence;
}

uint64_t WebPage::getFigurePrint()
{
    return _figure_print;
}

void WebPage::extractWebPage()
{
   XMLDocument doc;
    doc.Parse(_format_xml.c_str());

    XMLElement * page_elem = doc.FirstChildElement("webpage");

    if (page_elem == nullptr)
    {
        // 如果解析失败，尝试手动处理
        size_t content_start = _format_xml.find("<content>");
        size_t content_end = _format_xml.find("</content>", content_start);

        if (content_start != string::npos && content_end != string::npos)
        {
            // 提取 <content> 和 </content> 之间的内容
            string content = _format_xml.substr(content_start, content_end - content_start + 9);

            // 去掉 <content> 和 </content> 标签
            content = content.substr(9, content.size() - 18);

            // 替换原始内容
            _format_xml.replace(content_start, content_end - content_start + 9, content);

            // 重新解析
            doc.Parse(_format_xml.c_str());
            page_elem = doc.FirstChildElement("webpage");
        }
        else
        {
            // 处理无法解析的情况
            std::cerr << "\t[ERROR] : Invalid XML format\n";
            return;
        }
    }

    if (page_elem)
    {
        XMLElement * docid_elem   = page_elem->FirstChildElement("docid");
        XMLElement * title_elem   = page_elem->FirstChildElement("title");
        XMLElement * link_elem    = page_elem->FirstChildElement("link");
        XMLElement * content_elem = page_elem->FirstChildElement("content");

        if (docid_elem && title_elem && link_elem && content_elem)
        {
            _id      = std::stoi(docid_elem->GetText());
            _title   = title_elem->GetText();
            _url     = link_elem->GetText();
            _content = content_elem->GetText();
        }
        else
        {
            std::cerr << "\t[ERROR] : Missing elements in XML\n";
        }
    }
}

void WebPage::generateWordFrequenceMap(SplitTool *p_split_tool)
{
    string page_content(_content);

    extractChineseWord(page_content);

    vector<string> split_res = p_split_tool->cut(page_content);

    for (auto &word : split_res)
    {
        if (!isStopWord(word))
        {
            if (word.empty())
                continue;

            _word_frequence[word]++;
        }
    }
}

void WebPage::generateFigurePrint(Simhasher *p_simhasher)
{
    p_simhasher->make(_content, 5, _figure_print);
}

bool WebPage::isStopWord(string &word)
{
    auto stop_set = Configuration::getInstance()->getStopWordSet();

    return stop_set.find(word) != stop_set.end();
}

void WebPage::extractChineseWord(string &word)
{
    for (size_t i = 0; i < word.size();)
    {
        size_t bytes = nBytesCode(word[i]);

        if (!isChinese(word[i]))
        {
            word.erase(i, bytes);
            continue;
        }

        i += bytes;
    }
}

bool WebPage::isChinese(char ch)
{
    return 0x80 & ch;
}

size_t WebPage::nBytesCode(char ch)
{
    if (ch & 0x80)
    {
        int bytes = 1;

        for (int i = 0; i != 6; i++)
        {
            if (ch & (1 << (6 - i)))
            {
                bytes++;
            }
            else
            {
                break;
            }
        }

        return bytes;
    }

    return 1;
}
