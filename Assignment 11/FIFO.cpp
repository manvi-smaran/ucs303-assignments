int fifo(vector<int> refs, int framesCount) {
    vector<int> frames(framesCount, -1);   // memory frames
    int pageFaults = 0;
    int index = 0;  // points to next frame to replace (queue logic)

    cout << "\n--- FIFO Simulation ---\n";
    for (int page : refs) {
        bool hit = false;

        // Check if page already exists in frame
        for (int f : frames) if (f == page) hit = true;

        if (!hit) {  // if page fault
            frames[index] = page;          // replace in FIFO order
            index = (index + 1) % framesCount;
            pageFaults++;
        }

        printFrames(frames);
    }
    return pageFaults;
}