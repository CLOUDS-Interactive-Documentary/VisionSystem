# Empty Visual System 

Welcome to CLOUDS Visual System!
We call VisualSystems to modular visual sketches that reinforce and illustrate abstract concepts present on CLOUDS Documentary.

In order to make the process of making a VisualSystem efficient and easy. We have put together [Reza Ali](http://www.syedrezaali.com) DJ environment call *Rezonator*. This will lets sketch powerful sketches providing the exquisite `ofxUI` to customize every single detail of it. This variables will be able to be save as **Presets**. At the end this Presets are going to be curated inside the documentary.

Together with [James George](http://jamesgeorge.org/)'s `ofxTimeLine` this environment provides the ability to animate those changes over time.


## Install

### Clone the emptyVisualSystem Example

	cd openFrameworks
	cd apps/myApps
	git clone git@github.com:CLOUDS-Interactive-Documentary/emptyVisualSystem.git

### Add VisualSystemLibraries Submodule

Once the repo is cloned you need to pull the VisualSystemsLibrary submodule. This contain the source of Reza's Rezonator mixed with James's ofxTimeLine. Together this provide the abstract class you will extend in order to make your own VisualSystem.

	
	cd emptyVisualSystem	
	git pull && git submodule init && git submodule update && git submodule status

### Modify ofMaterial

The resonator let you adjust the camera, lights and other important rendering sets like the material. In order to be able to change the material properties from the GUI we need to modify `openframeworks/libs/openFrameworks/gl/ofMaterial.h` by forcing this functions to pass their values by reference:

	ofFloatColor &getDiffuseColor();
	ofFloatColor &getAmbientColor();
	ofFloatColor &getSpecularColor();
	ofFloatColor &getEmissiveColor();
	float &getShininess(); 
	
Do the same on the `ofMaterial.cpp`:

	float& ofMaterial::getShininess(){
		return shininess;
	}

	ofFloatColor& ofMaterial::getDiffuseColor() {
		return diffuse;
	}

	ofFloatColor& ofMaterial::getAmbientColor() {
		return ambient;
	}

	ofFloatColor& ofMaterial::getSpecularColor() {
		return specular;
	}

	ofFloatColor& ofMaterial::getEmissiveColor() {
		return emissive;
	}
	
### Install Addons

This environment use some addons from the community. Go to addons and start adding them.

	cd ../../../addons/

* [ofxRange](https://github.com/Flightphase/ofxRange) by James George

		git clone git@github.com:Flightphase/ofxRange.git

* [ofxMSATimer](https://github.com/obviousjim/ofxMSATimer) by Memo Atken, James George, Philip Whitfield, Juan Pablo Manson

		git clone git@github.com:obviousjim/ofxMSATimer.git
		
* [ofxTween](https://github.com/Flightphase/ofxTween) by James George

		git clone git@github.com:Flightphase/ofxTween.git
		
* [ofxTextInputField](https://github.com/Flightphase/ofxTextInputField) by James George, Elliot Woods, Kimchi and Chips.

		git clone git@github.com:Flightphase/ofxTextInputField.git
		
* [ofxTimecode](https://github.com/YCAMInterlab/ofxTimecode) by James George

		git clone git@github.com:YCAMInterlab/ofxTimecode.git
		
* [ofxTimeline](https://github.com/YCAMInterlab/ofxTimeline) by James George

		git clone git@github.com:YCAMInterlab/ofxTimeline.git
		git checkout develop
		
* [ofxCameraSaveLoad](https://github.com/roymacdonald/ofxCameraSaveLoad) by Roy MacDonald

		git clone git@github.com:roymacdonald/ofxCameraSaveLoad.git
		
* [ofxGenerative](https://github.com/rezaali/ofxGenerative) by Reza Ali

		git clone git@github.com:rezaali/ofxGenerative.git
		
* [ofxUI](https://github.com/rezaali/ofxUI) by Reza Ali

		git clone git@github.com:rezaali/ofxUI.git
		
## Making your own VisualSystem

### Your Code 

Your as you can see there is `vs_src` folder. There will be the extended class of `CloudsVisualSystem` together with all the classes your VS need.

### Hot-Keys 

### How to Animate?

### How to Save/Delete a Preset?


 






