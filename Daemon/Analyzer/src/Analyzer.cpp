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
            processingJSFile(file, fileName);
        else
            processingANYFileOtherJS(file, fileName);
        file.close();
    }
    else
    {
        countErrors++;
    }
}

AnalyzInformation Analyzer::getResultAnalyz()
{
    AnalyzInformation result{
        countProcFiles,
        countUNIXSus,
        countMACSus,
        countJSSus,
        countErrors};
    refreshCounters();
    return result;
}

void Analyzer::processingJSFile(std::ifstream &file, const std::string &filename)
{
    std::string line;
    while (getline(file, line))
    {
        if (line == JS_suspicious)
        {
            log_info_detected("JS_suspicious detected in %s", filename.c_str());
            countJSSus++;
            break; //по условию в 1 файле 1 тип угрозы
        }
    }
}

void Analyzer::processingANYFileOtherJS(std::ifstream &file, const std::string &filename)
{
    std::string line;
    while (getline(file, line))
    {
        if (line == Unix_suspicious)
        {
            log_info_detected("UNIX_suspicious detected in %s", filename.c_str());
            countUNIXSus++;
            break;
        }
        else if (line == macOS_suspicious)
        {
            log_info_detected("macOS_suspicious detected in %s", filename.c_str());
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

void Analyzer::refreshCounters()
{
    countProcFiles = 0;
    countUNIXSus = 0;
    countMACSus = 0;
    countJSSus = 0;
    countErrors = 0;
}