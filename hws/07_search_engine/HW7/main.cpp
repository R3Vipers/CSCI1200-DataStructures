#include <iostream>
#include <fstream>
#include <regex>
#include <list>
#include "Document.h"

//erase specific characters from a string
std::string trim_string (std::string& tmpString, const std::string& trim) {
    size_t quotePos;
    // unfortunately, autograder will pass \" to the command line, and thus the double quote will be a part of the string.
    if( (quotePos = tmpString.find(trim)) != std::string::npos ){
        tmpString.erase(quotePos, trim.size()); // remove the double quote character at the found position; here number 1 as the second argument means erasing 1 character.
    }
    return tmpString;
}

//split off the last section from a URL to get the file path
std::string split_string (std::string &URL){
    std::string directory;
// suppose URL is "html_files/subdir1/subdir2/file7.html"
    size_t lastSlashPos = URL.find_last_of('/');
    if (lastSlashPos != std::string::npos) {
        // directory will <title>now be "html_files/subdir1/subdir2/"
        directory = URL.substr(0, lastSlashPos + 1);
    }
    return directory;
}

//find the title in the content of a document
std::string extractTitle (const std::string &content){
    unsigned int begin = content.find("<title>");
    unsigned int end = content.find("</title>");
    return content.substr(begin+7, end-(begin+7));
}

//find the description in the content of a document
std::string extractDescription (const std::string &content){
    unsigned int begin = content.find("content=\"");
    unsigned int temp = content.find("</head>");
    unsigned int end = content.rfind("\">", temp);
    return content.substr(begin+9, end-(begin+9));
}

//generate the snippet from the body of the content
std::string extractSnippet(const std::vector<std::string> &query, const std::string &content){
    unsigned int begin = content.find("<body>");
    int pos;
    int count = 0;
    int tempPose = 0;
    std::string snip;
    for(const std::string & i : query) {
        if ((pos = content.find(i, begin)) != std::string::npos) {
            int pos2 = content.rfind('.',pos);
            if(tempPose>pos2){
                continue;
            } else {
                tempPose = pos2;
            }
            while(isspace(content[pos2+=1]));
            snip = content.substr(pos2, 120);
            if(count == 0){
                return snip;
            }
        }
        count++;
    }
    return  snip;
}

//recursive functionality to find the number of keywords
void findDensity(const std::string& word, const std::string &content, int pos, int &total){
    if((content.find(word, pos) == std::string::npos) || pos ==  -1) return;
    findDensity(word, content, content.find(word, pos+word.size()), total);
    total++;
}
//driver function to find keyword density
unsigned int findDensity(const std::vector<std::string> &query, const std::string &content){
    if(query.empty() || content.empty()) return 0;
    int total = 0;
    //if there is one word just find the density of this word
    if(query.size()==1){
        findDensity(query[0],content,0, total);
        return total-query.size();
    } else {
        // else iterate through all other keywords
        for(int i = 1; i< query.size(); i++){
            int current = total;
            findDensity(query[i],content, 0, total);
            if(total == current) return 0;
        }
        return total-(query.size()-1);
    }
}

// function to parse an HTML file and extract links to local files
std::list<std::string> extractLinksFromHTML(const std::string& fileContent, std::string& seed) {
    std::list<std::string> links;
    // regular expression to match href attributes in anchor tags
    std::regex linkRegex("<a\\s+[^>]*href\\s*=\\s*['\"]([^'\"]+)['\"][^>]*>");
    std::smatch match;

    // search for links in the HTML content
    std::string::const_iterator start = fileContent.cbegin();
    while (std::regex_search(start, fileContent.cend(), match, linkRegex)) {
        if (match.size() > 1) {
            std::string link = match[1].str();
            links.push_back(split_string(seed)+trim_string(link, "../"));
        }
        start = match.suffix().first;
    }

    return links;
}

//extract the content from a given html file
std::string file_to_string(const std::string& filePath){
    std::ifstream fileStream(filePath);
    if (fileStream.is_open()) {
        std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
    // suppose filePath is the string "html_files/subdir1/file3.html", then at this point, the string fileContent will be the full content of this file file3.html.
    // do something with fileContent
        return fileContent;
    } else {
        return "";
    }
}

//recursive crawler function to find all documents
void crawler(std::map<std::string, Document>& files, std::string& seed, const std::vector<std::string> &query) {
    std::string content = file_to_string(seed);
    std::list<std::string> links;
    std::string title;
    std::string description;
    std::string snippet;
    unsigned int density = 0;
    if(!content.empty()){
        //all information is extracted from the document once it is found
        title = extractTitle(content);
        description = extractDescription(content);
        snippet = extractSnippet(query, content);
        links = extractLinksFromHTML(content, seed);
        if (!snippet.empty()) density = findDensity(query, content);
        //a new document object is created and put into a map with the key of the URL
        Document document(seed, title, description, snippet, links, density, content.size());
        files.insert(std::make_pair(seed, document));
    }
    //crawler then crawls through eah of the other links
    for( std::string link : links){
        if(files.find(link)==files.end()){
            crawler(files,link, query);
        }
    }
}


std::vector<std::string> query_type(std::vector<std::string> &input_type){
    std::vector<std::string> output;
    std::vector<std::string> keywords;
    bool phrase = false;
    if(input_type[0].find('"') != std::string::npos ){
        input_type[0] = input_type[0].erase(0, 1);
        input_type[input_type.size()-1] = input_type[input_type.size()-1].erase(input_type[input_type.size()-1].find('"'), 1);
        phrase = true;
    }
    std::string tmp;
    for(std::string &words: input_type){
        tmp += words;
        tmp += " ";
    }
    if(phrase) input_type.clear();
    input_type.insert(input_type.begin(), tmp);
    return input_type;
}

//assigns a rank to each document
void rank (std::map<std::string, Document> &files) {
    double total_size = 0;
    double total_density = 0;
    double bscore;
    double dscore;
    double rank;
    //goes through each document sums the total length and density
    for(const std::pair<const std::basic_string<char>, Document>& f : files){
        total_size += f.second.getSize();
        total_density += f.second.getDensity();
    }
    //goes through each document sums the total length backscore for a document
    for(std::pair<const std::basic_string<char>, Document>& f1 : files){
        bscore = 0.0;
        for(const std::pair<const std::basic_string<char>, Document>& f2 : files){
            for(std::string& l: f2.second.get_outGoingLinks())
                //check to see if a link is the same as the current document
                if(l==f1.second.get_URL()){
                    bscore+=f2.second.getBackScore();
                }
        }
        dscore = f1.second.getDensity()/(f1.second.getSize()*(total_density/total_size));
        rank = (0.5*dscore) + (0.5*bscore);
        f1.second.setRank(rank);
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::string> test;
    //read in all of the arguments
    for(int i = 3; i<argc; i++) {
        std::string temp = argv[i];
        test.push_back(temp);
    }
    test = query_type(test);
    std::ofstream fout(argv[2], std::ios::app);
    //if we get more than 6 argument, or more than three words, say that there ae no matches
    if(argc > 6) {
        fout << "Your search - " << test[0] << " - did not match any documents.";
        return 0;
    }

    std::map<std::string, Document> files;
    std::string seed = argv[1];
    //start the crawler
    crawler(files, seed, test);
    rank(files);
    std::vector<Document> sorted_files;
    //read the found documents into a vector so that they can be sorted by their ranking
    for(std::pair <std::string, Document> f: files){
        sorted_files.push_back(f.second);
    }
    int matches = false;
    std::sort(sorted_files.begin(), sorted_files.end());
    //check to make sure that at least one document has a snippet
    for(const Document& file : sorted_files) {
        if (file.get_Snippet().empty()) {
            continue;
        }
        matches = true;
        break;
    }
    //print out the found matches in order of page ranking
    if(matches)fout<<"Matching documents: "<< std::endl<<std::endl;
    for(const Document& file : sorted_files){
        if(file.get_Snippet().empty()){
            continue;
        }
        matches = true;
        fout<<file;
        fout<<std::endl;
    }
    //if no matches were found print no matches found
    if(!matches) fout<<"Your search - "<<test[0]<< "- did not match any documents.";
    return 0;
}
