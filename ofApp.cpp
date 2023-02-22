#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(300, 4);
	this->mesh = ico_sphere.getMesh();
}

//--------------------------------------------------------------
void ofApp::update() {

	this->draw_mesh = this->mesh;
	this->line_mesh = this->mesh;

	for (int i = 0; i < this->draw_mesh.getNumVertices(); i++) {

		glm::vec3 vertex = this->draw_mesh.getVertex(i);
		auto noise_value = ofNoise(glm::vec4(vertex * 0.005, ofGetFrameNum() * 0.0005));

		if (noise_value > 0.46 && noise_value < 0.5) {

			vertex = glm::normalize(vertex) * ofMap(noise_value, 0.46, 0.5, 300, 350);
		}
		else if (noise_value > 0.5 && noise_value < 0.54) {

			vertex = glm::normalize(vertex) * ofMap(noise_value, 0.5, 0.54, 350, 300);
		}

		this->draw_mesh.setVertex(i, vertex);
		this->line_mesh.setVertex(i, vertex);
		this->draw_mesh.addColor(ofColor(0));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.37);

	this->draw_mesh.draw();

	ofSetColor(255);
	this->line_mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}