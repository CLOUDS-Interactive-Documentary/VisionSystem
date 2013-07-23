# Empty Visual System 

Welcome to CLOUDS Visual System!
We call VisualSystems to modular visual sketches that reinforce and illustrate abstract concepts present on CLOUDS Documentary.

In order to make the process of making a VisualSystem efficient and easy. We have put together [Reza Ali](http://www.syedrezaali.com) DJ environment call *Rezonator*. This will lets sketch powerful sketches providing the exquisite `ofxUI` to customize every single detail of it. This variables will be able to be save as **Presets**. At the end this Presets are going to be curated inside the documentary.

Together with [James George](http://jamesgeorge.org/)'s `ofxTimeLine` this environment provides the ability to animate those changes over time.


## Create your own visual system

### Fast Way:
	
	
	Download openFrameworks 0.7.4 http://www.openframeworks.cc/download/
	
	Download http://cloudsdocumentary.com/codestorm/VisualSystemTemplate.zip
	
	unzip VisualSystemTemplate.zip into apps/myApps
	
	rename project files
	
	
### Github Way: 

	cd openFrameworks
	cd apps/myApps
	git clone https://github.com/CLOUDS-Interactive-Documentary/emptyVisualSystem

	2) run git submodule init
	
	Once the repo is cloned you need to pull the VisualSystemsLibrary submodule. This contain the source of Reza's Rezonator mixed with James's ofxTimeLine. Together this provide the abstract
	class you will extend in order to make your own VisualSystem.

		cd emptyVisualSystem	
		git pull && git submodule init && git submodule update && git submodule status

	3) create a new repo on CLOUDS-Interactive-Documentary, for example 'Ocean' and at git@github.com:CLOUDS-Interactive-Documentary/Ocean

	4) make a copy of emptyVisualSystem folder in myApps/ and rename it to Ocean

	5) in the terminal, cd into Ocean/ and do the following 3 commands

		git remote rm origin
		git remote add origin git@github.com:CLOUDS-Interactive-Documentary/<YourRepoName>.git 
		git push -u origin master

	This will redirect the empty repo to your new repo

	6) rename the project files and files and you are good to go

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

This environment use some addons from the community. Go to addons...

	cd ../../../addons/
	
…  and start adding:

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

Once you follow the installation process you can compile and see the emptyVisualSystem working. To make your own VisualSystem you need to duplicate the emptyVisualSystem folder. And then rename the `emptyVisualSystem.h` and `emptyVisualSystem.cpp`

This will require some extra renaming on the `testApp.h` source as well. 

### Your Code 

As you can see there is `vs_src` folder. That's were your extended class of `CloudsVisualSystem` will be together with all the classes you make. This folder together with the content of the `data` folder witch also contents your **Presets** are going to be merge with the CLOUDS apps.

It's very important that you are consistent with the name of your VisualSystem. The name you choose for it have to be the same of your repo and embed on your extended class. Please put the name of it after 'CloudVisualSystem______' so if your VisualSystem is call "World" the repo will be call "World" and the extended class "CloudVisualSystemWorld".

One of the first things you may change on your custom extended class is the `getSystemName()` function in order to return the exact name of your VS ( and/or your repo)

	string CloudVisualSystemWorld::getSystemName()
	{
		return "World";
	}

By doing this the extended class will know how to access to his own `data/` folder when is embedded on the main CLOUDS app.
 
### Hot-Keys 

* F : Toogle Fullscreen
* H : Hide/Show GUI
* E : Arrange GUI in Cascade  
* R : Arrange GUI at Top
* T : Minimize GUI
* Y : Arrange GUI in circle
* ` : Take a snapshoot

### How to Animate?

### How to Save/Delete a Preset?


 






