#include "Analyzer.h"

void Analyzer::startAnalyzing(const std::string &pathName, const unsigned &countThread)
{
    it_fspath = std::filesystem::directory_iterator(pathName);
    if (countThread == 0)
        analyzingOneThread();
    else
        analyzingMultithread(countThread);
}

void Analyzer::analyzingOneFile(const std::filesystem::path &fileName)
{
    std::string line;
    std::ifstream file(fileName);
    if (file.is_open())
    {
        countProcFiles++;
        if (fileName.extension() == ".js")
            processingJSFile(file);
        else
            processingANYFileOtherJS(file);
    }
    else
    {
        countErrors++;
    }
}

void Analyzer::processingJSFile(std::ifstream &file)
{
    std::string line;
    while (getline(file, line))
    {
        if (line == JS_suspicious)
        {
            std::cout << "JS_suspicious detected\n";
            countJSSus++;
            break; //по условию в 1 файле 1 тип угрозы
        }
    }
}

void Analyzer::processingANYFileOtherJS(std::ifstream &file)
{
    std::string line;
    while (getline(file, line))
    {
        if (line == Unix_suspicious)
        {
            std::cout << "Unix_suspicious detected\n";
            countUNIXSus++;
            break;
        }
        else if (line == macOS_suspicious)
        {
            std::cout << "macOS_suspicious detected\n";
            countMACSus++;
            break;
        }
    }
}
void Analyzer::analyzingMultithread(const unsigned &countThread)
{
    std::vector<std::thread> threadPool;

    for (size_t i = 0; i < countThread; ++i)
        threadPool.push_back(std::thread(&Analyzer::analyzingOneThread, this));

    for (size_t i = 0; i < countThread; ++i)
        threadPool[i].join();
}

void Analyzer::analyzingOneThread()
{
    while (true)
    {
        std::filesystem::path nextFile = getNextFileForAnalyzing();
        if (nextFile.empty())
            break;
        analyzingOneFile(nextFile);
    }
}

std::filesystem::path Analyzer::getNextFileForAnalyzing()
{
    std::scoped_lock<std::mutex> lock(mtx);
    while (it_fspath != it_end)
    {
        std::filesystem::path nextFile = it_fspath->path();
        it_fspath++;
        return nextFile;
    }
    return std::filesystem::path();
}

