#pragma pack(16)


#include "ofMain.h"
#include "ofxMaxim.h"

class ofApp : public ofBaseApp{
    
public:
    ~ofApp();/* destructor is very useful */
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    float     getTileAverage(ofPixels& tilePix);            // returns the average difference in that tile
    ofPixels& makeTile(ofPixels&, int _row, int _tile);     // divides the image into tiles

    int		initialBufferSize; /* buffer size */
    int		sampleRate;
    
    ofVideoPlayer 		myMovie;
    ofVideoGrabber		myGrabber;
    
    ofPixels pixels;
    ofPixels tile;
    ofPixels pixelout, lastPixels, blockpix;
    
    ofTexture myTexture, tileTexture;
    
    vector<float> tileAvs;
    deque<ofPixels> grid, frameDiffs;
    
    int width, height, tileHeight, tileWidth, tileCount, graphStep;

    maxiFilter filter1;

};
