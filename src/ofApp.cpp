
#include "ofApp.h"


//-------------------------------------------------------------
ofApp::~ofApp() {
    
}
//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0,0,0);
    
    myGrabber.listDevices();
    myGrabber.initGrabber(320,240);
    
    // width = myMovie.getWidth();
    // height = myMovie.getHeight();
    
    
    width = myGrabber.getWidth();
    height = myGrabber.getHeight();
    myTexture.allocate(width,height,GL_RGB);
    
    pixelout.allocate(width, height, 1);
    lastPixels.allocate(width, height,3);
    
    
//    myMovie.load(ofToDataPath("IMG_7088.mov"));
//    ofPixelFormat format = myMovie.getPixelFormat();
//   cout << ofToString(format) << endl;
    
    
//    if (myMovie.isLoaded()){
    if (myGrabber.isInitialized()){
            pixels = myGrabber.getPixels();
//            myMovie.play();
    }
    
   // cout << myMovie.getDuration() << endl;
    tileAvs.reserve(16);        // reserve the vector memory in advance, might be a bit quicker
    
    tileWidth = width / 4;
    tileHeight = height / 4;
    
    tileTexture.allocate(tileWidth, tileHeight, GL_RED);
    tile.allocate(tileWidth, tileHeight, 1);
    graphStep = width/16;
    
//    ofSoundStreamSetup(0,0,this, sampleRate, initialBufferSize, 4);/* Call this last ! */
}

//--------------------------------------------------------------
void ofApp::update(){
    
//    myMovie.update();
    myGrabber.update();

    if (myGrabber.isFrameNew()) {

        pixels = myGrabber.getPixels();           // If there's a new frame, get the pixels
        
        // frame difference on Red channel... motion detection from Mick Grierson's class code
        for (int i = 0; i < width; i++){
            for (int j = 0; j < height; j++) {
                pixelout[(j*width+i)+1]=abs((lastPixels[(j*width+i)*3+1])-(pixels[(j*width+i)*3+1]));
                lastPixels[(j*width+i)*3+1]=pixels[(j*width+i)*3+1];
            }
        }
    
 //  make 16 tiles from the first channel of the frame-diffed image
        
        for (int _row=0; _row<4;_row++){
            for (int _tileNum=0; _tileNum<4; _tileNum++){
                
                grid.push_back(makeTile(pixelout, _row, _tileNum) ); // push the tiles onto a deque
                
                if (grid.size()>16) {           // make a kind of circular buffer of tiles.
                    grid.pop_front();
                }
            }
        }
    
// get the average difference for each tile in the grid and store them in a vector
        
        tileCount = 0;
        
        for (auto &tile : grid){        // fancy for loop style
            tileAvs[tileCount] = getTileAverage(tile);
            tileCount++;
        }
    
        myTexture.allocate(pixelout);
        tileTexture.allocate(pixels);
    
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255, 255, 255,255);

    myTexture.draw(0, 0, width, height);                // draw the frame diff'd image
    tileTexture.draw(width, 0, width, height);          // draw the original input
    
   for (int i=0;i<16;i++){                              //graph the chnage across the individual tiles
                            ofSetColor(tileAvs[i]*10,180-tileAvs[i],50,220);
                            ofDrawRectangle(i*graphStep, ofGetHeight(), 10, filter1.lopass(-tileAvs[i]*5, 0.5));
   }
}

//--------------------------------------------------------------
float ofApp::getTileAverage(ofPixels &tilePix){  // takes in a reference to the pixel tiles to avoid copying data
 
    
    size_t arrayLength = tilePix.getWidth() * tilePix.getHeight() * tilePix.getNumChannels();
    
    float sum = 0;
    
    for (int i=0;i<arrayLength;i++){
        sum += tilePix[i];
    }
    
    return sum / arrayLength;       // just returns a value, so thats ok
}

//--------------------------------------------------------------
ofPixels& ofApp::makeTile(ofPixels &imagePixels, int rowNum, int tileNum){
    
    size_t numChannels = imagePixels.getNumChannels();      // in case a colour image comes in
    
    size_t arrayWidth = imagePixels.getWidth()*numChannels; // total width of the frame in array elements
    size_t rowStride = arrayWidth * tileHeight;             // the number of index positions to jump to get to the first                            pixel in the next row of tiles.
    
    
// Loop through the image, making a 16x16 grid of tiles
    for (int i=0; i<tileHeight; i++){
        
        int tileCol = i*tileWidth;
        
        for (int j=0; j<tileWidth; j++){
            
            tile[tileCol+j] = imagePixels[(i*arrayWidth + rowStride*rowNum) + ((j+tileWidth*tileNum)*numChannels)];
        }
    }
    
    return tile; // returns a reference to the tile, not copying the data
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key == 's') {
        
        myGrabber.videoSettings();
    } 
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
