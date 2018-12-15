#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);

	ofEnableBlendMode(OF_BLENDMODE_ADD);

	ofSetFrameRate(60);

	width = ofGetWidth();
	height = ofGetHeight();

	step = 4;

	eta, theta, iota = 0;
	
	image.load("img.jpg");
	image.resize(width, height);

	mesh.setMode(OF_PRIMITIVE_TRIANGLES);
	mesh.enableColors();
	mesh.enableIndices();

	for (int y = 0; y < height; y += step) {
		for (int x = 0; x < width; x += step) {
			ofColor c = image.getColor(x, y);
			float z = c.getLightness();
			mesh.addVertex(ofPoint(x, y, ofMap(z, 0, 255, -100, 100)));
			mesh.addColor(ofColor(c, ofMap(z, 0, 255, 0, 30)));
			offsets.push_back(ofVec3f(ofRandom(0, 100000), ofRandom(0, 100000), ofRandom(0, 100000)));
		}
	}

	for (int y = 0; y < (height / step) - 1; y++ ) {
		for (int x = 0; x < (width / step) - 1; x++ ) {
			mesh.addIndex(x + y * (width / step));
			mesh.addIndex((x + 1) + y * (width / step));
			mesh.addIndex(x + (y + 1) * (width / step));
			mesh.addIndex((x + 1) + y * (width / step));
			mesh.addIndex((x + 1) + (y + 1) * (width / step));
			mesh.addIndex(x + (y + 1) * (width / step));
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	int numVerts = mesh.getNumVertices();
	for (int i = 0; i<numVerts; ++i) {
		ofVec3f vert = mesh.getVertex(i);

		float time = ofGetElapsedTimef();
		float timeScale = 0.5;
		float displacementScale = 0.5;
		ofVec3f timeOffsets = offsets[i];

		vert.x += (ofSignedNoise(time*timeScale + timeOffsets.x)) * displacementScale;
		vert.y += (ofSignedNoise(time*timeScale + timeOffsets.y)) * displacementScale;
		vert.z += (ofSignedNoise(time*timeScale + timeOffsets.z)) * displacementScale;
		mesh.setVertex(i, vert);
	}

	eta += 0.01;
	theta += 0.02;
	iota += 0.03;
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofColor centerColor = ofColor(60, 0, 40);
	ofColor edgeColor(0, 0, 20);
	ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
	
	cam.begin();
		ofRotateXDeg(eta);
		ofRotateYDeg(theta);
		ofRotateZDeg(180 + iota);
		ofTranslate(-width/2,-height/ 2);
		mesh.drawWireframe();
	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
