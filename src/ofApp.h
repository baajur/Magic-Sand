#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxKinectProjectorToolkit.h"

#include "ColorMap.h"
#include "FrameFilter.h"
#include "KinectGrabber.h"
#include "vehicle.h"
#include "SurfaceRenderer.h"
#include "Utils.h"

using namespace cv;
using namespace states;


class ofApp : public ofBaseApp{

public:

    void setup();
    void update();
    void draw();
    void drawProjWindow(ofEventArgs& args);
    void drawChessboard(int x, int y, int chessboardSize);
    void drawTestingPoint(ofVec2f projectedPoint);
    void drawSandbox();
    void prepareContourLines();
    void addPointPair();
    void setHeightMapRange(GLsizei newHeightMapSize,GLfloat newMinElevation,GLfloat newMaxElevation);

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    shared_ptr<ofAppBaseWindow> projWindow;

private:
    //kinect interfaces and calibration
    KinectGrabber               kinectgrabber;
    ofxKinectProjectorToolkit   kpt;

    //Images and cv matrixes
    ofxCvFloatImage             FilteredDepthImage;
    ofxCvColorImage             kinectColorImage;
    cv::Mat                     cvRgbImage;

    // Calibration variables
    vector<ofVec2f>             currentProjectorPoints;
    vector<cv::Point2f>         cvPoints;
    vector<ofVec3f>             pairsKinect;
    vector<ofVec2f>             pairsProjector;
    
    // Conversion matrices
    ofMatrix4x4                 kinectProjMatrix;
    ofMatrix4x4                 kinectWorldMatrix;

    // Gui variables
    string                      resultMessage;
    ofColor                     resultMessageColor;
    ofVec2f                     testPoint;
    bool saved;
    bool loaded;
    bool calibrated;

    // States variables
    General_state generalState;
    Calibration_state calibrationState;
    ROI_calibration_state ROICalibrationState;

    // ROI calibration variables
    ofxCvGrayscaleImage thresholdedImage;
    ofxCvContourFinder        contourFinder;
    float threshold;
    ofPolyline large;
    ofRectangle                 kinectROI;

    // Mesh
    ofMesh mesh;
    int meshwidth;          //Mesh size
    int meshheight;

    // Shaders
    ofShader elevationShader;
    ofShader heightMapShader;

    // FBos
    ofFbo fboProjWindow;
    ofFbo   contourLineFramebufferObject;

    // Base plane
    ofVec3f basePlaneNormal;
    ofVec3f basePlaneOffset;
    ofVec4f basePlaneEq; // Base plane equation in GLSL-compatible format

    // Colormap and heightmap variables
    ColorMap    heightMap;
	GLfloat heightMapScale,heightMapOffset; // Scale and offset values to convert from elevation to height color map texture coordinates

    double gradFieldresolution;
    
    float farclip, nearclip;
    float elevationMin, elevationMax;
    int   chessboardSize;
    int   chessboardX;
    int   chessboardY;
    int projResX;
    int projResY;
    int kinectResX;
    int kinectResY;
    bool drawContourLines; // Flag if topographic contour lines are enabled
	float contourLineFactor; // Inverse elevation distance between adjacent topographic contour lines

};