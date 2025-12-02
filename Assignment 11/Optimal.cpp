int optimal(vector<int> refs, int framesCount) {
    vector<int> frames(framesCount, -1);
    int pageFaults = 0;

    cout << "\n--- OPTIMAL Simulation ---\n";
    for (int i = 0; i < refs.size(); i++) {
        int page = refs[i];
        bool hit = false;

        for (int f : frames) if (f == page) hit = true;

        if (!hit) {  // page fault
            int replaceIndex = -1, farthest = -1;

            // Find page used farthest in the future
            for (int j = 0; j < framesCount; j++) {
                int nextUse = -1;
                for (int k = i + 1; k < refs.size(); k++)
                    if (frames[j] == refs[k]) { nextUse = k; break; }

                // If never used again: best option to replace
                if (nextUse == -1) {
                    replaceIndex = j;
                    break;
                }

                // Track farthest future usage
                if (nextUse > farthest) {
                    farthest = nextUse;
                    replaceIndex = j;
                }
            }

            frames[replaceIndex] = page;
            pageFaults++;
        }

        printFrames(frames);
    }
    return pageFaults;
}