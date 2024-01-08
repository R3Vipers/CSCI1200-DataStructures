#include <iostream>
#include <regex>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "Trends.h"

using namespace std;
//file output function/class
class Output {
public:
    explicit Output(const string& file_name) : file(file_name) {

    }
    void out (const std::string& txt){

        std::ofstream fout(file, std::ios::app);
        if (fout.is_open())
        {
            fout << txt;
        }
    }
private:
    string file;
};

//function to get information from a string
string extract_data_string (const string& line, const string& type){
    unsigned int start = line.find(type)+type.size();
    unsigned int end = line.find('"', start);
    return line.substr(start,end-start);
}
//function to get ints from a string
int extract_data_int (const string& line, const string& type){
    unsigned int start = line.find(type)+type.size();
    unsigned int end = line.find(',', start);
    return stoi(line.substr(start,end-start));
}
//given hashtag extract function
vector<string> extract_hash_tag(string text) {
    vector<string> hash;
    // the text of the post is given as a std::string, extract hashtags from the text.

    // define a regular expression to match hashtags
    std::regex hashtagRegex("#([\\w\\u0080-\\uFFFF]+)");

    // create an iterator for matching
    std::sregex_iterator hashtagIterator(text.begin(), text.end(), hashtagRegex);
    std::sregex_iterator endIterator;

    // iterate over the matches and extract the hashtags
    while (hashtagIterator != endIterator) {
        std::smatch match = *hashtagIterator;
        std::string hashtag = match.str(1);  // extract the first capturing group
        // this line will print each hash tag
        // if you want to do more with each hash tag, do it here. for example, store all hash tags in your container.
        //std::cout << "Hashtag: " << hashtag << std::endl;
        hash.push_back(hashtag);
        ++hashtagIterator;
    }
    return hash;
}

int main(int argc, char* argv[]) {
    // assume inputFile is a std::string, containing the file name of the input file.
    //assigning arguments to variables
    Output output(argv[2]);
    string input = argv[1];
    string output_type = argv[3];
    std::ifstream jsonFile(input);
    if (!jsonFile.is_open()) {
        std::cerr << "Failed to open the JSON file." << std::endl;
        exit(1);
    }
    //declaring containers
    std::string json_content;
    std::string line;
    unordered_map<string, Hashtag> hashTags;
    unordered_map<string, Sound> sounds;
    pair<unordered_map<string, Sound>::iterator, bool> update_s;
    pair<unordered_map<string, Hashtag>::iterator, bool> update_h;
    pair<unordered_map<string, priority_queue<Trend, vector<Trend>, CompareInfo>>::iterator, bool> update_i;
    unordered_map<string, priority_queue<Trend, vector<Trend>, CompareInfo>> info;
    priority_queue<Trend, vector<Trend>, CompareInfo> temp;
    priority_queue<Trend, vector<Trend>, CompareInfo> temp2;
    vector<string> Tags;
    //string for storing information
    string cover_url;
    string web_url;
    string name;
    string author;
    string music_id;
    //hashtag logic
    if(output_type == "hashtag") {
        while (std::getline(jsonFile, line)) {
            //use sub strings to get used information from each line
            long unsigned int views = extract_data_int(line, R"("playCount": )");
            cover_url = extract_data_string(line, R"("coverUrl": ")");
            web_url = extract_data_string(line, R"("webVideoUrl": ")");
            Tags = extract_hash_tag(line);
            if(!Tags.empty()) {
                //fo each hashtag create a new tag and read it into a map
                for (string tag: Tags) {
                    Hashtag newTag(tag, views);
                    update_h = hashTags.insert(make_pair(tag, newTag));
                    if (!update_h.second) {
                        update_h.first->second.increaseViews(views);
                        update_h.first->second.increaseUses();
                    }
                    //create an associated trend for each hashtag
                    //used for top three urls
                    Trend trend(tag, views, cover_url, web_url);
                    update_i = info.insert(make_pair(tag, temp));
                    update_i.first->second.emplace(trend);
                }
            }
        }
    //sound logic
    } else if (output_type == "sound"){
        while (std::getline(jsonFile, line)) {
            //extract information from each line
            long unsigned int views = extract_data_int(line, R"("playCount": )");
            music_id = extract_data_string(line, R"("musicId": ")");
            author = extract_data_string(line, R"("musicAuthor": ")");
            name = extract_data_string(line, R"("musicName": ")");
            cover_url = extract_data_string(line, R"("coverUrl": ")");
            web_url = extract_data_string(line, R"("webVideoUrl": ")");
            //create a new sound and add it to a map
            Sound sound (music_id, views, name, author);
            update_s = sounds.insert(make_pair(music_id, sound));
            if(!update_s.second) {
                update_s.first->second.increaseViews(views);
                update_s.first->second.increaseUses();
            }
            //create an associated trend for each sound
            //used for top three urls
            Trend trend (music_id, views, cover_url,web_url);
            update_i = info.insert(make_pair(music_id, temp2));
            update_i.first->second.emplace(trend);

        }
    } else {
        return 0;
    }

    // don't need this json file anymore, as the content is read into json_content.
    jsonFile.close();
    //declaring more containers
    priority_queue<pair<string, Hashtag>, vector<pair<string, Hashtag>>, Comparehash> trend;
    priority_queue<pair<string, Sound>, vector<pair<string, Sound>>, Comparesound> trend2;
    unordered_map<string, Hashtag>::const_iterator it;
    unordered_map<string, Sound>::const_iterator it2;
    //hashtag printing for top ten
    if (output_type == "hashtag") {
        //copy contents of map into priority queue
        for (it = hashTags.begin(); it != hashTags.end(); ++it) {
            trend.emplace(it->first, it->second);
        }
        int count = 0;
        output.out("trending hashtags:\n"
              "\n");
        //formatted output
        while(!trend.empty() and count < 10) {
            output.out("========================\n");
            output.out("#"+trend.top().first +"\n");
            output.out("used "+ to_string(trend.top().second.getUsed()) +" times\n");
            output.out(to_string(trend.top().second.getViews()) + " views\n");
            output.out("\n");
            int count2 = 3;
            //print out the top three urls
            while (count2 > 0 && !info.find(trend.top().first)->second.empty()) {
                //use try catch when the number of urls is less than three and catch segmentation fault
                try {
                    output.out("cover url: " + info.find(trend.top().first)->second.top().getCover() + "\n");
                    output.out("web video url: " + info.find(trend.top().first)->second.top().getWeb() + "\n");
                    info.find(trend.top().first)->second.pop();
                    count2--;
                } catch (...) {
                    cerr<<"segmentation fault caught" << endl;
                }

            }

            output.out("========================\n");
            trend.pop();
            count++;
        }
    //sound printing for top ten
    } else if (output_type == "sound") {
        //copy contents of map into priority queue
        for (it2 = sounds.begin(); it2 != sounds.end(); ++it2) {
            trend2.emplace(it2->first, it2->second);
        }
        int count = 0;
        //formatted output
        output.out("trending sounds:\n"
              "\n");
        //formatted output
        while(!trend2.empty() and count < 10) {
            output.out("========================\n");
            output.out(trend2.top().second.getTitle()+"\n");
            output.out(to_string(trend2.top().second.getViews())+" views\n");
            output.out(trend2.top().second.getAuthor()+"\n");
            output.out("music id: "+ trend2.top().first+"\n");
            output.out("\n");
            int count2 = 3;
            //print out the top three urls
            while (count2 > 0 && !info.find(trend2.top().first)->second.empty()) {
                //use try catch when the number of urls is less than three and catch segmentation fault
                try {
                    output.out("cover url: "+info.find(trend2.top().first)->second.top().getCover()+"\n");
                    output.out("web video url: "+info.find(trend2.top().first)->second.top().getWeb()+"\n");
                    info.find(trend2.top().first)->second.pop();
                    count2--;
                } catch (...) {
                    cerr<<"segmentation fault caught" << endl;
                }

            }

            output.out("========================\n");
            trend2.pop();
            count++;
        }
    }

    return 0;
}
