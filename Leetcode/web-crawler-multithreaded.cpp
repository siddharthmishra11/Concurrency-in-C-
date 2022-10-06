/**
 * // This is the HtmlParser's API interface.
 * // You should not implement it, or speculate about its implementation
 * class HtmlParser {
 *   public:
 *     vector<string> getUrls(string url);
 * };
 */
class Solution {
    unordered_set<string> vis_urls; 
    condition_variable cv;
    mutex m;
    queue<string> blocking_queue;
    bool no_left;
    int curr_thread_exec;
    string startUrl;
public:
    bool sameWeb(string s){
        s = s.substr(7,s.size()-7);
        string starturl = startUrl.substr(7,startUrl.size()-7);
        int idx = s.find("/");
        int idx2 = starturl.find("/");
        if(idx==string::npos)
            idx = s.size();
        if(idx2==string::npos)
            idx2 = starturl.size();
        return s.substr(0,idx)==starturl.substr(0,idx2);
    }
    void searching_url_bfs(HtmlParser& htmlParser){
    while(true){
          unique_lock<mutex> ul(m);
        cv.wait(ul,[this]{return no_left||blocking_queue.size()>0;});
        if(no_left)return;
        curr_thread_exec++;
        string url = blocking_queue.front();
        blocking_queue.pop();
        ul.unlock();
        vector<string> url_crawl = htmlParser.getUrls(url);
        ul.lock();
        for(string urls:url_crawl){
                if(vis_urls.find(urls)==vis_urls.end() && sameWeb(urls)){
                    blocking_queue.push(urls);
                    vis_urls.insert(urls);
                }
        }
        curr_thread_exec--;
        if(curr_thread_exec==0 && blocking_queue.size()==0)no_left = true;
        cv.notify_all();
    }
    }
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        this->startUrl = startUrl;
        blocking_queue.push(startUrl);
        vis_urls.insert(startUrl);
        no_left = false;
        curr_thread_exec = 0;
        int num_threads = std::thread::hardware_concurrency();
       
        vector<thread> worker_thread;
        for(int i=0;i<num_threads;i++)           worker_thread.emplace_back( &Solution::searching_url_bfs,this,ref(htmlParser));
       
    
            for(thread& t:worker_thread)
                t.join();
          
        return vector<string>(vis_urls.begin(),vis_urls.end());
    }
};