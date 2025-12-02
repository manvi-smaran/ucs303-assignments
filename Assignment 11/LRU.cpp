int lru(vector<int> refs, int framesCount) {
    vector<int> frames(framesCount, -1);
    vector<int> lastUsed(framesCount, 0);
    int pageFaults = 0, time = 0;

    cout << "\n--- LRU Simulation ---\n";
    for (int page : refs) {
        time++;
        bool hit = false;

        // Check if page already exists in frame, update usage time
        for(int i = 0; i < framesCount; i++){
            if(frames[i] == page){
                hit = true;
                lastUsed[i] = time;
            }
        }

        if (!hit) {  // if page fault
            int replaceIndex = 0;
            for (int i = 0; i < framesCount; i++) {
                if (lastUsed[i] < lastUsed[replaceIndex]) replaceIndex = i;
            }
            frames[replaceIndex] = page;
            lastUsed[replaceIndex] = time;
            pageFaults++;
        }

        printFrames(frames);
    }

    return pageFaults;
}